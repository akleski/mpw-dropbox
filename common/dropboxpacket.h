#ifndef DROPBOXPACKET_H
#define DROPBOXPACKET_H

#include <QDataStream>

enum PacketType
{
    Name,
    NameResp,//not used?

    ClientFiles,
    ClientFilesResp,

    GetFiles,
    GetFilesResp,

    GetFile,
    GetFileResp,

    SendFiles,
    SendFilesResp,

    SendFile,
    SendFileResp
};

QDataStream& operator >>(QDataStream& in, PacketType& e);

#endif // DROPBOXPACKET_H
