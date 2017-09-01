#include "clientfilespacket.h"

ClientFilesPacket::ClientFilesPacket()
{

}

ClientFilesPacket::~ClientFilesPacket()
{

}

QStringList ClientFilesPacket::clientFiles() const
{
    return mClientFiles;
}

void ClientFilesPacket::setClientFiles(const QStringList &clientFiles)
{
    mClientFiles = clientFiles;
}

QDataStream &operator<<(QDataStream &out, const ClientFilesPacket &packet)
{
    out << packet.clientFiles();
    return out;
}

QDataStream &operator>>(QDataStream &in, ClientFilesPacket &packet)
{
    QStringList clientFiles;
    in >> clientFiles;
    packet = ClientFilesPacket();
    packet.setClientFiles(clientFiles);
    return in;
}
