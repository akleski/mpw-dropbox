
#include <QDebug>
#include <QCoreApplication>
#include <QCommandLineParser>

#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCoreApplication::setApplicationName("dropboxcli");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Dropbox client");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption userOption(QStringList() << "u" << "user",
            QCoreApplication::translate("main", "User name."),
            QCoreApplication::translate("main", "user"));
    parser.addOption(userOption);

    QCommandLineOption directoryOption(QStringList() << "d" << "dir",
            QCoreApplication::translate("main", "Sync all files from <directory> to Dropbox."),
            QCoreApplication::translate("main", "directory"));
    parser.addOption(directoryOption);

    // Process the actual command line arguments given by the user
    parser.process(a);

    Client cli(parser.value(userOption), parser.value(directoryOption));
    cli.start();

    return 0;//a.exec();
}
