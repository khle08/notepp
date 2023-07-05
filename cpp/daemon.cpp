
/*
1. Daemon process works as a long running service in background
2. They have no controlling tty ie User cannot access the Daemon process from the terminal
3. Daemon processes are used to do the recursive tasks and starts when the system boots up until the system is shutdown
4. They can be started using the /etc/init.d/ scripts on system boots.
5. There may be the configuration file associated with the daemon in /etc/
6. We can log the errors in file/syslog for debugging and troubleshooting purpose
7. There are many daemon processes used by the linux like httpd, sshd, syslogd etc


Steps:
1. fork() and let the parent exit
2. Create a new session
3. Ignore the signals
4. fork() again so that PID != SID
5. Set permission for the files created by daemon
6. Change the ??? to the root directory
7. Close all open file descriptors of the process
8. Logging for debugging and info
 */


#include <string>
#include <stdio.h>
#include <unistd.h>     // for fork
#include <stdlib.h>     // for exit
#include <sys/stat.h>   // for umask
#include <sys/types.h>
#include <syslog.h>
#include <signal.h>
#include <fcntl.h>
#include <cstring>


int main()
{
    pid_t pid;
    int x_fd;

    // 1. fork off the parent process
    pid = fork();

    // an error occurred
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    // success: let the parent terminate
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // 2. On success: the child process becomes session leader and process group leader
    if (setsid() < 0) {
        exit(EXIT_FAILURE);
    }

    // 3. Catch, ignore and handle signals
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    // 4. fork off for the 2nd time
    pid = fork();

    // an error occurred
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    // success: let the parent terminate
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // 5. Set the new file permissions that is created by daemon
    umask(0);

    // Change the working directory to the root directory
    // if the current directory is on some mounted file system
    // , so daemon process will not let the mounted file system to umount

    // 6. close all open file descriptors
    chdir("/");

    // 7.
    for (x_fd = sysconf(_SC_OPEN_MAX); x_fd >= 0; x_fd --) {
        close(x_fd);
    }

    // 8. Logging errors/info in the syslog system
    int fd = 0;
    int count = 0;
    // 8-1. Either write log in syslog
    openlog("Logs", LOG_PID, LOG_USER);
    // use the following command to check 
    // CMD: tail -f /var/log/syslog

    // 8-2. Or write log in self-defined file
    fd = open("/tmp/daemon.log", O_CREAT | O_WRONLY | O_APPEND);
    if (fd < 0) {
        exit(EXIT_FAILURE);
    }

    while (1) {
        sleep(2);
        syslog(LOG_INFO, "Start Logging task = %d\n", count++);

        std::string info = "Start Logging task =\n";
        write(fd, info.c_str(), strlen(info.c_str()));
    }
    closelog();
    close(fd);
    return 1;

}
