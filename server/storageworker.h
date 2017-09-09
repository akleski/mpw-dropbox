#ifndef WORKER_H
#define WORKER_H

#include <qobject.h>
#include <QString>
#include <QThread>
#include "storagetask.h"

class StorageWorker : public QObject, public StorageTask
{
    Q_OBJECT
    QThread workerThread;

public:

    StorageWorker();
    StorageWorker(const TaskType &type, const qint64 &clientId, const QString &file, const QString &path);
    StorageWorker(const StorageTask& task, const QString &path);

public slots:
    void doWork();

signals:
    void done();

private:
    QString mPath;

};

#endif // WORKER_H
