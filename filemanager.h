#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "monitoredfile.h"
#include <QObject>
#include <QVector>

class FileManager : public QObject
{
    Q_OBJECT
private:
    QVector<MonitoredFile> files;
    qint32 search(const QString &path) const;
    FileManager(QObject *parent = nullptr);

public:
    static FileManager& getInstance();
    bool addFile(const QString &path);
    bool removeFile(const QString &path);
    void emitAllStatuses();
    const QVector<MonitoredFile>& list() const;

signals:
    void modified(qint32 index, const MonitoredFile &monitoredFile);
    void changed();
public slots:
    void updateAll();
};

#endif
