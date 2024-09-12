#include "logger.h"
#include <iostream>


Logger& Logger::GetInstance()
{
    static Logger logger;
    return logger;
}
void Logger::SetLogLevel(LogLevel level)
{
    m_loglevel = level;
}
void Logger::Log(std::string msg)
{
    m_lckQue.Push(msg);
}

Logger::Logger()
{
    std::thread writeLogTask([&](){
        while(true)
        {
            time_t now = time(nullptr);
            tm* nowtm = localtime(&now);

            char file_name[128] = {0};
            sprintf(file_name,"%d-%d-%d-log.txt",nowtm->tm_year+1900,nowtm->tm_mon+1,nowtm->tm_mday);

            FILE *pf = fopen(file_name,"a+");
            if(pf == nullptr)
            {
                std::cout << "logger file : " << file_name << " open error!" << std::endl;
                exit(EXIT_FAILURE);
            }

            std::string msg = m_lckQue.Pop();

            char time_buf[128] = {0};
            sprintf(time_buf, "%d:%d:%d =>[%s] ", 
                    nowtm->tm_hour, 
                    nowtm->tm_min, 
                    nowtm->tm_sec,
                    (m_loglevel == INFO ? "info" : "error"));
            msg.insert(0, time_buf);
            msg.append("\n");

            fputs(msg.c_str(), pf);
            fclose(pf);
        }
    });
    // 设置分离线程，守护线程
    writeLogTask.detach();
}