#ifndef DOWNLOADFILESPACKET_H
#define DOWNLOADFILESPACKET_H

#include <QStringList>
#include <QDataStream>

class DownloadFilesPacket
{
public:
    DownloadFilesPacket();

    QStringList files() const;
    void setFiles(const QStringList &files);

private:
    QStringList mFiles;
};

QDataStream &operator<<(QDataStream &out, const DownloadFilesPacket &packet);
QDataStream &operator>>(QDataStream &in, DownloadFilesPacket &packet);


#endif // DOWNLOADFILESPACKET_H
