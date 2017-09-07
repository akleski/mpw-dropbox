
#include <QDebug>

#include "workerthread.h"

WorkerThread::WorkerThread(QString id, QObject *parent)
    : QThread(parent)
    , mId(id)
    , mStorage(QDir::currentPath()+mId)
{
    qDebug() << __FUNCTION__ << " path: " << mStorage.absolutePath();
    mStorage.mkpath(QDir::currentPath()+mId);
}

WorkerThread::~WorkerThread()
{
    qDebug() << __FUNCTION__;
}

void WorkerThread::run()
{
    qDebug() << __FUNCTION__;
    exec();
}

