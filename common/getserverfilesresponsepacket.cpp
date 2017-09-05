#include "getserverfilesresponsepacket.h"

GetServerFilesResponsePacket::GetServerFilesResponsePacket()
{

}

QStringList GetServerFilesResponsePacket::files() const
{
    return mFiles;
}

void GetServerFilesResponsePacket::setFiles(const QStringList &files)
{
    mFiles = files;
}

QDataStream &operator<<(QDataStream &out, const GetServerFilesResponsePacket &packet)
{
    out << packet.files();
    return out;
}

QDataStream &operator>>(QDataStream &in, GetServerFilesResponsePacket &packet)
{
    QStringList files;
    in >> files;
    packet = GetServerFilesResponsePacket();
    packet.setFiles(files);
    return in;
}
