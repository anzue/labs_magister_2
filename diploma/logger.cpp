#include "logger.h"
#include <string>
#include <iomanip>

std::string operation_names[] = {
    "Addition",
    "Substraction",
    "Multiplication",
    "Division",
    "Bitshift"
};

void Logger::print_and_clear(std::ostream &str, int iters){
#ifdef operations_counter
    str << std::dec << std::fixed << std :: setprecision(3);
    for(auto x:operations){
        str << std::dec << operation_names[x.first] << "\t\t" << x.second << " | " << x.second * 1./iters  << " p.op. \n";
    }
    operations.clear();
#endif
}

Logger::~Logger(){
    print_and_clear(std::cout);
}

void Logger::start_timer(){
    timer = clock();
}

float Logger::end_timer(){
    float time = (clock() - timer)/CLOCKS_PER_SEC;
    timer = clock();
    return time;
}

void Logger::record_operation(Operation name){
    ++operations[name];
}
