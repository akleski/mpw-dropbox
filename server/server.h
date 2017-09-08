#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QList>

class ClientHandler;
class WorkerThread;

class Server : public QTcpServer
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = 0);
    ~Server();

    void start();
signals:

public slots:

    void clientThreadFinished();

    void getServerFilesForUser(qint64, QString);
    void uploadFiles(qint64, QString, QStringList);
    void downloadFiles(qint64, QString, QStringList);

protected:
    virtual void incomingConnection(qintptr socketDescriptor);

private:
    QList<WorkerThread*> mWorkers;

    QHash<qint64, ClientHandler*> mClientThreads;
};

#endif // SERVER_H
