#include "filemanager.h"
#include "consolewriter.h"
#include "logger.h"
#include <QCoreApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTimer timer;
    ConsoleWriter consoleWriter;
    Logger logger;

    QObject::connect(&timer, &QTimer::timeout,
                     &FileManager::getInstance(), &FileManager::updateAll);

    QObject::connect(&FileManager::getInstance(), &FileManager::modified,
                     &logger, &Logger::log);

    QObject::connect(&FileManager::getInstance(), &FileManager::changed,
                     &consoleWriter, &ConsoleWriter::refreshAll);

    FileManager& fm = FileManager::getInstance();
    fm.addFile("resources/file1.txt");
    fm.addFile("resources/file2.txt");
    fm.addFile("resources/file3.txt");

    consoleWriter.refreshAll();  // начальный вывод один раз

    timer.start(1000);
    return a.exec();
}
