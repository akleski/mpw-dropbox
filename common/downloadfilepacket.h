#ifndef DOWNLOADFILEPACKET_H
#define DOWNLOADFILEPACKET_H

#include <QString>
#include <QDataStream>

class DownloadFilePacket
{
public:
    DownloadFilePacket();

    QString file() const;
    void setFile(const QString &file);

private:
    QString mFile;
};

QDataStream &operator<<(QDataStream &out, const DownloadFilePacket &packet);
QDataStream &operator>>(QDataStream &in, DownloadFilePacket &packet);

#endif // DOWNLOADFILEPACKET_H
