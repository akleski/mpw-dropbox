#ifndef STORAGETASK_H
#define STORAGETASK_H

#include <QString>

class StorageTask
{
public:
    enum TaskType{
        Upload,
        Download
    };

    StorageTask();
    StorageTask(const TaskType &type, const qint64 &clientId, const QString &file);

    TaskType type() const;
    void setType(const TaskType &type);

    qint64 clientId() const;
    void setClientId(const qint64 &clientId);

    QString file() const;
    void setFile(const QString &file);

protected:
    TaskType mType;
    qint64 mClientId;
    QString mFile;
};

#endif // STORAGETASK_H
