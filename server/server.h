#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QList>
#include "storageworker.h"

class ClientHandler;
class StorageController;

class Server : public QTcpServer
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = 0);
    ~Server();

    void start();
signals:
    void newTasks();

public slots:
    void clientThreadFinished();

    void getServerFilesForUser(qint64, QString);
    void uploadFiles(qint64, QString, QStringList);
    void downloadFiles(qint64, QString, QStringList);

    void uploadTaskFinished(int, qint64, QString);
    void downloadTaskFinished(int, qint64, QString);

    void assignTasks();

protected:
    virtual void incomingConnection(qintptr socketDescriptor);

private:
    QMap<int, StorageController*> mWorkers;

    QHash<qint64, ClientHandler*> mClients;

    QMap<QString, int> mClientFileStorage;
    QHash<QString, QStringList> mClientFiles;

    QMap<QString, QMap<qint64, QStringList>> mUploadTasks;
    QMap<QString, QMap<qint64, QStringList>> mDownloadTasks;
};

#endif // SERVER_H
