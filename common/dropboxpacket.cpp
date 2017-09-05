#include "dropboxpacket.h"

#include <QDataStream>

QDataStream& operator >>(QDataStream& in, PacketType& e)
{
    quint32 buffer;
    in >> buffer;
    e = PacketType(buffer);
    return in;
}
