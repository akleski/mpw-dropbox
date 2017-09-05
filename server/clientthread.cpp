#include "clientthread.h"

#include "dropboxpacket.h"

#include <QTcpSocket>
#include <QDebug>

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

    exec();
}

void ClientThread::processData()
{
    QDataStream clientReadStream(mTcpSocket);
    quint32 next_block_size = 0;
    while(true) {
        if (!next_block_size) {
            if (mTcpSocket->bytesAvailable() < sizeof(quint32)) { // are size data available
                break;
            }
            clientReadStream >> next_block_size;
        }

        if (mTcpSocket->bytesAvailable() < next_block_size) {
            break;
        }
        PacketType type;
        clientReadStream >> type;

        switch(type){
        case PacketType::Name:
            NamePacket namePacket;
            clientReadStream >> namePacket;
            qDebug() << "NamePacket name: " << namePacket.name();
            break;
        }

        next_block_size = 0;
    }
}
