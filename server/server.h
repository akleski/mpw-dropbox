#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = 0);
    ~Server();

    void start();
signals:

public slots:

protected:
    virtual void incomingConnection(qintptr socketDescriptor);

};

#endif // SERVER_H
