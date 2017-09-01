#include "clientfilesresppacket.h"

ClientFilesRespPacket::ClientFilesRespPacket()
{

}

ClientFilesRespPacket::~ClientFilesRespPacket()
{

}

QStringList ClientFilesRespPacket::serverFiles() const
{
    return mServerFiles;
}

void ClientFilesRespPacket::setServerFiles(const QStringList &serverFiles)
{
    mServerFiles = serverFiles;
}


QDataStream &operator<<(QDataStream &out, const ClientFilesRespPacket &packet)
{
    out << packet.serverFiles();
    return out;
}

QDataStream &operator>>(QDataStream &in, ClientFilesRespPacket &packet)
{
    QStringList serverFiles;
    in >> serverFiles;
    packet = ClientFilesRespPacket();
    packet.setServerFiles(serverFiles);
    return in;
}
