
#include "storagecontroller.h"

StorageController::StorageController(int id, QObject *parent)
    : QObject(parent)
    , mId(id)
    , mStorage(QDir::currentPath()+"/"+QString::number(mId))
    , mTask(NULL)
    , mLastTaskType(StorageWorker::TaskType::Upload)
{
    printf("%s path: %s\n", __FUNCTION__, mStorage.absolutePath().toStdString().c_str()); fflush(stdout);
    mStorage.mkpath(mStorage.absolutePath());
}

StorageController::~StorageController()
{
    printf("%s\n", __FUNCTION__);fflush(stdout);

    workerThread.quit();
    workerThread.wait();
}

void StorageController::setTask(const StorageWorker::TaskType &type, const qint64 &clientId, const QString &file)
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    mTask = new StorageWorker(type, clientId, file, mStorage.absolutePath());

    mTask->moveToThread(&workerThread);
    connect(&workerThread, SIGNAL(started()), mTask, SLOT(doWork()));
    connect(this, SIGNAL(operate()), mTask, SLOT(doWork()));
    connect(mTask, SIGNAL(done()), this, SLOT(taskDone()));

    printf("thread start\n");fflush(stdout);
    workerThread.start();
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
        emit uploadTaskFinished(mId, mTask->clientId(), mTask->file());
    } else if(mTask->type() == StorageWorker::Download){
        emit downloadTaskFinished(mId, mTask->clientId(), mTask->file());
    }

    mLastTaskType = mTask->type();
    mTask->deleteLater();
    mTask=NULL;
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

