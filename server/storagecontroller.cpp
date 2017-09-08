
#include "storagecontroller.h"

StorageController::StorageController(int id, QObject *parent)
    : QObject(parent)
    , mId(id)
    , mStorage(QDir::currentPath()+"/"+QString::number(mId))
    , mLastTaskType(StorageWorker::TaskType::Upload)
{
    printf("%s path: %s\n", __FUNCTION__, mStorage.absolutePath().toStdString().c_str()); fflush(stdout);
    mStorage.mkpath(mStorage.absolutePath());
    mThread = new QThread(this);
}

StorageController::~StorageController()
{
    printf("%s\n", __FUNCTION__);fflush(stdout);

    mThread->quit();
    mThread->wait();
    mThread->deleteLater();
}

void StorageController::setTask(const StorageWorker::TaskType &type, const qint64 &clientId, const QString &file)
{
    mTask = new StorageWorker(type, clientId, file);

    mTask->moveToThread(mThread);
    connect(this, &StorageController::operate, mTask, &StorageWorker::doWork);
    connect(mTask, &StorageWorker::done, this, &StorageController::taskDone);
    mThread->start();
}

void StorageController::setTask(const StorageTask &task)
{
    setTask(task.type(), task.clientId(), task.file());
}

void StorageController::taskDone()
{
    if(mTask->type() == StorageWorker::Upload){
        emit uploadTaskFinished(mId, mTask->clientId(), mTask->file());
    } else if(mTask->type() == StorageWorker::Download){
        emit downloadTaskFinished(mId, mTask->clientId(), mTask->file());
    }

    mLastTaskType = mTask->type();
    mTask->deleteLater();
    mTask=NULL;
}

