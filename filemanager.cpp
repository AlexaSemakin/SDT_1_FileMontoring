#include "filemanager.h"

FileManager::FileManager(QObject *parent) : QObject{parent} {}

FileManager& FileManager::getInstance()
{
    static FileManager instance;
    return instance;
}

qint32 FileManager::search(const QString &path) const
{
    QFileInfo fi(path);
    for (qint32 i = 0; i < files.size(); ++i)
        if (files[i].absoluteFilePath() == fi.absoluteFilePath())
            return i;
    return -1;
}

bool FileManager::addFile(const QString &path)
{
    if (search(path) >= 0) return false;
    files.append(MonitoredFile(path));
    return true;
}

bool FileManager::removeFile(const QString &path)
{
    qint32 idx = search(path);
    if (idx < 0) return false;
    files.removeAt(idx);
    return true;
}

void FileManager::emitAllStatuses()
{
    for (qint32 i = 0; i < files.size(); ++i)
        emit modified(i, files[i]);
}

const QVector<MonitoredFile>& FileManager::list() const
{
    return files;
}

void FileManager::updateAll()
{
    bool anyChanged = false;
    for (qint32 i = 0; i < files.size(); ++i) {
        if (files[i].update()) {
            anyChanged = true;
            emit modified(i, files[i]); // пишет в лог конкретное изменение
        }
    }
    if (anyChanged)
        emit changed(); // один раз за цикл — для полной перерисовки
}
