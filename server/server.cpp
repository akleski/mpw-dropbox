
#include <QTcpServer>
#include <QCoreApplication>
#include <unistd.h>

#include "server.h"
#include "clienthandler.h"
#include "common.h"
#include "workerthread.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    for(int i = 0; i < 5; ++i)
    {
        WorkerThread* worker = new WorkerThread(QString::number(i), this);
        mWorkers.append(worker);
        worker->start();
    }
}

Server::~Server()
{
    printf("%s\n", __FUNCTION__);fflush(stdout);

}

void Server::start()
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    if(!listen(QHostAddress(DROPBOX_SERVER_ADDRESS), 6543))
    {
        printf("Unable to start the server: %s\n",errorString().toStdString().c_str());fflush(stdout);
        QCoreApplication::exit();
        return;
    }
}

void Server::clientThreadFinished()
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    ClientHandler* thread = (ClientHandler*)this->sender();
    mClientThreads.remove(thread->socketDescriptor());
}

void Server::getServerFilesForUser(qint64 clientSocketDesc, QString user)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    QStringList files;
    for(int i = 0; i< 15; ++i){
        files << "file"+QString::number(i)+".txt";
    }
    QGenericReturnArgument ret;
    metaObject()->invokeMethod(mClientThreads.value(clientSocketDesc),
                               "replyToGetServerFiles",
                               Qt::QueuedConnection,
                               ret,
                               Q_ARG(QStringList, files));
}

void Server::uploadFiles(qint64 clientSocketDesc, QString user, QStringList files)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);

    QGenericReturnArgument ret;
    metaObject()->invokeMethod(mClientThreads.value(clientSocketDesc),
                               "replyToUploadFiles",
                               Qt::QueuedConnection,
                               ret,
                               Q_ARG(QString, "OK"));
}

void Server::downloadFiles(qint64 clientSocketDesc, QString user, QStringList files)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    QGenericReturnArgument ret;
    ClientHandler* client = mClientThreads.value(clientSocketDesc);
    foreach (QString file, files) {
        metaObject()->invokeMethod(client,
                                   "fileReadyForDownload",
                                   Qt::QueuedConnection,
                                   ret,
                                   Q_ARG(QString, file));
    }
    metaObject()->invokeMethod(client,
                               "allFilesDownloaded",
                               Qt::QueuedConnection,
                               ret);
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    printf("%s sd: %d\n", __FUNCTION__, socketDescriptor);fflush(stdout);
    ClientHandler *thread = new ClientHandler(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), this, SLOT(clientThreadFinished()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    connect(thread, SIGNAL(getServerFilesPacketReceived(qint64, QString)), this, SLOT(getServerFilesForUser(qint64,QString)), Qt::QueuedConnection);
    connect(thread, SIGNAL(uploadFiles(qint64, QString, QStringList)), this, SLOT(uploadFiles(qint64,QString,QStringList)), Qt::QueuedConnection);
    connect(thread, SIGNAL(downloadFiles(qint64, QString, QStringList)), this, SLOT(downloadFiles(qint64,QString,QStringList)), Qt::QueuedConnection);

    thread->start();
    mClientThreads.insert(socketDescriptor, thread);
}
