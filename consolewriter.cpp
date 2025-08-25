#include "consolewriter.h"
#include "filemanager.h"
#include <QTextStream>

ConsoleWriter::ConsoleWriter(QObject *parent) : QObject{parent}
{
    SetConsoleTitleW(L"FileManager");
    printHeader();
}

QString ConsoleWriter::sizeToString(qint64 size) const
{
    const char units[] = {'K', 'M', 'G', 'T', 'P', 'E'};
    int i = -1;
    qreal newSize = static_cast<qreal>(size);
    while (newSize >= 1024) { newSize /= 1024; ++i; }
    if (i >= 0) return QString().setNum(newSize, 'f', 1) + " " + units[i] + 'B';
    return QString::number(size) + " B";
}

void ConsoleWriter::clearConsole()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (!GetConsoleScreenBufferInfo(handle, &info)) return;
    DWORD cells = info.dwSize.X * info.dwSize.Y;
    COORD home = {0, 0};
    DWORD written = 0;
    FillConsoleOutputCharacterA(handle, ' ', cells, home, &written);
    FillConsoleOutputAttribute(handle, info.wAttributes, cells, home, &written);
    SetConsoleCursorPosition(handle, home);
}

void ConsoleWriter::printHeader()
{
    QTextStream out(stdout);
    QVector<QString> titles {"index", "Name", "Status", "Size", "Path"};
    out << Qt::left;
    for (int i = 0; i < titles.size() - 1; ++i)
        out << qSetFieldWidth(sizes[i]) << titles[i];
    out << Qt::reset << titles.last() << Qt::endl;
}

void ConsoleWriter::printRow(qint32 index, const MonitoredFile &monitoredFile)
{
    QVector<QString> data {
        QString::number(index),
        monitoredFile.fileName(),
        monitoredFile.exists() ? "exists" : "missing",
        sizeToString(monitoredFile.size()),
        monitoredFile.absoluteFilePath()
    };
    QTextStream out(stdout);
    out << Qt::left;
    for (int i = 0; i < data.size() - 1; ++i)
        out << qSetFieldWidth(sizes[i]) << data[i];
    out << Qt::reset << data.last() << Qt::endl;
}

void ConsoleWriter::write(qint32 index, const MonitoredFile &monitoredFile)
{
    printRow(index, monitoredFile);
}

void ConsoleWriter::refreshAll()
{
    clearConsole();
    printHeader();
    const auto &v = FileManager::getInstance().list();
    for (qint32 i = 0; i < v.size(); ++i)
        printRow(i, v[i]);
}
