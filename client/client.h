#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QDir>

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

public slots:
    void localFolderChanged(QString dir);

    void receive();

private:

    enum ClientState {
        Starting,
        SendingFiles,
        DownloadingFiles,
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
