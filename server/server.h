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
    void clientFinished();

    void getServerFilesForUser(qint64, QString);
    void uploadFiles(qint64, QString, QStringList);
    void downloadFiles(qint64, QString, QStringList);

    void uploadTaskFinished(int, qint64, QString);
    void downloadTaskFinished(int, qint64, QString);

    void assignTasks();

protected:
    virtual void incomingConnection(qintptr socketDescriptor);

private:
    QVector<StorageController*> mStorageControllers;

    QHash<qint64, ClientHandler*> mClients;

    QMap<QString, int> mUserfileStorage;//mapa plik_usera - storage
    QHash<QString, QStringList> mUserFiles;//mapa user - pliki

    QMap<qint64, QStringList> mUploadTasks;//mapa klient (client socket descriptor) - pliki do uploadu
    QMap<qint64, QStringList> mOngoingUploadTasks;//mapa klient - obsługiwany/uploadowany pliki
    QMap<qint64, QStringList>::iterator mCurrentUploadTask;//iterator aktualnego taska

    QMap<qint64, QStringList> mDownloadTasks;//jw
    QVector<QMap<qint64, QStringList>> mStorageDownloadTasks;//poniewaz pliki sa na konkretnych serverach/starage/dyskach to list DL tasków musi byc osobna  dla poszczegolnych starge
    QMap<qint64, QStringList> mOngoingDownloadTasks;//tablica map tasków jw //TODO wywalic vector
    QVector<QMap<qint64, QStringList>::iterator> mCurrentDownloadTasks;//tablica iteratrów jw
};

#endif // SERVER_H
