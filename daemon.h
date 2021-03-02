#ifndef DAEMON_H
#define DAEMON_H

#include <QString>

#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syslog.h>
#include <sys/resource.h>
#include <memory>



class Daemon
{
public:
    typedef std::unique_ptr<Daemon> pDaemon;

public:

    static pDaemon getInstance();
    Daemon(Daemon& other) = delete;
    Daemon& operator=(Daemon& other) = delete;

    static void Daemonize();

    static void termHandler(int sig);
    static void pauseHandler(int sig);
    static void resumeHandler(int sig);

    static void logMessage(const QString& message);

protected:
    Daemon();
private:
    Daemon(Daemon&& other) = default;
    Daemon& operator=(Daemon&& other) = default;
    static void signalHandlerConfig();
private:

    static pDaemon _daemon;
    static QString _pidFile;
};

#endif // DAEMON_H
