#include "server.h"

#include <QTcpServer>
#include <QCoreApplication>
#include "clientthread.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{

}

Server::~Server()
{

}

void Server::start()
{
    if(!listen(QHostAddress::Any, 6543))
    {
        qDebug() << tr("Unable to start the server: %1.").arg(errorString());
        QCoreApplication::exit();
        return;
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    ClientThread *thread = new ClientThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
