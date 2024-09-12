#pragma once
#include "lockqueue.h"
#include <string>

// 定义日志级别
enum LogLevel
{
    INFO,  // 普通信息
    ERROR, // 错误信息
};

class Logger
{
public:
    static Logger& GetInstance();
    void SetLogLevel(LogLevel level);
    void Log(std::string msg);
private:
    int m_loglevel;
    LockQueue<std::string> m_lckQue;

    Logger();
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
};