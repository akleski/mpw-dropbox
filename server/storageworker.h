#ifndef WORKER_H
#define WORKER_H

#include <qobject.h>
#include <QString>
#include "storagetask.h"

class StorageWorker : public QObject, public StorageTask
{
    Q_OBJECT
public:

    StorageWorker();
    StorageWorker(const TaskType &type, const qint64 &clientId, const QString &file);
    StorageWorker(const StorageTask& task);

public slots:
    void doWork();

signals:
    void done();


};

#endif // WORKER_H
