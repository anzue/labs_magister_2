#include <math.h>
#include <stdio.h>
#include <bitset>
#include <assert.h>

#include "logger.h"
#include "bigint.h"
#include "montgomeri.h"

using namespace std;

BigInt::BigInt (int value, bool positive_val){
    positive = positive_val;
    if(value < 0){
        *this = BigInt(-value,!positive);
        return;
    }
    numbers = vector<int>();

    do{
        numbers.push_back(value % delimiter);
        value /= delimiter;
    }while(value>0);
    normalize();
}


BigInt BigInt::operator += (const BigInt  &obj){
    if(positive != obj.positive){
        return *this -= (-obj);
    }
    operation(Addition);
    int res_len = max(get_size(), obj.get_size()) + 1;
    numbers.resize(res_len);
    int add = 0;
    for(int i=0;i<res_len;++i){
        add += get_value_at(i) + obj.get_value_at(i);
        numbers[i] = add % delimiter;
        add /= delimiter;
    }
    normalize();
    return *this;
}

BigInt BigInt::operator *= (const BigInt  &obj){
    return *this = *this*obj;
}

BigInt BigInt::operator -= (const BigInt  &obj){
    if(positive != obj.positive){
        return *this += (-obj);
    }
    if(obj.abs() >= this->abs()){
        return *this = obj - *this;
    }

    operation(Substraction);

    int res_len = max(get_size(), obj.get_size()) + 1;
    numbers.resize(res_len);
    int add = 0;
    for(int i=0;i<res_len;++i){
        add += get_value_at(i) - obj.get_value_at(i);
        if(add < 0){
            numbers[i]  = delimiter + add;
            add = -1;
        } else {
            numbers[i] = add % delimiter;
            add /= delimiter;
        }
    }
    normalize();
    return *this;
}

BigInt BigInt::operator /= (const BigInt  &obj){
    return *this = divmod(obj).first;
}

BigInt BigInt::operator %= (const BigInt  &obj){
 return *this = divmod(obj).second;
}


BigInt BigInt::operator -() const{
    BigInt res = *this;
    res.positive = !positive;
    return res;
}

BigInt BigInt::operator + (const BigInt  &obj) const{
    if(positive != obj.positive){
        return *this - (-obj);
    }
    operation(Addition);
    BigInt res(0);
    res.positive = positive;
    int res_len = max(get_size(), obj.get_size()) + 1;
    res.numbers.resize(res_len);
    int add = 0;
    for(int i=0;i<res_len;++i){
        add += get_value_at(i) + obj.get_value_at(i);
        res.numbers[i] = add % delimiter;
        add /= delimiter;
    }
    res.normalize();
    return res;
}

BigInt BigInt::operator * (const BigInt  &obj) const{
    operation(Multiplication);
    BigInt res(0);
    res.positive = positive == obj.positive;
    int res_len = get_size() * obj.get_size() + 1;
    res.numbers.resize(res_len);
    int add = 0;
    for(int i=0;i<get_size();++i){
        add = 0;
        for(int j=0;j< obj.get_size() || add > 0;++j){
            add +=  res.numbers[i+j] + get_value_at(i) * obj.get_value_at(j);
            res.numbers[i+j] = add % delimiter;
            add /= delimiter;
        }
    }
    res.normalize();
    return res;
}

BigInt BigInt::operator - (const BigInt  &obj) const{
    if(positive != obj.positive){
        return *this + (-obj);
    }
    operation(Substraction);
    BigInt res(0);
    res.positive = positive;
    int res_len = max(get_size(), obj.get_size()) + 1;
    res.numbers.resize(res_len);
    int add = 0;
    for(int i=0;i<res_len;++i){
        add += get_value_at(i) - obj.get_value_at(i);
        if(add < 0){
            res.numbers[i]  = delimiter + add;
            add = -1;
        } else {
            res.numbers[i] = add % delimiter;
            add /= delimiter;
        }
    }
    if(add < 0){
        return -(obj - *this);
    }

    res.normalize();
    return res;
}

BigInt BigInt::operator / (const BigInt  &obj) const{
    return divmod(obj).first;
}

BigInt BigInt::operator % (const BigInt  &obj) const{
    return divmod(obj).second;
}

int BigInt::get_value_at(int pos) const{
    if(pos < 0 || pos >= numbers.size()){
        return 0;
    } else {
        return numbers[pos];
    }
}

int BigInt::get_size() const{
    return numbers.size();
}

void BigInt::normalize(){
    int pos = numbers.size() - 1;
    while(pos > 0 && numbers[pos] == 0){
        pos-=1;
    }
    numbers.resize(pos+1);
    if(numbers.size() == 1 && numbers[0] == 0) positive = true;
}

BigInt BigInt::random(int len,bool odd, bool all_positive){
    BigInt res = 0;
    res.numbers.resize(len);
    for(int i=0;i<len;++i){
        res.numbers[i] = rand()% delimiter;
    }
    if(rand()%2 & !all_positive){
        res.positive = false;
    }
    if(odd)res.numbers[0] |= 1;
    res.normalize();
    return res;
}

bool BigInt::operator < (const BigInt  &obj) const {
    if(positive != obj.positive){
        return positive < obj.positive;
    }
    int max_len = max(get_size(), obj.get_size());
    for(int i=max_len-1;i>=0;--i){
        if( get_value_at(i) != obj.get_value_at(i)){
            return (get_value_at(i) < obj.get_value_at(i)) ^ !positive;
        }
    }
    return false;
}

bool BigInt::operator > (const BigInt  &obj) const {
    if(positive != obj.positive){
        return positive > obj.positive;
    }
    int max_len = max(get_size(), obj.get_size());
    for(int i=max_len-1;i>=0;--i){
        if( get_value_at(i) != obj.get_value_at(i)){
            return (get_value_at(i) > obj.get_value_at(i)) ^ !positive;
        }
    }
    return false;
}

bool BigInt::operator <= (const BigInt  &obj) const {
    return !(*this > obj);
}

bool BigInt::operator >= (const BigInt  &obj) const {
    return !(*this < obj);
}

bool BigInt::operator == (const BigInt  &obj) const {
    if(positive != obj.positive){
        return false;
    }
    int max_len = max(get_size(), obj.get_size());
    for(int i=0;i<max_len;++i){
        if( get_value_at(i) != obj.get_value_at(i)){
            return false;
        }
    }
    return true;
}

bool BigInt::operator != (const BigInt  &obj) const {
    return !(*this == obj);
}

BigInt BigInt::abs() const{
    if(positive)
        return *this;
    else
        return -*this;
}

BigInt BigInt::operator >>(int x) const{
    if(x < 0){
        return *this << (-x);
    }
    operation(Bitshift);
    BigInt res = *this;

    int bytes_count = x / bits;
    int remainder = x % bits;
    for(int i = 0; i < numbers.size();++i){
        res.numbers[i] = (get_value_at(i + bytes_count) >> remainder)
                         + ((get_value_at(i + bytes_count + 1) & ((1 << remainder) - 1)) << (bits - remainder));
    }
    res.normalize();
    return res;
}

BigInt BigInt::operator <<(int x) const{
    if(x < 0){
        return *this >> (-x);
    }
    operation(Bitshift);
    int bytes_count = x / bits;
    int remainder = x % bits;
    BigInt res(0);
    res.numbers.resize(get_size() + bytes_count + 1);

    for(int i = 0; i < numbers.size() + bytes_count + 1;++i){
        res.numbers[i] = ((get_value_at(i - bytes_count) << remainder) & (( 1 << bits) - 1))
                         + (get_value_at(i - bytes_count - 1) >> (bits - remainder));
    }
    res.positive = positive;
    res.normalize();
    return res;
}


std::pair<BigInt,BigInt> BigInt::divmod(const BigInt &obj) const{
    if( !positive || !obj.positive){
        std::pair<BigInt,BigInt> res = this->abs().divmod(obj.abs());
        if( !positive){
            res.first.positive = false;
            res.second.positive = false;
            res.second.normalize();
        }
        if(!obj.positive){
            res.first = -res.first;
        }
        if(!res.second.positive){
            if(obj.positive)
                res.first = res.first.dec();
            else
                res.first = res.first.inc();
            res.second = res.second + obj.abs();
        }
        res.first.normalize();
        res.second.normalize();
        return res;
    }
    operation(Division);
    BigInt l = 0,r = *this, m;
    BigInt incm;
    while(l!=r){
        m = (l+r) >> 1;
        incm = m.inc();
        if(*this >= incm * obj)
            l = incm;
        else
            r = m;
    }
    l.normalize();
    return {l, *this - l*obj};
}

BigInt BigInt::bin_power(const BigInt &power, const BigInt &mod) const{
    assert(power.positive);
    BigInt a = *this;
    BigInt res = 1;
    for(int i=0;i< numbers.size() * bits;++i){
        if(power.numbers[i/bits]&( 1 << (i%bits))){
            res = (res * a) % mod;
        }
        a = (a*a) % mod;
    }
    return res;
}

BigInt BigInt::montgomery_power(const BigInt &power, const BigInt &mod) const{
    assert(power.positive);
    Montgomeri mul(mod);
    BigInt a = mul.apply(*this);
    BigInt res = mul.apply(1);
    for(int i=0;i<numbers.size() * bits;++i){
        if(power.numbers[i/bits]&( 1 << (i%bits))){
            res = mul.multiply(res,a);
        }
        a = mul.multiply(a,a);
    }
    return mul.multiply(res,1);
}


BigInt BigInt::inc_abs() const{
    BigInt res = *this;
    res.numbers[0] += 1;
    int pos = 0;
    for(;pos < res.numbers.size()-1 && res.numbers[pos] >= delimiter;++pos){
        res.numbers[pos] = 0;
        ++res.numbers[pos+1];
    }
    if(pos == res.numbers.size() - 1 && res.numbers[pos] >= delimiter){
        res.numbers[pos] = 0;
        res.numbers.push_back(1);
    }
    res.normalize();
    return res;
}

BigInt BigInt::dec_abs() const{
    if(this->get_size() == 1 && this->numbers[0] == 0){
        return -1;
    }
    BigInt res = *this;
    res.numbers[0] -= 1;
    int pos = 0;
    for(;pos < res.numbers.size()-1 && res.numbers[pos] < 0;++pos){
        res.numbers[pos] += delimiter;
        --res.numbers[pos+1];
    }
    return res;
}


BigInt BigInt::inc() const{
    return positive?inc_abs():dec_abs();
}

BigInt BigInt::dec() const{
    return positive?dec_abs():inc_abs();
}

std::ostream& operator<<(std::ostream& str, const BigInt& obj){
    cout << "[" << std::dec << obj.numbers.size() << "] ";
    if( !obj.positive){
        cout << "-";
    }
    for(int i= obj.numbers.size()-1;i>=0;--i){
        for(int j = BigInt::bits / 4 - 1;j >= 0; --j){
            cout << std::hex << (( obj.numbers[i] >> ( 4*j) ) & 15);
        }
    }
}

