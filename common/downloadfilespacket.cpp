#include "downloadfilespacket.h"

DownloadFilesPacket::DownloadFilesPacket()
{

}

QStringList DownloadFilesPacket::files() const
{
    return mFiles;
}

void DownloadFilesPacket::setFiles(const QStringList &files)
{
    mFiles = files;
}

QDataStream &operator<<(QDataStream &out, const DownloadFilesPacket &packet)
{
    out << packet.files();
    return out;
}

QDataStream &operator>>(QDataStream &in, DownloadFilesPacket &packet)
{
    QStringList files;
    in >> files;
    packet = DownloadFilesPacket();
    packet.setFiles(files);
    return in;
}
