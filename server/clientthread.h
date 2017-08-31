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

public slots:
    void processData();

private:
    int socketDescriptor;
    QTcpSocket *mTcpSocket;
};

#endif // CLIENTTHREAD_H
