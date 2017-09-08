#include "dropboxpacket.h"

#include <QDataStream>
#include <QTcpSocket>
#include <QByteArray>

static const char * PacketTypeStrings[] = {
    "Name",
    "NameResp",
    "GetServerFiles",
    "GetServerFilesResp",
    "UploadFiles",
    "UploadFilesResp",
    "DownloadFiles",
    "DownloadFile",
    "DownloadFilesResp"};

const char * getTextForPacketType( int enumVal )
{
  return PacketTypeStrings[enumVal];
}

QDataStream& operator >>(QDataStream& in, PacketType& e)
{
    quint32 buffer;
    in >> buffer;
    e = PacketType(buffer);
    return in;
}
