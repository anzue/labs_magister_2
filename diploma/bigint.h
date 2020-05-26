#ifndef BigInt_H
#define BigInt_H

#include<vector>
#include <iostream>


class BigInt
{
private:
    std::vector<int> numbers;
    const static int bits = 8;
    const static int delimiter = (1 << bits); // 256
    bool positive = true;

    BigInt inc_abs() const;
    BigInt dec_abs() const;

public:
    BigInt(int value = 0,  bool positive = true);
    BigInt operator + (const BigInt  &obj) const;
    BigInt operator * (const BigInt  &obj) const;
    BigInt operator - (const BigInt  &obj) const;
    BigInt operator / (const BigInt  &obj) const;
    BigInt operator % (const BigInt  &obj) const;
    BigInt operator -() const;
    BigInt abs() const;
    std::pair<BigInt,BigInt> divmod(const BigInt &obj) const;

    BigInt operator >>(int x) const;
    BigInt operator <<(int x) const;

    BigInt inc() const;
    BigInt dec() const;
    // todo
    BigInt operator += (const BigInt  &obj);
    BigInt operator *= (const BigInt  &obj);
    BigInt operator -= (const BigInt  &obj);
    BigInt operator /= (const BigInt  &obj);
    BigInt operator %= (const BigInt  &obj);

    BigInt bin_power(const BigInt &power, const BigInt &mod) const;
    BigInt montgomery_power(const BigInt &power, const BigInt &mod) const;

    bool operator < (const BigInt  &obj) const;
    bool operator > (const BigInt  &obj) const;
    bool operator <= (const BigInt  &obj) const;
    bool operator >= (const BigInt  &obj) const;
    bool operator == (const BigInt  &obj) const;
    bool operator != (const BigInt  &obj) const;

    int get_size() const;
    int get_value_at(int pos) const;
    void normalize();


    friend std::ostream& operator<<(std::ostream& str, const BigInt& obj);
    static BigInt random(int len = 1, bool odd = false, bool all_positive = false);

    friend class Montgomeri;

};

#endif // BigInt_H
