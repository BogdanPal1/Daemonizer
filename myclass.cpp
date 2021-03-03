#include "myclass.h"

MyClass::MyClass(QObject *parent) : QObject(parent)
{
    _timer = std::make_shared<QTimer>(this);
    _file = std::make_shared<QFile>("/home/daemontext.txt", this);

    connect(_timer.get(), &QTimer::timeout, this, &MyClass::write);
    _timer->start(5000);
}

MyClass::~MyClass()
{
    if (_file->isOpen()) {
        _file->close();
    }
    _file->remove("/home/daemontext.txt");
}

void MyClass::write()
{
    _file->open(QFile::Append|QFile::Text);
    _file->write("Hello from Daemon\n");
    _file->close();
}
