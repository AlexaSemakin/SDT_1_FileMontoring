#include "monitoredfile.h"

MonitoredFile::MonitoredFile(const QString &path) : QFileInfo(path)
{
    oldExists = exists();
    oldSize = size();
}

bool MonitoredFile::update()
{
    bool modified = false;
    refresh();

    if (oldExists != exists()) {
        oldExists = exists();
        modified = true;
    }

    qint64 newSize = size();
    if (oldSize != newSize) {
        oldSize = newSize;
        modified = true;
    }

    return modified;
}
