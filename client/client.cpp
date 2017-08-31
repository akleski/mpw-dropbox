#include "client.h"

#include <QTcpSocket>

Client::Client(QString user, QString path, QObject *parent) :
 QObject(parent)
  , mUser(user)
  , mPath(path)
{

}

Client::~Client()
{

}

void Client::start()
{
    mTcpSocket = new QTcpSocket(this);
    mTcpSocket->connectToHost("localhost", 6543);
    if (mTcpSocket->waitForConnected(1000))
        qDebug("Connected!");
    char buf[] = "client data";
    qDebug() << mTcpSocket->write(buf, sizeof(buf));
    qDebug() << "bytes written: "<<mTcpSocket->waitForBytesWritten();
    qDebug() << mTcpSocket->write(buf, sizeof(buf));
    qDebug() << "bytes written: "<<mTcpSocket->waitForBytesWritten();
    qDebug() << mTcpSocket->write(buf, sizeof(buf));
    qDebug() << "bytes written: "<<mTcpSocket->waitForBytesWritten();
}
