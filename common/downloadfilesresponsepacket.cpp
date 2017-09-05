#include "downloadfilesresponsepacket.h"

DownloadFilesResponsePacket::DownloadFilesResponsePacket()
{

}

QString DownloadFilesResponsePacket::status() const
{
    return mStatus;
}

void DownloadFilesResponsePacket::setStatus(const QString &status)
{
    mStatus = status;
}

QDataStream &operator<<(QDataStream &out, const DownloadFilesResponsePacket &packet)
{
    out << packet.status();
    return out;
}

QDataStream &operator>>(QDataStream &in, DownloadFilesResponsePacket &packet)
{
    QString status;
    in >> status;
    packet = DownloadFilesResponsePacket();\
    packet.setStatus(status);
    return in;
}
