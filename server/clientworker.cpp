#include "clientworker.h"
#include <unistd.h>

ClientWorker::ClientWorker(QObject *parent) : QObject(parent)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
}

ClientWorker::~ClientWorker()
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
}

void ClientWorker::process()
{
    printf("%s\n", __FUNCTION__);fflush(stdout);



    emit connected();

    while(mTcpSocket->isOpen()){
        if(mPacketsToSend.isEmpty()){
            usleep(100);
        } else {
            qint64 ret = mTcpSocket->write(mPacketsToSend.dequeue());
            printf("send packet bytes sent: %lld\n", ret);fflush(stdout);
        }
    }
    emit finished();
}
qint64 ClientWorker::socketDescriptor() const
{
    return mSocketDescriptor;
}

void ClientWorker::setSocketDescriptor(const qint64 &socketDescriptor)
{
    mSocketDescriptor = socketDescriptor;
}

QTcpSocket *ClientWorker::tcpSocket() const
{
    return mTcpSocket;
}

void ClientWorker::setTcpSocket(QTcpSocket *tcpSocket)
{
    mTcpSocket = tcpSocket;
}

QQueue<QByteArray> ClientWorker::packetsToSend() const
{
    return mPacketsToSend;
}

void ClientWorker::setPacketsToSend(const QQueue<QByteArray> &packetsToSend)
{
    mPacketsToSend = packetsToSend;
}


