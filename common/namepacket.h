#ifndef NAMEPACKET_H
#define NAMEPACKET_H

#include "dropboxpacket.h"

class NamePacket
{
public:
    NamePacket(QString name);
    ~NamePacket();

    QString name() const;
    void setName(const QString &name);

private:
    QString mName;
};

QDataStream &operator<<(QDataStream &out, const NamePacket &packet);
QDataStream &operator>>(QDataStream &in, NamePacket &packet);

#endif // NAMEPACKET_H
