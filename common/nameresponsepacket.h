#ifndef NAMERESPONSEPACKET_H
#define NAMERESPONSEPACKET_H

#include <QString>
#include <QDataStream>

class NameResponsePacket
{
public:
    NameResponsePacket();
    NameResponsePacket(const QString &status);

    QString status() const;
    void setStatus(const QString &value);

private:
    QString mStatus;
};

QDataStream &operator<<(QDataStream &out, const NameResponsePacket &packet);
QDataStream &operator>>(QDataStream &in, NameResponsePacket &packet);

#endif // NAMERESPONSEPACKET_H
