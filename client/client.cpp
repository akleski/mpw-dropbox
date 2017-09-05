#include "client.h"
#include "dropboxpacket.h"

#include <QTcpSocket>

Client::Client(QString user, QString path, QObject *parent) :
 QObject(parent)
  , mState(Starting)
  , mUser(user)
  , mPath(path)
  , mFileSystemWatcher(this)
{
    connect(&mFileSystemWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(localFolderChanged(QString)));
    mFileSystemWatcher.addPath(mPath.absolutePath());
    mLocalFiles = mPath.entryList(QDir::Files, QDir::Name);
}

Client::~Client()
{
    mTcpSocket->abort();
    delete mTcpSocket;
}

void Client::start()
{
    mTcpSocket = new QTcpSocket(this);

    connect(mTcpSocket, SIGNAL(readyRead()), this, SLOT(receive()));

    mTcpSocket->connectToHost("localhost", 6543);
    if (mTcpSocket->waitForConnected(1000))
        qDebug("Connected!");
}

void Client::sendName()
{
    QByteArray block;
    QDataStream sendStream(&block, QIODevice::ReadWrite);

    sendStream << quint32(0) //placeholder for size
               << PacketType::Name; //packet type

    NamePacket namePacket(mUser);
    sendStream << namePacket; //packet

    //update size
    sendStream.device()->seek(0);
    sendStream << (quint32)(block.size() - sizeof(quint32));

    qDebug() << "sending name : " << mTcpSocket->write(block);
}

void Client::localFolderChanged(QString /*dir*/)
{
    QStringList files = mPath.entryList(QDir::Files, QDir::Name);
    QSet<QString> subtraction = files.toSet().subtract( mLocalFiles.toSet() );

    qDebug() << "localFolderChanged - new files: ";
    for (QSet<QString>::iterator i = subtraction.begin(); i != subtraction.end();++i)
    {
        qDebug() << *i;
        mNewFiles << *i;
    }

    if(mState == Monitoring){
        //send file to server
        mNewFiles.clear();
    }
}
