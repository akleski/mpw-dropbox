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

    void storageFileCountChanged(int storageId, quint64 fileCount);

protected:
    virtual void incomingConnection(qintptr socketDescriptor);

private:
    QVector<StorageController*> mStorageControllers;

    QVector<quint64> mStorageFileCounts;
    quint64 mStorageFileCountsMean;

    QHash<qint64, ClientHandler*> mClients;

    QMap<QString, int> mUserfileStorage;//map userfile - storageId
    QHash<QString, QStringList> mUserFiles;//map user - files

    QMap<qint64, QStringList> mUploadTasks;//map client (client socket descriptor) - upload files
    QMap<qint64, QStringList> mOngoingUploadTasks;//map client - uploading files at this moment
    QMap<qint64, QStringList>::iterator mCurrentUploadTask;//iterator marking current task

    QMap<qint64, QStringList> mDownloadTasks;//see above
    QVector<QMap<qint64, QStringList>> mStorageDownloadTasks;//uploaded files are on specific storagtes, so download task list has to be separate for each storage
    QMap<qint64, QStringList> mOngoingDownloadTasks;//map client - downloading files at this moment
    QVector<QMap<qint64, QStringList>::iterator> mCurrentDownloadTasks;//iterator marking current task
};

#endif // SERVER_H
