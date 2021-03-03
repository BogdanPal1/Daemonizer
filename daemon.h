#ifndef DAEMON_H
#define DAEMON_H

#include <QObject>
#include <QString>
#include <QSocketNotifier>

#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syslog.h>
#include <sys/resource.h>
#include <memory>


class Daemon : public QObject
{
    Q_OBJECT
public:
    typedef std::unique_ptr<Daemon> pDaemon;

public:

    Daemon();
    Daemon(Daemon& other) = delete;
    Daemon& operator=(Daemon& other) = delete;
    Daemon(Daemon&& other) = delete;
    Daemon& operator=(Daemon&& other) = delete;
    ~Daemon();

    void Daemonize();

    // Unix signal handlers
    static void termHandler(int sig);
    static void intHandler(int sig);
    static void pauseHandler(int sig);
    static void resumeHandler(int sig);

    void logMessage(const QString& message);

public slots:
    // Qt signal handlers
    void handleSigHup();
    void handleSigTerm();
    void handleSigInt();

private:

    static void signalHandlerConfig();
private:

    pDaemon _daemon; //!< Unique pointer to Daemon
    QString _pidFile; //!< Name of file with process ID
    static int _sigHupFd[2]; //!< File descriptor for HUP signal
    static int _sigTermFd[2]; //!< File descriptor for TERM signal
    static int _sigIntFd[2]; //!< File descriptor for INT signal
    QSocketNotifier* _snHup = nullptr; //!< Socket notifier for HUP signal
    QSocketNotifier* _snTerm = nullptr; //!< Socket notifier for TERM signal
    QSocketNotifier* _snInt = nullptr; //!< Socket notifier for INT signal
};

#endif // DAEMON_H
