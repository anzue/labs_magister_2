#ifndef LOGGER_H
#define LOGGER_H

#include <map>
#include <time.h>
#include <fstream>
#include <iostream>
#include <vector>

//#define operations_counter

#ifdef operations_counter
#define operation(name)  Logger::get_instance().record_operation(name)
#else
#define operation(name)
#endif

#define print_log(str,iters) Logger::get_instance().print_and_clear(str,iters)
#define start_log_timer() Logger::get_instance().start_timer()
#define end_log_timer() Logger::get_instance().end_timer()

enum Operation{
        Addition,
        Substraction,
        Multiplication,
        Division,
        Bitshift
};



class Logger
{
private:
    Logger() {}
    float timer;
    std::map<Operation,int> operations;

public:

    static Logger& get_instance()
    {
        static Logger instance;
        return instance;
    }
    ~Logger();

    void start_timer();
    float end_timer();

    void record_operation(Operation operation);
    void print_and_clear(std::ostream &str, int iters = 1);

    Logger(Logger const&)          = delete;
    void operator=(Logger const&)  = delete;

};
#endif // LOGGER_H
