#pragma once

#include <string>
#include <vector>

// test common function

#define BF_KEY_MAX_LEN 50

constexpr char _alphanum[63] =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

class TestBase {
public:
    TestBase(int str_amount, int hash_num, int bit_num, double fpp, int key_len = 0)
        :_str_amount(str_amount),
        _hash_num(hash_num),
        _bit_num(bit_num),
        _fpp(fpp),
        _key_len(key_len){}
    virtual ~TestBase(){}

    virtual bool init() = 0;
    virtual bool run() = 0;

    // use after init;
    void gen_strs();        // random len
    void gen_strs(int len); // fixed len

private:
    int _str_amount = 0;
    int _hash_num = 0;
    int _bit_num = 0;
    int _key_len = 0;
    
    // use for check reasoning
    double _fpp = 0;
    std::vector<std::string> _strs;
};