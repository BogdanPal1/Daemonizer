#include "daemon.h"

Daemon::pDaemon Daemon::_daemon = nullptr;
QString Daemon::_pidFile = "";

Daemon::pDaemon Daemon::getInstance()
{
    if (_daemon == nullptr)
        _daemon = pDaemon{new Daemon()};
    return std::move(_daemon);
}

Daemon::Daemon()
{
    _pidFile = QString("/tmp/TestDaemon.pid");
    openlog("Daemon test", LOG_PID | LOG_CONS, LOG_DAEMON);
}

void Daemon::Daemonize()
{
    pid_t pid, sid;
    struct rlimit flim;
    char str[10];

    if (getppid() == 1) {
        return;
    }

    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    sid = setsid();
    if (sid < 0) {
        logMessage("Can't set session ID!");
        exit(EXIT_FAILURE);
    }

    getrlimit(RLIMIT_NOFILE, &flim);
    for (int i = 0; i < flim.rlim_max; ++i) {
        close(i);
    }

    int i = open("/dev/null", O_RDWR);
    dup(i);
    dup(i);

    umask(0);

    if (chdir("/") < 0) {
        logMessage("Can't change directory to root!");
        exit(EXIT_FAILURE);
    }

    int lFile = open(_pidFile.toStdString().c_str(), O_RDWR|O_CREAT, 0640);

    if (lFile < 0) {
        logMessage("Can't open PID file!");
        exit(EXIT_FAILURE);
    }

    if (lockf(lFile, F_TLOCK, 0) < 0) {
        exit(EXIT_SUCCESS);
    }
    sprintf(str, "%d\n", getpid());
    write(lFile, str, strlen(str));

    signalHandlerConfig();

    logMessage("Daemon started!");
}

void Daemon::signalHandlerConfig()
{
    signal(SIGCHLD, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTERM, termHandler);
    signal(SIGINT, termHandler);
    signal(SIGTSTP, pauseHandler);
    signal(SIGCONT, resumeHandler);
}

void Daemon::termHandler(int sig)
{
    switch (sig) {
        case SIGTERM:
            logMessage("Terminate signal catched!");
            closelog();
            unlink(_pidFile.toStdString().c_str());
            exit(EXIT_SUCCESS);
            break;
        case SIGINT:
            logMessage("Interrupt signal catched!");
            closelog();
            unlink(_pidFile.toStdString().c_str());
            exit(EXIT_SUCCESS);
            break;
    }
}

void Daemon::pauseHandler(int sig)
{
    logMessage("Stop signal catched!");
}

void Daemon::resumeHandler(int sig)
{
    logMessage("Continue signal catched!");
}

void Daemon::logMessage(const QString &message)
{
    syslog(LOG_INFO, "%s", message.toStdString().c_str());
}
