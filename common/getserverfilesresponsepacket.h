#ifndef GETSERVERFILESRESPONSEPACKET_H
#define GETSERVERFILESRESPONSEPACKET_H

#include <QString>
#include <QDataStream>
#include <QStringList>

class GetServerFilesResponsePacket
{
public:
    GetServerFilesResponsePacket();

    QStringList files() const;
    void setFiles(const QStringList &files);

private:
    QStringList mFiles;
};

QDataStream &operator<<(QDataStream &out, const GetServerFilesResponsePacket &packet);
QDataStream &operator>>(QDataStream &in, GetServerFilesResponsePacket &packet);


#endif // GETSERVERFILESRESPONSEPACKET_H
