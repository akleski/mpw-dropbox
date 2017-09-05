#ifndef DOWNLOADFILESRESPONSEPACKET_H
#define DOWNLOADFILESRESPONSEPACKET_H

#include <QString>
#include <QDataStream>

class DownloadFilesResponsePacket
{
public:
    DownloadFilesResponsePacket();

    QString status() const;
    void setStatus(const QString &status);

private:
    QString mStatus;
};

QDataStream &operator<<(QDataStream &out, const DownloadFilesResponsePacket &packet);
QDataStream &operator>>(QDataStream &in, DownloadFilesResponsePacket &packet);


#endif // DOWNLOADFILESRESPONSEPACKET_H
