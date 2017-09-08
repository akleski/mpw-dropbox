
#include "workerthread.h"

WorkerThread::WorkerThread(QString id, QObject *parent)
    : QThread(parent)
    , mId(id)
    , mStorage(QDir::currentPath()+"/"+mId)
{
    printf("%s path: %s\n", __FUNCTION__, mStorage.absolutePath().toStdString().c_str()); fflush(stdout);
    mStorage.mkpath(mStorage.absolutePath());
}

WorkerThread::~WorkerThread()
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
}

void WorkerThread::run()
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    exec();
}

