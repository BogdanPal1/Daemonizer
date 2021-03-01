#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QTimer>
#include <QFile>
#include <memory>

class MyClass : public QObject
{
    Q_OBJECT
public:
    explicit MyClass(QObject *parent = nullptr);
    ~MyClass();
signals:

public slots:
    void write();
private:
    std::shared_ptr<QTimer> _timer = nullptr;
    std::shared_ptr<QFile> _file = nullptr;
};

#endif // MYCLASS_H
