#pragma once

#include <string>
#include <vector>

// test common function

#define BF_KEY_MAX_LEN 50

class TestBase {
public:
    TestBase(){};
    virtual ~TestBase(){};

    virtual bool init() = 0;

    // use after init;
    void gen_strs();        // random len
    void gen_strs(int len); // fixed len

private:
    static const char _alphanum[] =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    int _str_amount = 0;
    int _inserted_num = 0;
    int _hash_num = 0;
    int _bit_num = 0;
    double _fpp = 0;
    std::vector<std::string> _strs;
};