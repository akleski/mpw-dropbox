#ifndef UPLOADFILESPACKET_H
#define UPLOADFILESPACKET_H

#include <QString>
#include <QDataStream>
#include <QStringList>

class UploadFilesPacket
{
public:
    UploadFilesPacket();

    QStringList files() const;
    void setFiles(const QStringList &files);

private:
    QStringList mFiles;
};

QDataStream &operator<<(QDataStream &out, const UploadFilesPacket &packet);
QDataStream &operator>>(QDataStream &in, UploadFilesPacket &packet);


#endif // UPLOADFILESPACKET_H
