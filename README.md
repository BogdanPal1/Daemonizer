# Daemonizer
**To build libraries, Qt must be installed on your machine.**

With this project you can make your Qt project work like UNIX daemon.

At this moment the daemon can handle 3 UNIX signals:
* SIGTERM
* SIGINT 
* SIGHUP

If you want to use static linking than go to StaticDaemonizer, otherwise
if you want to use dynamic linking go to DynamicDaemonizer.
