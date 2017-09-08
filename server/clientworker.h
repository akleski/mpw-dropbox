#ifndef CLIENTWORKER_H
#define CLIENTWORKER_H

#include <QObject>
#include <QQueue>
#include <QTcpSocket>

class ClientWorker : public QObject
{
    Q_OBJECT
public:
    explicit ClientWorker(QObject *parent = 0);
    ~ClientWorker();

    QQueue<QByteArray> packetsToSend() const;
    void setPacketsToSend(const QQueue<QByteArray> &packetsToSend);

    QTcpSocket *tcpSocket() const;
    void setTcpSocket(QTcpSocket *tcpSocket);

    qint64 socketDescriptor() const;
    void setSocketDescriptor(const qint64 &socketDescriptor);

public slots:
    void process();

signals:
    void finished();
    void error(QString err);
    void connected();

private:
    qint64 mSocketDescriptor;
    QTcpSocket *mTcpSocket;
};

#endif // CLIENTWORKER_H
