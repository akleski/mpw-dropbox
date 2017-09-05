#ifndef DROPBOXPACKET_H
#define DROPBOXPACKET_H

#include "namepacket.h"
#include "nameresponsepacket.h"
#include "getserverfilespacket.h"
#include "getserverfilesresponsepacket.h"
#include "uploadfilespacket.h"
#include "uploadfilesresponsepacket.h"
#include "downloadfilespacket.h"
#include "downloadfilepacket.h"
#include "downloadfilesresponsepacket.h"

enum PacketType
{
    Name,
    NameResp,

    GetServerFiles,
    GetServerFilesResp,

    UploadFiles,
    UploadFilesResp,

    DownloadFiles,
    DownloadFile,
    DownloadFilesResp,
};

QDataStream& operator >>(QDataStream& in, PacketType& e);

#endif // DROPBOXPACKET_H
