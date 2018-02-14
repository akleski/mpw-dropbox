#include "nameresponsepacket.h"

NameResponsePacket::NameResponsePacket()
{
}

NameResponsePacket::NameResponsePacket(const QString &status)
    : mStatus(status)
{
}

QString NameResponsePacket::status() const
{
    return mStatus;
}

void NameResponsePacket::setStatus(const QString &value)
{
    mStatus = value;
}

QDataStream &operator<<(QDataStream &out, const NameResponsePacket &packet)
{
    out << packet.status();
    return out;
}

QDataStream &operator>>(QDataStream &in, NameResponsePacket &packet)
{
    QString status;
    in >> status;
    packet = NameResponsePacket(status);
    return in;
}
