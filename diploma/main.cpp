#include <iostream>

#include "longtester.h"
#include "logger.h"

using namespace std;

int main()
{
    int bytes = 42;
    int decimal_aprox = (bytes * 8.) / 10 * 3;
    cout << "Numbers size = " << bytes << " bytes which is aproximatly " << decimal_aprox << " decimal numbers\n";

    LongTester tester(bytes, 20);
   // tester.test_all();
    tester.run_mongomeri_test();
    tester.run_simple_binpow_test();
   // tester.run_simple_binpow_test();

    return 0;
}
