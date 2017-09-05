#include "downloadfilepacket.h"

DownloadFilePacket::DownloadFilePacket()
{

}

QString DownloadFilePacket::file() const
{
    return mFile;
}

void DownloadFilePacket::setFile(const QString &file)
{
    mFile = file;
}

QDataStream &operator<<(QDataStream &out, const DownloadFilePacket &packet)
{
    out << packet.file();
    return out;
}

QDataStream &operator>>(QDataStream &in, DownloadFilePacket &packet)
{
    QString file;
    in >> file;
    packet = DownloadFilePacket();\
    packet.setFile(file);
    return in;
}
