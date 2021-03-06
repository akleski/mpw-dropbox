
#include <QTcpSocket>
#include <QFile>
#include <QHostAddress>

#include "client.h"
#include "common.h"

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

    connect(this, SIGNAL(fileDownloaded(QString)),
            this, SLOT(writeFileToLocal(QString)), Qt::QueuedConnection);

    connect(this, SIGNAL(allFilesDownloaded()),
            this, SLOT(uploadNewFiles()), Qt::QueuedConnection);

    connect(this, SIGNAL(filesUploaded()),
            this, SLOT(startMonitoring()), Qt::QueuedConnection);
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

    connect(mTcpSocket, SIGNAL(readyRead()), this, SLOT(receive()), Qt::DirectConnection);

    mTcpSocket->connectToHost(QHostAddress(DROPBOX_SERVER_ADDRESS), 6543);
    if (mTcpSocket->waitForConnected(1000))
        qDebug() << "Connected!";

    sendName();
}

void Client::sendName()
{
    qDebug() << __FUNCTION__;
    NamePacket namePacket(mUser);
    sendPacket(Name, &namePacket);
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

    if(mState == Monitoring && !mNewFiles.isEmpty()){
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

        qDebug() << "received packet - type: " << getTextForPacketType(type);

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
                qDebug() << "server files count: " << resp.files().toSet().count();//server contains duplicated files
                qDebug() << resp.files().toSet();//temporary solution to mask the problem using toSet()


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
    sendPacket(GetServerFiles, &packet);
}

void Client::processServerFiles(QStringList files)
{
    qDebug() << __FUNCTION__;
    QStringList downloadFiles;
    //set arithmetic instead of for loops
    QSet<QString> serverOnlyFiles = files.toSet().subtract( mLocalFiles.toSet() ); //files to be donwloaded
    QSet<QString> localOnlyFiles = mLocalFiles.toSet().subtract( files.toSet() );//files to be uploaded

    qDebug() << "serverOnlyFiles: ";
    for (QSet<QString>::iterator i = serverOnlyFiles.begin(); i != serverOnlyFiles.end();++i)
    {
        qDebug() << *i;
        downloadFiles << *i;
    }

    qDebug() << "localOnlyFiles: " << localOnlyFiles.count();
    for (QSet<QString>::iterator i = localOnlyFiles.begin(); i != localOnlyFiles.end();++i)
    {
        qDebug() << *i;
        mNewFiles << *i;
    }

    if(!downloadFiles.isEmpty()){
        qDebug() << "DownloadFilesPacket";
        DownloadFilesPacket packet;
        packet.setFiles(downloadFiles);
        qDebug() << "sendPacket";
        sendPacket(DownloadFiles, &packet);
        mState = DownloadingFiles;
    } else {
        uploadNewFiles();
    }
}

void Client::writeFileToLocal(QString file)
{
    qDebug() << __FUNCTION__;
    mLocalFiles.append(file);
    QFile localFile(mPath.absolutePath()+"/"+file);
    localFile.open(QIODevice::WriteOnly);
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
    if(!mNewFiles.isEmpty()){
        UploadFilesPacket packet;
        packet.setFiles(mNewFiles);
        sendPacket(UploadFiles, &packet);
        mState = SendingFiles;
        mNewFiles.clear();
    } else {
        startMonitoring();
    }
}

void Client::sendPacket(PacketType type, void *packet)
{
    QByteArray block;
    QDataStream sendStream(&block, QIODevice::ReadWrite);

    sendStream << quint32(0) //placeholder for size
               << type; //packet type

    switch(type)
    {
    case Name:
    {
        NamePacket* obj = static_cast<NamePacket*>(packet);
        sendStream << (*obj);
        break;
    }
    case NameResp:
    {
        NameResponsePacket* obj = static_cast<NameResponsePacket*>(packet);
        sendStream << (*obj);
        break;
    }
    case GetServerFiles:
    {
        GetServerFilesPacket* obj = static_cast<GetServerFilesPacket*>(packet);
        sendStream << (*obj);
        break;
    }
    case GetServerFilesResp:
    {
        GetServerFilesResponsePacket* obj =
                static_cast<GetServerFilesResponsePacket*>(packet);
        sendStream << (*obj);
        break;
    }
    case UploadFiles:
    {
        UploadFilesPacket* obj = static_cast<UploadFilesPacket*>(packet);
        sendStream << (*obj);
        break;
    }
    case UploadFilesResp:
    {
        UploadFilesResponsePacket* obj =
                static_cast<UploadFilesResponsePacket*>(packet);
        sendStream << (*obj);
        break;
    }
    case DownloadFiles:
    {
        DownloadFilesPacket* obj = static_cast<DownloadFilesPacket*>(packet);
        sendStream << (*obj);
        break;
    }
    case DownloadFile:
    {
        DownloadFilePacket* obj = static_cast<DownloadFilePacket*>(packet);
        sendStream << (*obj);
        break;
    }
    case DownloadFilesResp:
    {
        DownloadFilesResponsePacket* obj =
                static_cast<DownloadFilesResponsePacket*>(packet);
        sendStream << (*obj);
        break;
    }
    }

    //update size
    sendStream.device()->seek(0);//poczatek gdzie jest size packietu, placeholder
    sendStream << (quint32)(block.size() - sizeof(quint32));

    qint64 ret = mTcpSocket->write(block);
    mTcpSocket->flush();
    printf("send packet type: %s, bytes sent: %lld\n", getTextForPacketType(type), ret);fflush(stdout);
}
