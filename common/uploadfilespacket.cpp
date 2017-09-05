#include "uploadfilespacket.h"

UploadFilesPacket::UploadFilesPacket()
{

}

QStringList UploadFilesPacket::files() const
{
    return mFiles;
}

void UploadFilesPacket::setFiles(const QStringList &files)
{
    mFiles = files;
}

QDataStream &operator<<(QDataStream &out, const UploadFilesPacket &packet)
{
    out << packet.files();
    return out;
}

QDataStream &operator>>(QDataStream &in, UploadFilesPacket &packet)
{
    QStringList files;
    in >> files;
    packet = UploadFilesPacket();
    packet.setFiles(files);
    return in;
}
