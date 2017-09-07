#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

class ClientThread : public QThread
{
    Q_OBJECT

public:
    ClientThread(int socketDescriptor, QObject *parent);

    void run();

signals:
    void error(QTcpSocket::SocketError socketError);

    void namePacketReceived();

    void getServerFilesPacketReceived(QString);

    void uploadFiles(QString, QStringList);

    void downloadFiles(QString, QStringList);


public slots:
    void processData();

    void replyToNamePacket();

    void replyToGetServerFiles(QStringList files);

    void replyToUploadFiles(QString status);

    void fileReadyForDownload(QString file);

    void allFilesDownloaded();

private:
    int socketDescriptor;
    QTcpSocket *mTcpSocket;
    QString mUser;
};

#endif // CLIENTTHREAD_H
