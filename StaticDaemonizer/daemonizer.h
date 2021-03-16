#ifndef DAEMONIZER_H
#define DAEMONIZER_H

#include <QObject>
#include <QString>
#include <QSocketNotifier>

#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/resource.h>

/*!
 * \brief The Daemon class
 */
class Daemon : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief Daemon Basic constructor.
     * \param parent
     */
    Daemon(QObject* parent = nullptr);
    Daemon(Daemon& other) = delete;
    Daemon& operator=(Daemon& other) = delete;
    Daemon(Daemon&& other) = delete;
    Daemon& operator=(Daemon&& other) = delete;

    /*!
     * \brief Destructor
     */
    ~Daemon();

    /*!
     * \brief daemonize Main method of class. Use for daemonisation.
     */
    void daemonize();

    // Unix signal handlers
    /*!
     * \brief termHandler Handler of UNIX SIGTERM signal.
     * \param sig Number of UNIX signal.
     */
    static void termHandler(int sig);

    /*!
     * \brief intHandler Handler of UNIX SIGINT signal.
     * \param sig Number of UNIX signal.
     */
    static void intHandler(int sig);

    /*!
     * \brief hupHandler Handler of UNIX SIGHUP signal.
     * \param sig Number of UNIX signal.
     */
    static void hupHandler(int sig);

signals:
    /*!
     * \brief You can use this signals for bounding with slots from another Qt object.
     */

    /*!
     * \brief sigHup
     */
    void sigHup();

    /*!
     * \brief sigTerm
     */
    void sigTerm();

    /*!
     * \brief sigInt
     */
    void sigInt();

public slots:
    /*!
     * \brief handleSigHup Handler of SIGHUP signal which can work with Qt objects.
     */
    void handleSigHup();

    /*!
     * \brief handleSigTerm Handler of SIGTERM signal which can work with Qt objects.
     */
    void handleSigTerm();

    /*!
     * \brief handleSigInt Handler of SIGINT signal which can work with Qt objects.
     */
    void handleSigInt();

private:
    /*!
     * \brief signalHandlerConfig Method that configure signal handlers.
     */
    static void signalHandlerConfig();

private:
    QString _pidFile; //!< Name of file with process ID.
    static int _sigHupFd[2]; //!< File descriptor for HUP signal.
    static int _sigTermFd[2]; //!< File descriptor for TERM signal.
    static int _sigIntFd[2]; //!< File descriptor for INT signal.
    QSocketNotifier* _snHup = nullptr; //!< Socket notifier for HUP signal.
    QSocketNotifier* _snTerm = nullptr; //!< Socket notifier for TERM signal.
    QSocketNotifier* _snInt = nullptr; //!< Socket notifier for INT signal.
};

#endif // DAEMONIZER_H
