
#include <QTcpServer>
#include <QCoreApplication>
#include <unistd.h>

#include "server.h"
#include "clienthandler.h"
#include "common.h"
#include "storagecontroller.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    for(int i = 0; i < 5; ++i)
    {
        StorageController* worker = new StorageController(i, this);
        mWorkers.insert(i, worker);
        connect(worker, SIGNAL(downloadTaskFinished(int,qint64,QString)), this, SLOT(downloadTaskFinished(int,qint64,QString)), Qt::QueuedConnection);
        connect(worker, SIGNAL(uploadTaskFinished(int,qint64,QString)), this, SLOT(uploadTaskFinished(int,qint64,QString)), Qt::QueuedConnection);
    }
    connect(this, SIGNAL(newTasks()), this, SLOT(assignTasks()), Qt::QueuedConnection);
}

Server::~Server()
{
    printf("%s\n", __FUNCTION__);fflush(stdout);

}

void Server::start()
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    if(!listen(QHostAddress(DROPBOX_SERVER_ADDRESS), 6543))
    {
        printf("Unable to start the server: %s\n",errorString().toStdString().c_str());fflush(stdout);
        QCoreApplication::exit();
        return;
    }
}

void Server::clientThreadFinished()
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    ClientHandler* thread = (ClientHandler*)this->sender();
    mClients.remove(thread->socketDescriptor());
}

void Server::getServerFilesForUser(qint64 clientSocketDesc, QString user)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    QStringList files;

    files.append(mClientFiles.value(user));

    metaObject()->invokeMethod(mClients.value(clientSocketDesc),
                               "replyToGetServerFiles",
                               Qt::QueuedConnection,
                               Q_ARG(QStringList, files));
}

void Server::uploadFiles(qint64 clientSocketDesc, QString user, QStringList files)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    QStringList userFiles;
    foreach (QString file, files) {
        userFiles.append(user+"/"+file);
    }
    mUploadTasks[user].insert(clientSocketDesc,userFiles);

    emit newTasks();
}

void Server::downloadFiles(qint64 clientSocketDesc, QString user, QStringList files)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);

    foreach (QString file, files) {
        QString userfile = user + "/" + file;
        int storageId = mClientFileStorage.value(userfile, -1);
        if(storageId >= 0){
            mDownloadTasks[user][clientSocketDesc].append(userfile);
        } else {
            qDebug() << "requested file not found on server!";
        }
    }
    emit newTasks();
}

void Server::uploadTaskFinished(int storageId, qint64 clientSocketDesc, QString file)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    QString user = mClients.value(clientSocketDesc)->getUser();
    mUploadTasks[user][clientSocketDesc].removeOne(file);
    mClientFiles[user].append(file);
    mClientFileStorage.insert(user+"/"+file, storageId );

    if( mUploadTasks.value(user).value(clientSocketDesc).isEmpty() ){

        metaObject()->invokeMethod(mClients.value(clientSocketDesc),
                                   "replyToUploadFiles",
                                   Qt::QueuedConnection,
                                   Q_ARG(QString, "OK"));
    }

    emit newTasks();
}

void Server::downloadTaskFinished(int , qint64 clientSocketDesc, QString file)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    QString user = mClients.value(clientSocketDesc)->getUser();
    mDownloadTasks[user][clientSocketDesc].removeOne(file);

    metaObject()->invokeMethod(mClients.value(clientSocketDesc),
                               "fileReadyForDownload",
                               Qt::QueuedConnection,
                               Q_ARG(QString, file));

    if(mDownloadTasks.value(user).value(clientSocketDesc).isEmpty()){
        metaObject()->invokeMethod(mClients.value(clientSocketDesc),
                                   "allFilesDownloaded",
                                   Qt::QueuedConnection);
    }

}

void Server::assignTasks()
{

}

void Server::incomingConnection(qintptr socketDescriptor)
{
    printf("%s sd: %d\n", __FUNCTION__, socketDescriptor);fflush(stdout);
    ClientHandler *thread = new ClientHandler(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), this, SLOT(clientThreadFinished()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    connect(thread, SIGNAL(getServerFilesPacketReceived(qint64, QString)), this, SLOT(getServerFilesForUser(qint64,QString)), Qt::QueuedConnection);
    connect(thread, SIGNAL(uploadFiles(qint64, QString, QStringList)), this, SLOT(uploadFiles(qint64,QString,QStringList)), Qt::QueuedConnection);
    connect(thread, SIGNAL(downloadFiles(qint64, QString, QStringList)), this, SLOT(downloadFiles(qint64,QString,QStringList)), Qt::QueuedConnection);

    thread->start();
    mClients.insert(socketDescriptor, thread);
}
