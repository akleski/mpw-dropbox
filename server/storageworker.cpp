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
                       const QString &file) :
    QObject(),
    StorageTask(type, clientId, file)
{
}

StorageWorker::StorageWorker(const StorageTask &task)
    : QObject(),
      StorageTask(task)
{
}

void StorageWorker::doWork()
{
    printf("%s\n", __FUNCTION__);fflush(stdout);
    if(mType == Upload){
        QFile file(mFile);
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
