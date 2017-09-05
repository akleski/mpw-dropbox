#include "uploadfilesresponsepacket.h"

UploadFilesResponsePacket::UploadFilesResponsePacket()
{

}

QString UploadFilesResponsePacket::status() const
{
    return mStatus;
}

void UploadFilesResponsePacket::setStatus(const QString &status)
{
    mStatus = status;
}

QDataStream &operator<<(QDataStream &out, const UploadFilesResponsePacket &packet)
{
    out << packet.status();
    return out;
}

QDataStream &operator>>(QDataStream &in, UploadFilesResponsePacket &packet)
{
    QString status;
    in >> status;
    packet = UploadFilesResponsePacket();\
    packet.setStatus(status);
    return in;
}
