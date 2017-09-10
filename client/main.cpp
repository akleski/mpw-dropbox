
#include <QDir>
#include <QDebug>
#include <QCoreApplication>
#include <QCommandLineParser>

#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

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
    parser.process(app);

    QDir dir(parser.value(directoryOption));
    if(!dir.exists())    {
        qDebug() << "dir ("<<dir.absolutePath()<<") doesnt exists!";
        return 0;
    }

    if(parser.value(userOption).isEmpty()){
        qDebug() << "username cannot be empty!";
        return 0;
    }
    Client cli(parser.value(userOption), dir.absolutePath());
    cli.start();

    return app.exec();
}
