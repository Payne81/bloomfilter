#include "bloom_filter_test.h"
#include <iostream>

bool BloomFilterTest::init() {
    if (_key_len != 0) {
        gen_strs(key_len);
    } else {
        gen_strs();
    }

    _bf = make_unique();
    _bf->init(_str_amount, _fpp);
    for(auto it : _strs) {

        _bf->add_bytes(it.c_str(), it.length());
        cout<< sizeof(it.c_str()) << " " < it.length() << endl;
    }
}

bool BloomFilterTest::run() {

}