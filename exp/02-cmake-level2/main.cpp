// For daemon.cpp test in CMakeLists env
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

#include <iostream>
#include "hello.hpp"

#define print(x) std::cout << x << std::endl

int main() {
    hello::say_hello();

    pid_t pid;
    int x_fd;

    // 1. fork off the parent process
    pid = fork();

    print(pid);
    // an error occurred
    if (pid < 0) {
        exit(EXIT_FAILURE);
        print("1. failed in pid");
    }

    // success: let the parent terminate
    if (pid > 0) {
        exit(EXIT_SUCCESS);
        print("2. succeed in pid");
    }

    // 2. On success: the child process becomes session leader and process group leader
    if (setsid() < 0) {
        print("3. failed in setsid");
        exit(EXIT_FAILURE);
    }

    // 3. Catch, ignore and handle signals
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    // 4. fork off for the 2nd time
    pid = fork();

    // an error occurred
    if (pid < 0) {
        print("4. failed in pid");
        exit(EXIT_FAILURE);
    }

    // success: let the parent terminate
    if (pid > 0) {
        print("5. succeed in pid");
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
    return 0;
}