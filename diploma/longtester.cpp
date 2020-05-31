#include <iostream>
#include <iomanip>

#include "longtester.h"
#include "logger.h"

using namespace std;

bool check_fail(std::string method_name,  std::string operator_char, BigInt arg1, BigInt arg2, BigInt real_res, BigInt expected_res){
    if(expected_res != real_res){
        cout << "Method " << method_name << " failed : Expected \n   " << arg1 << "\n " << operator_char << " " << arg2 << " \n = " << expected_res << " \n while got \n   " << real_res << "\n";
        return false;
    }
    return true;
}

void show_progress(string name,int cur,int max, int len = 20){
    if(cur % 5 != 0){
        return;
    }
    double pers = 1. * cur / max;
    cout << name + ": [";
    int i;
    for(i=0;i < len * pers - 1;++i){
        cout << "=";
    }
    if( cur < max ){
        cout << ">";
        ++i;
    }
    while(i++<len){
        cout << " ";
    }
    cout << "] " << std::dec << cur << "/"<< max << "\n";
}


bool LongTester::test_addition(){
    string method_name = "addition";string operator_char = "+";
    for(int i=0;i<iters;++i){
        BigInt a = BigInt::random(test_len);
        BigInt b = BigInt::random(test_len);
        BigInt c = BigInt::random(test_len);
        show_progress(method_name,i,iters);
        if (!check_fail(method_name,operator_char,a+b,c,(a+b) + c,(a+c)+b) |
            !check_fail(method_name,operator_char,a+b,c,(a+b) + c,(b+c)+a)
            ) {
            return false;
        }
    }
    cout << "Addition OK\n";

    return true;
}

bool LongTester::test_substraction(){
    string method_name = "substraction";string operator_char = "-";
    for(int i=0;i<iters;++i){
        BigInt a = BigInt::random(test_len);
        BigInt b = BigInt::random(test_len);
        BigInt c = BigInt::random(test_len);
        show_progress(method_name,i,iters);
        if (!check_fail(method_name,operator_char,a-b,c,(a-b) - c,(a-c)-b) |
            !check_fail(method_name,operator_char,a-b,c,(a-b) - c,a-(b+c))
            ) {
            return false;
        }
    }
    cout << "Substraction OK\n";
    return true;
}

bool LongTester::test_multiplication(){
    string method_name = "multiplication";string operator_char = "*";
    for(int i=0;i<iters;++i){
        BigInt a = BigInt::random(test_len);
        BigInt b = BigInt::random(test_len);
        BigInt c = BigInt::random(test_len);
        show_progress(method_name,i,iters);
        if (!check_fail(method_name,operator_char,a*b,c,(a*b) * c,(a*c)*b) |
            !check_fail(method_name,operator_char,a*b,c,(a*b) * c,(b*c)*a)
            ) {
            return false;
        }
    }
    cout << "Multiplication OK\n";
    return true;

}

bool LongTester::test_division(){
    string method_name = "division";string operator_char = "/";
    for(int i=0;i<iters;++i){
        BigInt a = BigInt::random((1+test_len)/2);
        BigInt b = BigInt::random((1+test_len)/2);
        BigInt c = BigInt::random((1+test_len)/2);
        if(b == 0) continue;
        show_progress(method_name,i,iters);
        if (!check_fail(method_name,operator_char,a * b, b , (a*b)/b , a)
         |  !check_fail(method_name,operator_char,a*b + b * c, a + c,(a*b+b*c) / (a+c), b)
            ) {
            return false;
        }
    }
    cout << "Division OK\n";
    return true;
}

bool LongTester::test_binpower(){
    string method_name = "binpower";string operator_char = "^";
    for(int i=0;i<iters;++i){
        BigInt a = BigInt::random(test_len,false,true);
        BigInt b = BigInt::random(test_len,false,true);
        BigInt c = BigInt::random(test_len,true,true);

        show_progress(method_name,i,iters);
        if (!check_fail(method_name,operator_char, a, b, a.bin_power(b,c), a.montgomery_power(b,c))
            ) {
            return false;
        }
    }
    cout << "Binary power OK\n";

}


bool LongTester::test_all(){
    test_addition();
    test_substraction();
    test_multiplication();
    test_division();
    test_binpower();
}


bool LongTester::run_mongomeri_test(){
    start_log_timer();
    for(int i=0;i<iters;++i){
        BigInt a = BigInt::random(test_len,true,true);
        BigInt b = BigInt::random(test_len,true,true);
        BigInt c = BigInt::random(test_len,true,true);

        show_progress("Montgomeri test",i,iters);
        a.montgomery_power(b,c);

    }
    float total_runtime =  end_log_timer();
    cout << std::dec << fixed << std::setprecision(3);
    cout << "Total time = " << total_runtime << " or " << total_runtime / iters << " per operation\n";
    cout << "Total operations \n"; print_log(std::cout, iters);
}

bool LongTester::run_simple_binpow_test(){
    start_log_timer();
    for(int i=0;i<iters;++i){
        BigInt a = BigInt::random(test_len,true,true);
        BigInt b = BigInt::random(test_len,true,true);
        BigInt c = BigInt::random(test_len,true,true);

        show_progress("Simple power test",i,iters);
        a.bin_power(b,c);

    }
    float total_runtime =  end_log_timer();
    cout << std::dec << fixed << std::setprecision(3);
    cout << "Total time = " << total_runtime << " or " << total_runtime / iters << " per operation\n";
    cout << "Total operations \n"; print_log(std::cout, iters);
}



