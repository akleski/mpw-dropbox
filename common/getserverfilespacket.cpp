#include "getserverfilespacket.h"

GetServerFilesPacket::GetServerFilesPacket()
{

}

QDataStream &operator<<(QDataStream &out, const GetServerFilesPacket &packet)
{
    return out;
}

QDataStream &operator>>(QDataStream &in, GetServerFilesPacket &packet)
{
    packet = GetServerFilesPacket();
    return in;
}
