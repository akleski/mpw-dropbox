#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QDir>
#include <QStringList>
#include <QMap>

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

    QMap<QString, QStringList> userFiles() const;

    quint64 fileCount() const;

public slots:
    void taskDone();

signals:
    void uploadTaskFinished(int, qint64, QString);
    void downloadTaskFinished(int, qint64, QString);

    void operate();

    void fileCountChanged(int, quint64);

private:
    QThread workerThread;

    int mId;

    QDir mStorage;

    StorageWorker* mTask;

    StorageWorker::TaskType mLastTaskType;

    quint64 mFileCount;

    QFile mUserFilesCvs;

    QMap<QString, QStringList> mUserFiles;
};

#endif // CONTROLLER_H
