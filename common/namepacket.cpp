#include "namepacket.h"
#include <QString>

NamePacket::NamePacket(QString name) : mName(name)
{
}

NamePacket::~NamePacket()
{
}

QString NamePacket::name() const
{
    return mName;
}

void NamePacket::setName(const QString &name)
{
    mName = name;
}


QDataStream &operator<<(QDataStream &out, const NamePacket &packet)
{
    out << packet.name();
    return out;
}

QDataStream &operator>>(QDataStream &in, NamePacket &packet)
{
    QString name;
    in >> name;
    packet = NamePacket(name);
    return in;
}
