#include "daemon.h"
#include "program.cpp"

int main(int argc, char *argv[])
{
    Daemon::pDaemon d = Daemon::getInstance();
    d->Daemonize();
    prog_main(argc, argv);
}
