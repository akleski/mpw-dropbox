#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QDir>

#include "storageworker.h"

class  StorageController : public QObject
{
    Q_OBJECT

public:
    StorageController(int id, QObject *parent);

    ~StorageController();

    void setTask(const StorageWorker::TaskType &type, const qint64 &clientId, const QString &file);

    void setTask(const StorageTask &task);

    StorageWorker *task() const;

    StorageWorker::TaskType lastTaskType() const;

    int id() const;

    void setLastTaskType(const StorageWorker::TaskType &lastTaskType);

public slots:
    void taskDone();

signals:
    void uploadTaskFinished(int, qint64, QString);
    void downloadTaskFinished(int, qint64, QString);

    void operate();

private:
    QThread workerThread;

    int mId;

    QDir mStorage;

    StorageWorker* mTask;

    StorageWorker::TaskType mLastTaskType;
};

#endif // CONTROLLER_H
