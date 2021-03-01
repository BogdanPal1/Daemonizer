#include <QCoreApplication>
#include <QFile>

#include <iostream>
#include <unistd.h>

#include "myclass.h"

int prog_main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);

    MyClass cl;

    int ret = a.exec();

    cl.~MyClass();

    return ret;
}
