#ifndef CONSOLEWRITER_H
#define CONSOLEWRITER_H

#include "monitoredfile.h"
#include <QObject>
#include <QVector>
#include <windows.h>

class ConsoleWriter : public QObject
{
    Q_OBJECT
private:
    QVector<qint32> sizes {6, 18, 12, 12};
    HANDLE handle {GetStdHandle(STD_OUTPUT_HANDLE)};
    void clearConsole();
    void printHeader();
    void printRow(qint32 index, const MonitoredFile &monitoredFile);

public:
    explicit ConsoleWriter(QObject *parent = nullptr);
    QString sizeToString(qint64 size) const;

public slots:
    void write(qint32 index, const MonitoredFile &monitoredFile);
    void refreshAll();
};

#endif // CONSOLEWRITER_H
