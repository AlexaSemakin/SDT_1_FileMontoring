#ifndef LOGGER_H
#define LOGGER_H

#include "monitoredfile.h"
#include <QObject>
#include <QFile>

class Logger : public QObject
{
    Q_OBJECT
private:
    QFile *file;

public:
    explicit Logger(QObject *parent = nullptr);

public slots:
    void log(qint32 index, const MonitoredFile &monitoredFile);
};

#endif // LOGGER_H
