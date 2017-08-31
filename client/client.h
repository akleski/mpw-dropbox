#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

QT_BEGIN_NAMESPACE
class QTcpSocket;
QT_END_NAMESPACE

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QString user, QString path, QObject *parent = 0);
    ~Client();

    void start();

signals:

public slots:

private:
    QString mUser;
    QString mPath;
    QTcpSocket *mTcpSocket;
};

#endif // CLIENT_H
