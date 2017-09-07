#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QList>

class ClientThread;
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

protected:
    virtual void incomingConnection(qintptr socketDescriptor);

private:
    QList<WorkerThread*> mWorkers;

    QList<ClientThread*> mClientThreads;
};

#endif // SERVER_H
