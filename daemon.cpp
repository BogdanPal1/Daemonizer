#include "daemon.h"

int Daemon::_sigHupFd[2];
int Daemon::_sigIntFd[2];
int Daemon::_sigTermFd[2];

Daemon::Daemon(QObject* parent) : QObject(parent)
{
    _pidFile = QString("/tmp/TestDaemon.pid");
    openlog("Daemon test", LOG_PID | LOG_CONS, LOG_DAEMON);

    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, _sigHupFd)) {}
        // log error

    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, _sigTermFd)) {}
        // log error

    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, _sigIntFd)) {}
        // log error

    _snHup = new QSocketNotifier(_sigHupFd[1], QSocketNotifier::Read, this);
    connect(_snHup, &QSocketNotifier::activated, this, &Daemon::handleSigHup);
    _snTerm = new QSocketNotifier(_sigTermFd[1], QSocketNotifier::Read, this);
    connect(_snTerm, &QSocketNotifier::activated, this, &Daemon::handleSigTerm);
    _snInt = new QSocketNotifier(_sigIntFd[1], QSocketNotifier::Read, this);
    connect(_snInt, &QSocketNotifier::activated, this, &Daemon::handleSigInt);
}

Daemon::~Daemon()
{
    delete _snHup;
    delete _snInt;
    delete _snTerm;
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
    struct sigaction hup, term, interrupt;

    hup.sa_handler = Daemon::hupHandler;
    sigemptyset(&hup.sa_mask);
    hup.sa_flags = 0;
    hup.sa_flags |= SA_RESTART;

    sigaction(SIGHUP, &hup, nullptr);

    term.sa_handler = Daemon::termHandler;
    sigemptyset(&term.sa_mask);
    term.sa_flags = 0;
    term.sa_flags |= SA_RESTART;

    sigaction(SIGTERM, &term, nullptr);

    interrupt.sa_handler = Daemon::intHandler;
    sigemptyset(&interrupt.sa_mask);
    interrupt.sa_flags = 0;
    interrupt.sa_flags |= SA_RESTART;

    sigaction(SIGINT, &interrupt, nullptr);

    signal(SIGCHLD, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
}

void Daemon::termHandler(int unusedSig)
{
    qint8 a = 1;
    ::write(_sigTermFd[0], &a, sizeof (a));
}

void Daemon::intHandler(int unusedSig)
{
    qint8 a = 1;
    ::write(_sigIntFd[0], &a, sizeof (a));
}

void Daemon::hupHandler(int unusedSig)
{
    qint8 a = 1;
    ::write(_sigHupFd[0], &a, sizeof (a));
}


void Daemon::pauseHandler(int unusedSig)
{
    //logMessage("Stop signal catched!");
}

void Daemon::resumeHandler(int unusedSig)
{
    //logMessage("Continue signal catched!");
}

void Daemon::handleSigHup()
{
    _snHup->setEnabled(false);
    quint8 tmp;
    ::read(_sigHupFd[1], &tmp, sizeof (tmp));

    // some stuff
    logMessage("Hangup signal catched!");
    closelog();
    unlink(_pidFile.toStdString().c_str());
    exit(EXIT_SUCCESS);

    _snHup->setEnabled(true);
}

void Daemon::handleSigTerm()
{
    _snTerm->setEnabled(false);
    quint8 tmp;
    ::read(_sigTermFd[1], &tmp, sizeof (tmp));

    // some stuff
    logMessage("Terminate signal catched!");
    closelog();
    unlink(_pidFile.toStdString().c_str());
    exit(EXIT_SUCCESS);

    _snTerm->setEnabled(true);
}

void Daemon::handleSigInt()
{
    _snInt->setEnabled(false);
    quint8 tmp;
    ::read(_sigIntFd[1], &tmp, sizeof (tmp));

    // some stuff
    logMessage("Interrupt signal catched!");
    closelog();
    unlink(_pidFile.toStdString().c_str());
    exit(EXIT_SUCCESS);

    _snInt->setEnabled(true);
}

void Daemon::logMessage(const QString &message)
{
    syslog(LOG_INFO, "%s", message.toStdString().c_str());
}


