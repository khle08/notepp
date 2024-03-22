// // For daemon.cpp test in CMakeLists env
// #include <string>
// #include <stdio.h>
// #include <unistd.h>     // for fork
// #include <stdlib.h>     // for exit
// #include <sys/stat.h>   // for umask
// #include <sys/types.h>
// #include <syslog.h>
// #include <signal.h>
// #include <fcntl.h>
// #include <cstring>

#include <chrono>
#include <thread>
#include <cstring>    // strlen
#include <fcntl.h>    // O_CREAT ... 
#include <unistd.h>   // write / close / usleep / fork
#include <iostream>
#include <sys/wait.h>

#include "log.hpp"
#include "daemon.hpp"

#define print(x) std::cout << x << std::endl


int main() {

    Daemon& dm = Daemon::instance();
    int fd = open("/home/kcl/Documents/notepp/tools/daemon/daemon.log", O_CREAT | O_WRONLY | O_APPEND);

    int count = 0;
    while (dm.IsRunning()) {
        LOG_DEBUG("count: ", count++);

        // =============================================================
        pid_t pid = fork();
        if (pid == 0) {
            execlp("sudo", "sudo", "echo 255 > /sys/devices/pwm-fan/target_pwm", NULL);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            // Error occurred and handle error
        }
        // =============================================================

        std::string info = "testing another ... " + std::to_string(count) + "\n";
        write(fd, info.c_str(), strlen(info.c_str()));
        usleep(1 * 1000 * 1000);
    }

    LOG_INFO("The daemon process ended gracefully.");
    close(fd);

	return 0;
}
