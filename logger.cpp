#include "logger.h"
#include <QTextStream>
#include <QDateTime>

Logger::Logger(QObject *parent) : QObject{parent}
{
    file = new QFile("Logs.txt", this);
    if (!file->exists())
        file->open(QIODevice::WriteOnly);
    file->close();
}

void Logger::log(qint32 index, const MonitoredFile &monitoredFile)
{
    if (!file->open(QIODevice::Append | QIODevice::Text))
        return;

    QTextStream out(file);
    out << index << ' '
        << (monitoredFile.exists() ? "1" : "0") << ' '
        << monitoredFile.size() << ' '
        << monitoredFile.absoluteFilePath() << ' '
        << QDateTime::currentDateTime().toString("dd.MM.yy hh:mm:ss.zzz")
        << Qt::endl;

    file->close();
}
