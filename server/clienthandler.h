#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include <QThread>
#include <QQueue>
#include <QTcpSocket>

#include "dropboxpacket.h"
#include "clientworker.h"

class ClientHandler : public QObject
{
    Q_OBJECT

public:
    ClientHandler(qintptr socketDescriptor, QObject *parent);

    void start();

    qintptr socketDescriptor() const;
    void setSocketDescriptor(const qintptr &value);

signals:
    void error(QTcpSocket::SocketError socketError);

    void namePacketReceived();

    void getServerFilesPacketReceived(qint64, QString);

    void uploadFiles(qint64, QString, QStringList);

    void downloadFiles(qint64, QString, QStringList);

public slots:
    void socketConnected();

    void processData();

    void replyToNamePacket();

    void replyToGetServerFiles(QStringList files);

    void replyToUploadFiles(QString status);

    void fileReadyForDownload(QString file);

    void allFilesDownloaded();

private:
    void sendPacket(PacketType type, void *packet);

private:
    qint64 mSocketDescriptor;
    QTcpSocket *mTcpSocket;
    QString mUser;
    QThread *mThread;
    ClientWorker *mWorker;
};

#endif // CLIENTHANDLER_H
