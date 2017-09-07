#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QThread>
#include <QDir>


class WorkerThread : public QThread
{
    Q_OBJECT

public:
    WorkerThread(QString id, QObject *parent);

    ~WorkerThread();

    void run();

public slots:


signals:

private:
    QString mId;

    QDir mStorage;
};

#endif // WORKERTHREAD_H
