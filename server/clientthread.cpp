#include "clientthread.h"

#include "dropboxpacket.h"

#include <QTcpSocket>
#include <QDebug>

ClientThread::ClientThread(int socketDescriptor, QObject *parent)
: QThread(parent),
  socketDescriptor(socketDescriptor)
{
    qDebug() << __FUNCTION__;
    connect(this, SIGNAL(namePacketReceived()), this, SLOT(namePacketReceived()), Qt::QueuedConnection);

}

void ClientThread::run()
{
    qDebug() << __FUNCTION__;
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
    qDebug() << __FUNCTION__;
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
            mUser = namePacket.name();
            emit namePacketReceived();
            break;
        }
        case GetServerFiles:
        {
            GetServerFilesPacket packet;
            clientReadStream >> packet;

            emit getServerFilesPacketReceived(mUser);
            break;
        }

        case UploadFiles:
        {
            UploadFilesPacket packet;
            clientReadStream >> packet;

            emit uploadFiles(mUser, packet.files());
            break;
        }
        case DownloadFiles:
        {
            DownloadFilesPacket packet;
            clientReadStream >> packet;

            emit downloadFiles(mUser, packet.files());
            break;
        }

        case NameResp:
        case GetServerFilesResp:
        case UploadFilesResp:
        case DownloadFile:
        case DownloadFilesResp:
        default:
            qDebug()<<"unexpected packet - this should not happen... ";
            break;
        }
    }
}

void ClientThread::replyToNamePacket()
{
    qDebug() << __FUNCTION__;
    NameResponsePacket resp("OK");

    DropboxPacket::sendPacket(mTcpSocket, NameResp, &resp);
}

void ClientThread::replyToGetServerFiles(QStringList files)
{
    qDebug() << __FUNCTION__;
    GetServerFilesResponsePacket resp;
    resp.setFiles(files);

    DropboxPacket::sendPacket(mTcpSocket, GetServerFilesResp, &resp);
}

void ClientThread::replyToUploadFiles(QString status)
{
    qDebug() << __FUNCTION__;
    UploadFilesResponsePacket resp;
    resp.setStatus(status);

    DropboxPacket::sendPacket(mTcpSocket, UploadFilesResp, &resp);
}

void ClientThread::fileReadyForDownload(QString file)
{
    qDebug() << __FUNCTION__;
    DownloadFilePacket resp;
    resp.setFile(file);

    DropboxPacket::sendPacket(mTcpSocket, DownloadFile, &resp);
}

void ClientThread::allFilesDownloaded()
{
    qDebug() << __FUNCTION__;
    DownloadFilesResponsePacket resp;
    resp.setStatus("OK");

    DropboxPacket::sendPacket(mTcpSocket, DownloadFilesResp, &resp);
}
