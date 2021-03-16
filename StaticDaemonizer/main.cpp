#include <QCoreApplication>
#include "daemon.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Daemon d;
    d.daemonize();

    // Make some great stuff here!

    return a.exec();
}
