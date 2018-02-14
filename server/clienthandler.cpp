#include "clienthandler.h"

#include <QTcpSocket>
#include <QMetaEnum>
#include <stdio.h>
#include <QStringBuilder>
#include <unistd.h>
#include <QCoreApplication>

ClientHandler::ClientHandler(qintptr socketDescriptor, QObject *parent)
: QObject(parent),
  mSocketDescriptor(socketDescriptor)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
}

void ClientHandler::start()
{
    printf("%s\nClientHandler", __FUNCTION__);fflush(stdout);

    mTcpSocket = new QTcpSocket(this);

    if (!mTcpSocket->setSocketDescriptor(mSocketDescriptor)) {
        printf("ERROR!!!\n");fflush(stdout);
        return;
    }
    if(mTcpSocket->waitForConnected()){
        printf("Connected!\n");fflush(stdout);
    }
    else{
         printf("Not connected!\n");fflush(stdout);
    }

    connect(this, SIGNAL(namePacketReceived()), this, SLOT(replyToNamePacket()), Qt::QueuedConnection);
    connect(mTcpSocket, SIGNAL(readyRead()), this, SLOT(processData()), Qt::AutoConnection);
}

void ClientHandler::processData()
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
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

        printf("received packet - type: %s\n", getTextForPacketType(type));fflush(stdout);

        switch(type){
        case Name:
        {
            NamePacket namePacket;
            clientReadStream >> namePacket;
            printf("NamePacket name: %s\n", namePacket.name().toStdString().c_str());fflush(stdout);

            mUser = namePacket.name();
            emit namePacketReceived();
            break;
        }
        case GetServerFiles:
        {
            GetServerFilesPacket packet;
            clientReadStream >> packet;

            emit getServerFilesPacketReceived(mSocketDescriptor, mUser);
            break;
        }

        case UploadFiles:
        {
            UploadFilesPacket packet;
            clientReadStream >> packet;

            emit uploadFiles(mSocketDescriptor, mUser, packet.files());
            break;
        }
        case DownloadFiles:
        {
            DownloadFilesPacket packet;
            clientReadStream >> packet;

            emit downloadFiles(mSocketDescriptor, mUser, packet.files());
            break;
        }

        case NameResp:
        case GetServerFilesResp:
        case UploadFilesResp:
        case DownloadFile:
        case DownloadFilesResp:
        default:
            printf("unexpected packet - this should not happen... \n");fflush(stdout);
            break;
        }
    }
}

void ClientHandler::replyToNamePacket()
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    NameResponsePacket* resp = new NameResponsePacket("OK");
    sendPacket(NameResp, resp);
    delete resp;
}

void ClientHandler::replyToGetServerFiles(QStringList files)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    GetServerFilesResponsePacket resp;
    resp.setFiles(files);
    sendPacket(GetServerFilesResp, &resp);
}

void ClientHandler::replyToUploadFiles(QString status)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    UploadFilesResponsePacket resp;
    resp.setStatus(status);
    sendPacket(UploadFilesResp, &resp);
}

void ClientHandler::fileReadyForDownload(QString file)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    DownloadFilePacket resp;
    resp.setFile(file);
    sendPacket(DownloadFile, &resp);
}

void ClientHandler::allFilesDownloaded()
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    DownloadFilesResponsePacket resp;
    resp.setStatus("OK");
    sendPacket(DownloadFilesResp, &resp);
}

qintptr ClientHandler::socketDescriptor() const
{
    return mSocketDescriptor;
}

void ClientHandler::setSocketDescriptor(const qintptr &value)
{
    mSocketDescriptor = value;
}

void ClientHandler::sendPacket(PacketType type, void *packet)
{
    printf("%s %s\n",__FUNCTION__, getTextForPacketType(type));fflush(stdout);
    QByteArray block;
    QDataStream sendStream(&block, QIODevice::ReadWrite);

    sendStream << quint32(0) //placeholder for size
               << type; //packet type

    switch(type)
    {
    case Name:
    {
        NamePacket* obj = static_cast<NamePacket*>(packet);
        sendStream << (*obj);
        break;
    }
    case NameResp:
    {
        NameResponsePacket* obj = static_cast<NameResponsePacket*>(packet);
        sendStream << (*obj);
        break;
    }
    case GetServerFiles:
    {
        GetServerFilesPacket* obj = static_cast<GetServerFilesPacket*>(packet);
        sendStream << (*obj);
        break;
    }
    case GetServerFilesResp:
    {
        GetServerFilesResponsePacket* obj =
                static_cast<GetServerFilesResponsePacket*>(packet);
        sendStream << (*obj);
        break;
    }
    case UploadFiles:
    {
        UploadFilesPacket* obj = static_cast<UploadFilesPacket*>(packet);
        sendStream << (*obj);
        break;
    }
    case UploadFilesResp:
    {
        UploadFilesResponsePacket* obj =
                static_cast<UploadFilesResponsePacket*>(packet);
        sendStream << (*obj);
        break;
    }
    case DownloadFiles:
    {
        DownloadFilesPacket* obj = static_cast<DownloadFilesPacket*>(packet);
        sendStream << (*obj);
        break;
    }
    case DownloadFile:
    {
        DownloadFilePacket* obj = static_cast<DownloadFilePacket*>(packet);
        sendStream << (*obj);
        break;
    }
    case DownloadFilesResp:
    {
        DownloadFilesResponsePacket* obj =
                static_cast<DownloadFilesResponsePacket*>(packet);
        sendStream << (*obj);
        break;
    }
    }

    //update size
    sendStream.device()->seek(0);
    sendStream << (quint32)(block.size() - sizeof(quint32));

    qint64 ret = mTcpSocket->write(block);
    mTcpSocket->flush();
    printf("send packet bytes sent: %lld\n", ret);fflush(stdout);
}

QString ClientHandler::getUser() const
{
    return mUser;
}
