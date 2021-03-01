#include <QString>

#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syslog.h>
#include <sys/resource.h>

#include "program.cpp"

const QString c_logFile = "TestDaemon.log";
#define PID_FILE "/tmp/TestDaemon.pid"

void daemonize();
void signalHandler(int sig);
void logMessage(const QString& message);

int main(int argc, char *argv[])
{
    daemonize();
    prog_main(argc, argv);
    closelog();
}

void daemonize() {
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

    openlog("Daemon test", LOG_PID | LOG_CONS, LOG_DAEMON);

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

    int lFile = open(PID_FILE, O_RDWR|O_CREAT, 0640);

    if (lFile < 0) {
        logMessage("Can't open PID file!");
        exit(EXIT_FAILURE);
    }

    if (lockf(lFile, F_TLOCK, 0) < 0) {
        exit(EXIT_SUCCESS);
    }
    sprintf(str, "%d\n", getpid());
    write(lFile, str, strlen(str));

    signal(SIGCHLD, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGHUP, signalHandler);
    signal(SIGTERM, signalHandler);
}

void signalHandler(int sig) {
    switch (sig) {
        case SIGHUP:
            logMessage("Hangup signal catched!");
            break;
        case SIGTERM:
            logMessage("Terminate signal catched!");
            closelog();
            unlink(PID_FILE);
            exit(EXIT_SUCCESS);
            break;
    }
}

void logMessage(const QString& message) {
    syslog(LOG_INFO, "%s", message.toStdString().c_str());
}
