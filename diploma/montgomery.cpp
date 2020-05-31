#include <assert.h>
#include <iostream>

#include "montgomeri.h"

using namespace std;

BigInt extendedEuclid(BigInt a, BigInt b, BigInt &x, BigInt &y){
    if( b == 0){
        x = 1;
        y = 0;
        return a;
    }
    std::pair<BigInt,BigInt> divmod =  a.divmod(b);
    BigInt x_new,y_new,gcd_new = extendedEuclid(b, divmod.second, x_new,y_new);
    x = y_new;
    y = x_new - y_new * divmod.first;
    return gcd_new;
}



Montgomeri::Montgomeri(BigInt n_){
    n = n_;
    r = BigInt(0);
    if( n.numbers.back()  >= (1 << (BigInt::bits-1))){
        r.numbers.resize(n.get_size() + 1);
        r.numbers.back() = 1;
        logr = n.get_size() * BigInt::bits;
    } else {
        logr = n.get_size() * BigInt::bits - 1;
        r.numbers.resize(n.get_size());
        int val = 1 << (BigInt::bits-1);
        while( val > 0 && val / 2 >  n.numbers.back()) {val /= 2;--logr;}
        r.numbers.back() = val;
    }

    BigInt gcd = extendedEuclid(n,r,revn,revr);
    revn = -revn;

    if( !revn.positive ){
        BigInt addition = revn / r;
        revn = revn - r*addition;
        revr = revr - n*addition;
    }
}


BigInt Montgomeri::modr(const BigInt &obj){
    BigInt res = obj;
    if(logr / BigInt::bits < res.numbers.size()){
        res.numbers[logr/BigInt::bits] &= (1 << logr % BigInt::bits) - 1;
    }
    for(int i=logr / BigInt::bits + 1;i<res.numbers.size();++i){
        res.numbers[i] = 0;
    }
    res.normalize();
    return res;
}

BigInt Montgomeri::multiply(const BigInt &a, const BigInt &b){
    BigInt t = a * b;
    BigInt u = (t +  ( modr(t* revn)) * n) >> logr;
    if(u>=n){
        u = u-n;
    }
    return u;
}

BigInt Montgomeri::apply(const BigInt &x){
    return (x << logr) % n;
}
