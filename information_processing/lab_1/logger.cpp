#include "logger.h"
#define FILE "logger.cpp"

void Logger::info(std::string s,std::string func){
    message(s,"INFO    : "+func);
}

void Logger::warn(std::string s,std::string func){
    message(s,"WARNING : " +func);
}

void Logger::err(std::string s,std::string func) {
    message(s,"ERROR   : " + func);
}

void Logger::message(std::string mes,std::string func){
    if(func.length() > COL_WIDTH){
        func = func.substr(0,COL_WIDTH);
    }
    while(func.length() < COL_WIDTH){
        func += " ";
    }
    messages.push_back(func + mes);
}

void Logger::print_logs(std::ostream &str){
    for(auto &mess:messages){
        str<<mess<<"\n";
    }
    str << std::endl;
    messages.clear();
}

Logger::~Logger(){
    print_logs(std::cout);
}

void Logger::start_timer(){
    timer = clock();
}

float Logger::end_timer(){
    float time = (clock() - timer)/CLOCKS_PER_SEC;
    timer = clock();
    return time;
}
