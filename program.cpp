#include <QCoreApplication>
#include <QFile>

#include <iostream>
#include <unistd.h>

#include "daemon.h"
#include "myclass.h"

int prog_main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    Daemon d;
    d.Daemonize();
    MyClass cl;

    int ret = a.exec();

    cl.~MyClass();
    d.~Daemon();

    return ret;
}
