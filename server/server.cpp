
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
        StorageController* controller = new StorageController(i, this);

        connect(controller, SIGNAL(downloadTaskFinished(int,qint64,QString)), this, SLOT(downloadTaskFinished(int,qint64,QString)), Qt::QueuedConnection);
        connect(controller, SIGNAL(uploadTaskFinished(int,qint64,QString)), this, SLOT(uploadTaskFinished(int,qint64,QString)), Qt::QueuedConnection);

        connect(controller, SIGNAL(fileCountChanged(int,quint64)), this, SLOT(storageFileCountChanged(int,quint64)));
        mStorageControllers.append(controller);
        mStorageDownloadTasks.append(QMap<qint64, QStringList>());
        mCurrentDownloadTasks.append(mStorageDownloadTasks[i].begin());

        mStorageFileCounts.append(controller->fileCount());

        QMap<QString, QStringList> userfiles = controller->userFiles();

        for( QMap<QString, QStringList>::iterator it = userfiles.begin(); it != userfiles.end(); ++it){
            QString user = it.key();
            mUserFiles[user].append(it.value());
            foreach(QString file, it.value()){
                mUserfileStorage[user+"/"+file] = i;
            }
        }
    }
    connect(this, SIGNAL(newTasks()), this, SLOT(assignTasks()), Qt::QueuedConnection);

    mCurrentUploadTask = mUploadTasks.begin();
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

void Server::clientFinished()
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    ClientHandler* handler = (ClientHandler*)this->sender();
    mClients.remove(handler->socketDescriptor());
}

void Server::getServerFilesForUser(qint64 clientSocketDesc, QString user)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    QStringList files;

    files.append(mUserFiles.value(user));

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
        mUserFiles[user].append(file);
        userFiles.append(user+"/"+file);
    }
    bool noTasksBefore = mUploadTasks.isEmpty();

    mUploadTasks.insert(clientSocketDesc,userFiles);

    if(noTasksBefore)
        mCurrentUploadTask = mUploadTasks.begin();

    emit newTasks();
}

void Server::downloadFiles(qint64 clientSocketDesc, QString user, QStringList files)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    foreach (QString file, files) {
        QString userfile = user + "/" + file;
        int storageId = mUserfileStorage.value(userfile, -1);
        if(storageId >= 0){
            bool noTasksBefore = mStorageDownloadTasks[storageId].isEmpty();

            mStorageDownloadTasks[storageId][clientSocketDesc].append(userfile);
            mDownloadTasks[clientSocketDesc].append(userfile);

            if(noTasksBefore)
                mCurrentDownloadTasks[storageId] = mStorageDownloadTasks[storageId].begin();
        } else {
            qDebug() << "requested file not found on server!";
        }
    }
    emit newTasks();
}

void Server::uploadTaskFinished(int storageId, qint64 clientSocketDesc, QString file)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);

    mOngoingUploadTasks[clientSocketDesc].removeOne(file);
    mUserfileStorage.insert(file, storageId);

    if( mUploadTasks.value(clientSocketDesc).isEmpty() &&
            mOngoingUploadTasks[clientSocketDesc].isEmpty() ){
        mOngoingUploadTasks.remove(clientSocketDesc);

        metaObject()->invokeMethod(mClients.value(clientSocketDesc),
                                   "replyToUploadFiles",
                                   Qt::QueuedConnection,
                                   Q_ARG(QString, "OK"));
    }

    emit newTasks();
}

void Server::downloadTaskFinished(int, qint64 clientSocketDesc, QString file)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    mOngoingDownloadTasks[clientSocketDesc].removeOne(file);

    QStringList values = file.split("/");

    metaObject()->invokeMethod(mClients.value(clientSocketDesc),
                               "fileReadyForDownload",
                               Qt::QueuedConnection,
                               Q_ARG(QString, values.at(1)));

    if(mDownloadTasks.value(clientSocketDesc).isEmpty() &&
            mOngoingDownloadTasks[clientSocketDesc].isEmpty()){
        mOngoingDownloadTasks.remove(clientSocketDesc);

        metaObject()->invokeMethod(mClients.value(clientSocketDesc),
                                   "allFilesDownloaded",
                                   Qt::QueuedConnection);
    }

    emit newTasks();
}

void Server::assignTasks()
{
    foreach (StorageController* control, mStorageControllers) {
        int id = control->id();
        if( control->task() == NULL ){
            printf("%s\n", __FUNCTION__);fflush(stdout);
            printf("controller id:%d\n", id);fflush(stdout);

            StorageTask::TaskType nextTask;

            if(mStorageDownloadTasks[id].isEmpty() && mUploadTasks.isEmpty()){
                continue;
            }

            if( control->lastTaskType() == StorageTask::Download ){
                if( !mUploadTasks.isEmpty() ){
                    nextTask = StorageTask::Upload;
                } else {
                    printf("mUploadTasks empty\n");fflush(stdout);
                    nextTask = StorageTask::Download;
                }

            } else if( control->lastTaskType() == StorageTask::Upload ){
                if(!mStorageDownloadTasks[id].isEmpty()){
                    nextTask = StorageTask::Download;
                }else{
                    printf("mStorageDownloadTasks[i] empty\n");fflush(stdout);
                    nextTask = StorageTask::Upload;
                }
            }

            if(nextTask == StorageTask::Upload){
                if(mStorageFileCounts[id] >= mStorageFileCountsMean){
                    printf("too many files on storage, try download\n");fflush(stdout);
                } else {
                    if(mUploadTasks.isEmpty()){
                        printf("no more upload tasks\n");fflush(stdout);
                        continue;
                    }
                    printf("setTask Upload\n");fflush(stdout);
                    qint64 clientSocketDesc = mCurrentUploadTask.key();
                    control->setTask(StorageTask::Upload,
                                     clientSocketDesc,
                                     mCurrentUploadTask.value().first());

                    mOngoingUploadTasks[clientSocketDesc].append(mCurrentUploadTask.value().first());
                    mUploadTasks[clientSocketDesc].removeFirst();

                    if(mUploadTasks[clientSocketDesc].isEmpty()){
                        mCurrentUploadTask = mUploadTasks.erase(mCurrentUploadTask);
                    } else {
                        ++mCurrentUploadTask;
                    }

                    if(mCurrentUploadTask == mUploadTasks.end())
                        mCurrentUploadTask = mUploadTasks.begin();
                }
            }// endof upload task

            if(nextTask == StorageTask::Download){
                if(mStorageDownloadTasks[id].isEmpty() ){
                    printf("no more download tasks\n");fflush(stdout);
                    continue;
                }
                printf("setTask Download\n");fflush(stdout);
                qint64 clientSocketDesc = mCurrentDownloadTasks[id].key();
                control->setTask(StorageTask::Download,
                                 clientSocketDesc,
                                 mCurrentDownloadTasks[id].value().first());

                mOngoingDownloadTasks[clientSocketDesc].append(mCurrentDownloadTasks[id].value().first());
                mDownloadTasks[clientSocketDesc].removeOne(mCurrentDownloadTasks[id].value().first());
                mStorageDownloadTasks[id][clientSocketDesc].removeFirst();

                if(mStorageDownloadTasks[id][clientSocketDesc].isEmpty()){
                    mCurrentDownloadTasks[id] =
                            mStorageDownloadTasks[id].erase(mCurrentDownloadTasks[id]);
                } else {
                    ++mCurrentDownloadTasks[id];
                }

                if(mDownloadTasks[clientSocketDesc].isEmpty()){
                    mDownloadTasks.remove(clientSocketDesc);
                }

                if(mCurrentDownloadTasks[id] == mStorageDownloadTasks[id].end())
                    mCurrentDownloadTasks[id] = mStorageDownloadTasks[id].begin();
            }
        }
    }
}

void Server::storageFileCountChanged(int storageId, quint64 fileCount)
{
    mStorageFileCounts[storageId] = fileCount;
    mStorageFileCountsMean = 1 + std::ceil(std::accumulate(mStorageFileCounts.begin(), mStorageFileCounts.end(), .0) / mStorageFileCounts.size());
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    printf("%s sd: %d\n", __FUNCTION__, socketDescriptor);fflush(stdout);
    ClientHandler *clientHandler = new ClientHandler(socketDescriptor, this);
    connect(clientHandler, SIGNAL(finished()), this, SLOT(clientFinished()));
    connect(clientHandler, SIGNAL(finished()), clientHandler, SLOT(deleteLater()));

    connect(clientHandler, SIGNAL(getServerFilesPacketReceived(qint64, QString)), this, SLOT(getServerFilesForUser(qint64,QString)), Qt::QueuedConnection);
    connect(clientHandler, SIGNAL(uploadFiles(qint64, QString, QStringList)), this, SLOT(uploadFiles(qint64,QString,QStringList)), Qt::QueuedConnection);
    connect(clientHandler, SIGNAL(downloadFiles(qint64, QString, QStringList)), this, SLOT(downloadFiles(qint64,QString,QStringList)), Qt::QueuedConnection);

    clientHandler->start();
    mClients.insert(socketDescriptor, clientHandler);
}
