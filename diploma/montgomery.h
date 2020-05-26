#ifndef Montgomery_H
#define Montgomery_H

#include <bigint.h>

class Montgomery
{
    BigInt n,r,revn,revr;
    int logr;
public:
    Montgomery(BigInt n);
    BigInt multiply(const BigInt &a, const BigInt &b);
    BigInt apply(const BigInt &x);
    BigInt modr(const BigInt &obj);
};

BigInt extendedEuclid(BigInt a, BigInt b, BigInt &x, BigInt &y);

#endif // Montgomery_H
