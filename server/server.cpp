
#include <QTcpServer>
#include <QCoreApplication>

#include "server.h"
#include "clientthread.h"
#include "common.h"
#include "workerthread.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    qDebug() << __FUNCTION__;
    for(int i = 0; i < 5; ++i)
    {
        WorkerThread* worker = new WorkerThread(QString::number(i), this);
        mWorkers.append(worker);
        worker->start();
    }
}

Server::~Server()
{
    qDebug() << __FUNCTION__;

}

void Server::start()
{
    qDebug() << __FUNCTION__;
    if(!listen(QHostAddress(DROPBOX_SERVER_ADDRESS), 6543))
    {
        qDebug() << tr("Unable to start the server: %1.").arg(errorString());
        QCoreApplication::exit();
        return;
    }
}

void Server::clientThreadFinished()
{
    qDebug() << __FUNCTION__;
    mClientThreads.removeOne((ClientThread*)this->sender());
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "incomingConnection " << socketDescriptor;
    ClientThread *thread = new ClientThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), this, SLOT(clientThreadFinished()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    connect(thread, SIGNAL(getServerFilesPacketReceived(QString)), this, SLOT(), Qt::QueuedConnection);
    connect(thread, SIGNAL(uploadFiles(QString, QStringList)), this, SLOT(), Qt::QueuedConnection);
    connect(thread, SIGNAL(downloadFiles(QString, QStringList)), this, SLOT(), Qt::QueuedConnection);

    thread->start();
    mClientThreads.append(thread);
}
