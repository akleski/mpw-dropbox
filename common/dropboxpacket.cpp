#include "dropboxpacket.h"

#include <QDataStream>
#include <QTcpSocket>
#include <QByteArray>

QDataStream& operator >>(QDataStream& in, PacketType& e)
{
    quint32 buffer;
    in >> buffer;
    e = PacketType(buffer);
    return in;
}

void DropboxPacket::sendPacket(QTcpSocket *socket, PacketType type, void *packet)
{
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
        DownloadFilePacket* obj = static_cast<DownloadFilePacket*>(packet);
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

    qDebug() << "send packet: " << type << " bytes sent: " << socket->write(block);
}
