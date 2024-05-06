#include "test_base.h"


void TestBase::gen_strs() {
    assert(_str_amount != 0);
    for(int i = 0; i < _str_amount; i++) {
        std::string new_str;
        int len = rand() % BF_KEY_MAX_LEN;
        new_str.reserve(len);

        for (int i = 0; i < len; ++i) {
            new_str += _alphanum[rand() % (sizeof(_alphanum) - 1)];
        }

        _strs.push_back(new_str);
    }
}

void TestBase::gen_strs(int len) {
    assert(_str_amount != 0);
    for(int i = 0; i < _str_amount; i++) {
        std::string new_str;
        new_str.reserve(len);

        for (int i = 0; i < len; ++i) {
            new_str += _alphanum[rand() % (sizeof(_alphanum) - 1)];
        }

        _strs.push_back(new_str);
    }
}