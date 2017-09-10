#include "storageworker.h"

#include <unistd.h>
#include <QDir>
#include <QFile>
#include <QFileInfo>

StorageWorker::StorageWorker()
{
}

StorageWorker::StorageWorker(const StorageWorker::TaskType &type,
                       const qint64 &clientId,
                       const QString &file,
                       const QString &path) :
    QObject(),
    StorageTask(type, clientId, file),
    mPath(path)
{
}

StorageWorker::StorageWorker(const StorageTask &task, const QString &path)
    : QObject(),
      StorageTask(task),
      mPath(path)
{
}

void StorageWorker::doWork()
{
    printf("%s - file: %s\n", __FUNCTION__, mFile.toStdString().c_str());fflush(stdout);
    if(mType == Upload){
        QFile file(mPath+"/"+mFile);
        QFileInfo fileInfo(file);
        QDir fileDir = fileInfo.absoluteDir();
        if(!fileDir.exists()){
            printf("create fileDir %s\n", mFile.toStdString().c_str());fflush(stdout);
            fileDir.mkdir(fileInfo.absolutePath());
        }
        file.open(QIODevice::WriteOnly);
        file.close();
    }
    sleep(qrand() % 14 + 1);
    emit done();
}
