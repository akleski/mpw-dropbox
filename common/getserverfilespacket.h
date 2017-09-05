#ifndef GETSERVERFILESPACKET_H
#define GETSERVERFILESPACKET_H

#include <QString>
#include <QDataStream>

class GetServerFilesPacket
{
public:
    GetServerFilesPacket();
};

QDataStream &operator<<(QDataStream &out, const GetServerFilesPacket &packet);
QDataStream &operator>>(QDataStream &in, GetServerFilesPacket &packet);

#endif // GETSERVERFILESPACKET_H
