
#include "storagecontroller.h"

StorageController::StorageController(int id, QObject *parent)
    : QObject(parent)
    , mId(id)
    , mStorage(QDir::currentPath()+"/"+QString::number(mId))
    , mTask(NULL)
    , mLastTaskType(StorageWorker::TaskType::Upload)
    , mFileCount(0)
    , mUserFilesCvs(mStorage.absolutePath()+"/storage.info")
{
    printf("%s path: %s\n", __FUNCTION__, mStorage.absolutePath().toStdString().c_str()); fflush(stdout);
    mStorage.mkpath(mStorage.absolutePath());

    mUserFilesCvs.open(QIODevice::ReadOnly | QIODevice::Text);

    while(!mUserFilesCvs.atEnd()){
        QString line = QString::fromUtf8(mUserFilesCvs.readLine()).trimmed();
        QStringList values = line.split("\",\"");
        QString userName = values.at(0);
        QString file = values.at(1);
        mUserFiles[userName.remove("\"")].append(file.remove("\""));
        ++mFileCount;
    }
    mUserFilesCvs.close();
}

StorageController::~StorageController()
{
    printf("%s\n", __FUNCTION__);fflush(stdout);

    workerThread.quit();
    workerThread.wait();
    mUserFilesCvs.close();
}

void StorageController::setTask(const StorageWorker::TaskType &type, const qint64 &clientId, const QString &file)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    mTask = new StorageWorker(type, clientId, file, mStorage.absolutePath());

    mTask->moveToThread(&workerThread);
    connect(this, SIGNAL(operate()), mTask, SLOT(doWork()));
    connect(mTask, SIGNAL(done()), this, SLOT(taskDone()));

    printf("thread start\n");fflush(stdout);
    workerThread.start();
    emit operate();
}

void StorageController::setTask(const StorageTask &task)
{
    setTask(task.type(), task.clientId(), task.file());
}

StorageWorker *StorageController::task() const
{
    return mTask;
}

void StorageController::taskDone()
{
    if(mTask->type() == StorageWorker::Upload){
        emit fileCountChanged(mId, ++mFileCount);
        emit uploadTaskFinished(mId, mTask->clientId(), mTask->file());

        QStringList values = mTask->file().split("/");
        QString userName = values.at(0);
        QString file = values.at(1);
        QString line = "\""+userName+"\",\""+file+"\"\n";
        if(!mUserFilesCvs.isOpen()){
            mUserFilesCvs.open(QIODevice::Append | QIODevice::Text);
        }
        mUserFilesCvs.write(line.toUtf8());
        mUserFilesCvs.flush();
    } else if(mTask->type() == StorageWorker::Download){
        emit downloadTaskFinished(mId, mTask->clientId(), mTask->file());
    }

    mLastTaskType = mTask->type();
    mTask->deleteLater();
    mTask=NULL;
}

quint64 StorageController::fileCount() const
{
    return mFileCount;
}

QMap<QString, QStringList> StorageController::userFiles() const
{
    return mUserFiles;
}

void StorageController::setLastTaskType(const StorageWorker::TaskType &lastTaskType)
{
    mLastTaskType = lastTaskType;
}

int StorageController::id() const
{
    return mId;
}

StorageWorker::TaskType StorageController::lastTaskType() const
{
    return mLastTaskType;
}

