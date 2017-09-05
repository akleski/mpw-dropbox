#ifndef UPLOADFILESRESPONSEPACKET_H
#define UPLOADFILESRESPONSEPACKET_H

#include <QString>
#include <QDataStream>

class UploadFilesResponsePacket
{
public:
    UploadFilesResponsePacket();

    QString status() const;
    void setStatus(const QString &status);

private:
    QString mStatus;
};

QDataStream &operator<<(QDataStream &out, const UploadFilesResponsePacket &packet);
QDataStream &operator>>(QDataStream &in, UploadFilesResponsePacket &packet);

#endif // UPLOADFILESRESPONSEPACKET_H
