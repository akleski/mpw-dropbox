#ifndef CLIENTFILESRESPPACKET_H
#define CLIENTFILESRESPPACKET_H

#include <QStringList>

class ClientFilesRespPacket
{
public:
    ClientFilesRespPacket();
    ~ClientFilesRespPacket();

    QStringList serverFiles() const;
    void setServerFiles(const QStringList &serverFiles);

private:
    QStringList mServerFiles;
};

QDataStream &operator<<(QDataStream &out, const ClientFilesRespPacket &packet);
QDataStream &operator>>(QDataStream &in, ClientFilesRespPacket &packet);

#endif // CLIENTFILESRESPPACKET_H
