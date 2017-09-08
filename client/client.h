#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QDir>

#include "dropboxpacket.h"

QT_BEGIN_NAMESPACE
class QTcpSocket;
QT_END_NAMESPACE

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QString user, QString path, QObject *parent = 0);
    ~Client();

    void start();

    void sendName();

signals:

    void nameRespReceived();

    void serverFilesRespReceived(QStringList files);

    void filesUploaded();

    void fileDownloaded(QString);

    void allFilesDownloaded();

public slots:
    void localFolderChanged(QString dir);

    void receive();

    void requestServerFiles();

    void processServerFiles(QStringList files);

    void writeFileToLocal(QString file);

    void startMonitoring();

    void uploadNewFiles();

private:

    void sendPacket(PacketType type, void *packet);

private:

    enum ClientState {
        Starting,
        DownloadingFiles,
        SendingFiles,
        Monitoring
    };
    ClientState mState;
    QString mUser;
    QDir mPath;
    QTcpSocket *mTcpSocket;
    QFileSystemWatcher mFileSystemWatcher;
    QStringList mLocalFiles;
    QStringList mNewFiles;
};

#endif // CLIENT_H
