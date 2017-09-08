#include "storagetask.h"

StorageTask::StorageTask()
{

}

StorageTask::StorageTask(const StorageTask::TaskType &type,
                         const qint64 &clientId,
                         const QString &file) :
    mType(type),
    mClientId(clientId),
    mFile(file)
{

}

StorageTask::TaskType StorageTask::type() const
{
    return mType;
}

void StorageTask::setType(const TaskType &type)
{
    mType = type;
}

qint64 StorageTask::clientId() const
{
    return mClientId;
}

void StorageTask::setClientId(const qint64 &clientId)
{
    mClientId = clientId;
}

QString StorageTask::file() const
{
    return mFile;
}

void StorageTask::setFile(const QString &file)
{
    mFile = file;
}
