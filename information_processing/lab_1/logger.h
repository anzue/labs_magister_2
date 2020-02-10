#ifndef LOGGER_H
#define LOGGER_H

#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include <time.h>

#define COL_WIDTH 30

//#define Info(x,y) Logger::getInstance().info(x,y)
//#define Err(x,y)  Logger::getInstance().err(x,y)
//#define Warn(x,y) Logger::getInstance().warn(x,y)

#define Info(x) Logger::getInstance().info(x,FILE)
#define Err(x)  Logger::getInstance().err(x,FILE)
#define Warn(x) Logger::getInstance().warn(x,FILE)

#define FILE "logger.h"



#define StartTimer() Logger::getInstance().start_timer()
#define EndTimer() Logger::getInstance().end_timer()


class Logger
{
private:
    Logger() {}
    std::vector<std::string> messages;
    clock_t timer;

public:
    static Logger& getInstance()
    {
        static Logger instance;
        return instance;
    }
    ~Logger();

    void start_timer();
    float end_timer();

    void info(std::string s,std::string func="");
    void warn(std::string s,std::string func="");
    void err(std::string s,std::string func="");
    void message(std::string s,std::string func);
    void print_logs(std::ostream &str);

    Logger(Logger const&)          = delete;
    void operator=(Logger const&)  = delete;

};
#endif // LOGGER_H
