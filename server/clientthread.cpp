#include "clientthread.h"

#include "dropboxpacket.h"

#include <QTcpSocket>
#include <QDebug>

ClientThread::ClientThread(int socketDescriptor, QObject *parent)
: QThread(parent),
  socketDescriptor(socketDescriptor)
{

    connect(this, SIGNAL(namePacketReceived()), this, SLOT(namePacketReceived()), Qt::QueuedConnection);

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
    else
         qDebug("Not connected!");

    exec();
}

void ClientThread::processData()
{
    QDataStream clientReadStream(mTcpSocket);
    quint32 next_block_size = 0;
    while(true)
    {
        if (!next_block_size)
        {
            if (mTcpSocket->bytesAvailable() < sizeof(quint32))
            {
                break;
            }
            clientReadStream >> next_block_size;
        }

        if (mTcpSocket->bytesAvailable() < next_block_size) {
            break;
        }
        PacketType type;
        clientReadStream >> type;

        qDebug() << "received packet - type: " << type;

        switch(type){
        case Name:
        {
            NamePacket namePacket;
            clientReadStream >> namePacket;
            qDebug() << "NamePacket name: " << namePacket.name();
            emit namePacketReceived();
            break;
        }
        case NameResp:
            break;
        case GetServerFiles:
            break;
        case GetServerFilesResp:
            break;
        case UploadFiles:
            break;
        case UploadFilesResp:
            break;
        case DownloadFiles:
            break;
        case DownloadFile:
            break;
        case DownloadFilesResp:
            break;
        }
    }
}

void ClientThread::replyToNamePacket()
{
    NameResponsePacket response("OK");

    DropboxPacket::sendPacket(mTcpSocket, NameResp, &response);
}
