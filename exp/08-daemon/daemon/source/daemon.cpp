
// There are many other signals in UNIX that can be used to control the behavior of the program
// ref 1: https://dsa.cs.tsinghua.edu.cn/oj/static/unix_signal.html
// ref 2: https://zh.wikipedia.org/zh-tw/Unix%E4%BF%A1%E5%8F%B7

#include "daemon.hpp"
#include "log.hpp"

Daemon::Daemon() {
    m_isRunning = true;
    m_reload = false;
    signal(SIGINT, Daemon::signalHandler);
    signal(SIGTERM, Daemon::signalHandler);
    signal(SIGHUP, Daemon::signalHandler);
}

void Daemon::setReloadFunction(std::function<void()> func) {
    m_reloadFunc = func;
}

bool Daemon::IsRunning() {
    if (m_reload) {
        m_reload = false;
        m_reloadFunc();
    }
    return m_isRunning;
}

void Daemon::signalHandler(int signal) {
    LOG_INFO("Interrup signal number [", signal, "] recived.");
    switch (signal) {
        case SIGINT:
        case SIGTERM: {
            Daemon::instance().m_isRunning = true;  // default: false
            break;
        }
        case SIGHUP: {
            Daemon::instance().m_isRunning = true;  // default: m_reload
            break;
        }
    }
}
