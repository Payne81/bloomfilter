#pragma once 

#include <memory>

#include "test_base.h"
#include "../src/bloom_filter.h"

/**
    test target：
        1. if fpp close to the reasoning;

*/

class BloomFilterTest : public TestBase {
public:
    BloomFilterTest(int str_amount, int bit_num, double fpp, int key_len = 0)
        :TestBase(str_amount, 0, bit_num, fpp, key_len) {}
    ~BloomFilterTest() = default;

    bool init() override;
    bool run() override;

private:
    std::unique_ptr<BloomFilter> _bf = nullptr;
};



