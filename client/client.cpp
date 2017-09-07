#include "client.h"
#include "dropboxpacket.h"

#include <QTcpSocket>
#include <QFile>

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

    connect(this, SIGNAL(nameRespReceived()),
            this, SLOT(requestServerFiles()), Qt::QueuedConnection);

    connect(this, SIGNAL(serverFilesRespReceived(QStringList)),
            this, SLOT(processServerFiles(QStringList)), Qt::QueuedConnection);

    connect(this, SIGNAL(filesUploaded()),
            this, SLOT(startMonitoring()), Qt::QueuedConnection);

    connect(this, SIGNAL(fileDownloaded(QString)),
            this, SLOT(writeFileToLocal(QString)), Qt::QueuedConnection);

    connect(this, SIGNAL(allFilesDownloaded()),
            this, SLOT(uploadNewFiles()), Qt::QueuedConnection);
}

Client::~Client()
{
    mTcpSocket->abort();
    delete mTcpSocket;
}

void Client::start()
{
    qDebug() << __FUNCTION__;
    mTcpSocket = new QTcpSocket(this);

    connect(mTcpSocket, SIGNAL(readyRead()), this, SLOT(receive()));

    mTcpSocket->connectToHost("localhost", 6543);
    if (mTcpSocket->waitForConnected(1000))
        qDebug() << "Connected!";

    sendName();
}

void Client::sendName()
{
    qDebug() << __FUNCTION__;
    NamePacket namePacket(mUser);
    DropboxPacket::sendPacket(mTcpSocket, Name, &namePacket);
}

void Client::localFolderChanged(QString /*dir*/)
{
    qDebug() << __FUNCTION__;
    QStringList files = mPath.entryList(QDir::Files, QDir::Name);
    QSet<QString> subtraction = files.toSet().subtract( mLocalFiles.toSet() );

    qDebug() << "new files: ";
    for (QSet<QString>::iterator i = subtraction.begin(); i != subtraction.end();++i)
    {
        qDebug() << *i;
        mNewFiles << *i;
    }

    if(mState == Monitoring){
        uploadNewFiles();
        mNewFiles.clear();
    }
}

void Client::receive()
{
    qDebug() << __FUNCTION__;
    QDataStream clientReadStream(mTcpSocket);
    quint32 next_block_size = 0;
    while(true)
    {
        if (!next_block_size)
        {
            if (mTcpSocket->bytesAvailable() < sizeof(quint32))
            {
                break;
            }
            clientReadStream >> next_block_size;
        }

        if (mTcpSocket->bytesAvailable() < next_block_size) {
            break;
        }
        PacketType type;
        clientReadStream >> type;

        qDebug() << "received packet - type: " << type;

        switch(type){
            case NameResp:
            {
                NameResponsePacket nameresp;
                clientReadStream >> nameresp;
                qDebug() << "status: " << nameresp.status();
                emit nameRespReceived();
                break;
            }
            case GetServerFilesResp:
            {
                GetServerFilesResponsePacket resp;
                clientReadStream >> resp;
                qDebug() << "server files count: " << resp.files().count();
                qDebug() << resp.files();

                emit serverFilesRespReceived(resp.files());
                break;
            }
            case UploadFilesResp:
            {
                UploadFilesResponsePacket resp;
                clientReadStream >> resp;
                qDebug() << "files uploaded - status: " << resp.status();

                emit filesUploaded();
                break;
            }
            case DownloadFile:
            {
                DownloadFilePacket resp;
                clientReadStream >> resp;
                qDebug() << "file downloaded: " << resp.file();

                emit fileDownloaded(resp.file());
                break;
            }
            case DownloadFilesResp:
            {
                DownloadFilesResponsePacket resp;
                clientReadStream >> resp;
                qDebug() << "all files downloaded: " << resp.status();

                emit allFilesDownloaded();
                break;
            }

            case DownloadFiles://server only packets
            case UploadFiles:
            case GetServerFiles:
            case Name:
            default:
                qDebug() << "server packet received - well, this should not happen...";
                break;
        }
    }
}

void Client::requestServerFiles()
{
    qDebug() << __FUNCTION__;
    GetServerFilesPacket packet;
    DropboxPacket::sendPacket(mTcpSocket, GetServerFiles, &packet);
}

void Client::processServerFiles(QStringList files)
{
    qDebug() << __FUNCTION__;
    QStringList downloadFiles;
    QSet<QString> serverOnlyFiles = files.toSet().subtract( mLocalFiles.toSet() );
    QSet<QString> localOnlyFiles = mLocalFiles.toSet().subtract( files.toSet() );

    qDebug() << "serverOnlyFiles: ";
    for (QSet<QString>::iterator i = serverOnlyFiles.begin(); i != serverOnlyFiles.end();++i)
    {
        qDebug() << *i;
        downloadFiles << *i;
    }

    qDebug() << "localOnlyFiles: ";
    for (QSet<QString>::iterator i = localOnlyFiles.begin(); i != localOnlyFiles.end();++i)
    {
        qDebug() << *i;
        mNewFiles << *i;
    }

    DownloadFilesPacket packet;
    packet.setFiles(downloadFiles);
    DropboxPacket::sendPacket(mTcpSocket, DownloadFiles, &packet);
    mState = DownloadingFiles;
}

void Client::writeFileToLocal(QString file)
{
    qDebug() << __FUNCTION__;
    QFile localFile(mPath.absolutePath()+"/"+file);
    qDebug() << "file open: " << localFile.open(QIODevice::WriteOnly);
    localFile.close();
}

void Client::startMonitoring()
{
    qDebug() << __FUNCTION__;
    mState = Monitoring;
}

void Client::uploadNewFiles()
{
    qDebug() << __FUNCTION__;
    UploadFilesPacket packet;
    packet.setFiles(mNewFiles);
    DropboxPacket::sendPacket(mTcpSocket, UploadFiles, &packet);
    mState = SendingFiles;
    mNewFiles.clear();
}
