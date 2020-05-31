#ifndef LONGTESTER_H
#define LONGTESTER_H

#include "bigint.h"

class LongTester
{
    int test_len;
    int iters;
public:
    LongTester(int test_len = 10 , int iters = 10):test_len(test_len),iters(iters){};

    BigInt get_random(int len = 1);

    bool test_addition();
    bool test_substraction();
    bool test_multiplication();
    bool test_division();
    bool test_binpower();

    bool test_all();

    bool run_mongomeri_test();
    bool run_simple_binpow_test();

};

#endif // LONGTESTER_H
