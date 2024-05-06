#include <iostream>

#include "bloom_filter_test.h"

int main() {

// ------- bloom filter --------
    std::unique_ptr<BloomFilterTest> bft(new BloomFilterTest(100, 10, 0.05, 0));
    // bft->init();



    return 0;
}