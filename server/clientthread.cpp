#include "clientthread.h"

#include <QTcpSocket>

ClientThread::ClientThread(int socketDescriptor, QObject *parent)
: QThread(parent),
  socketDescriptor(socketDescriptor)
{

}

void ClientThread::run()
{
    mTcpSocket = new QTcpSocket(NULL);
    if (!mTcpSocket->setSocketDescriptor(socketDescriptor)) {
        emit error(mTcpSocket->error());
        return;
    }
    connect(mTcpSocket, SIGNAL(readyRead()), this, SLOT(processData()));

    connect(mTcpSocket, SIGNAL(disconnected()), this, SLOT(terminate()));
    if(mTcpSocket->waitForConnected())
        qDebug("Connected!");

    qDebug()<< "waitfor read ready: " <<mTcpSocket->waitForReadyRead();
    char buf[1024];
    qDebug()<<mTcpSocket->readLine(buf, sizeof(buf));
    qDebug()<<buf;
    exec();
}

void ClientThread::processData()
{
    qDebug()<< __FUNCTION__;
    char buf[1024];
    mTcpSocket->readLine(buf, sizeof(buf));
    qDebug()<<buf;
}
