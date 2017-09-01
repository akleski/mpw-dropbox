#ifndef CLIENTFILESPACKET_H
#define CLIENTFILESPACKET_H

#include <QStringList>

class ClientFilesPacket
{
public:
    ClientFilesPacket();
    ~ClientFilesPacket();

    QStringList clientFiles() const;
    void setClientFiles(const QStringList &clientFiles);

private:
    QStringList mClientFiles;
};

QDataStream &operator<<(QDataStream &out, const ClientFilesPacket &packet);
QDataStream &operator>>(QDataStream &in, ClientFilesPacket &packet);

#endif // CLIENTFILESPACKET_H
