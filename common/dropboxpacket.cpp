#include "dropboxpacket.h"

QDataStream& operator >>(QDataStream& in, PacketType& e)
{
    quint32 buffer;
    in >> buffer;
    e = PacketType(buffer);
    return in;
}
