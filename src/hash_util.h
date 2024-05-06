#pragma once

#include <functional>
#include "murmur_hash3.h"


// Utility class to compute hash values.
class HashUtil {
public:
    template <typename T>
    static uint32_t fixed_len_to_uint32(T value) {
        if constexpr (sizeof(T) <= sizeof(uint32_t)) {
            return (uint32_t)value;
        }
        return std::hash<T>()(value);
    }


    static const uint32_t MURMUR3_32_SEED = 104729;

    static uint32_t murmur_hash3_32(const void* key, int32_t len, uint32_t seed) {
        uint32_t out = 0;
        murmur_hash3_x86_32(key, len, seed, &out);
        return out;
    }

    static const int MURMUR_R = 47;

    // Murmur2 hash implementation returning 64-bit hashes.
    static uint64_t murmur_hash2_64(const void* input, int len, uint64_t seed) {
        uint64_t h = seed ^ (len * MURMUR_PRIME);

        const uint64_t* data = reinterpret_cast<const uint64_t*>(input);
        const uint64_t* end = data + (len / sizeof(uint64_t));

        while (data != end) {
            uint64_t k = *data++;
            k *= MURMUR_PRIME;
            k ^= k >> MURMUR_R;
            k *= MURMUR_PRIME;
            h ^= k;
            h *= MURMUR_PRIME;
        }

        const uint8_t* data2 = reinterpret_cast<const uint8_t*>(data);
        switch (len & 7) {
        case 7:
            h ^= uint64_t(data2[6]) << 48;
            [[fallthrough]];
        case 6:
            h ^= uint64_t(data2[5]) << 40;
            [[fallthrough]];
        case 5:
            h ^= uint64_t(data2[4]) << 32;
            [[fallthrough]];
        case 4:
            h ^= uint64_t(data2[3]) << 24;
            [[fallthrough]];
        case 3:
            h ^= uint64_t(data2[2]) << 16;
            [[fallthrough]];
        case 2:
            h ^= uint64_t(data2[1]) << 8;
            [[fallthrough]];
        case 1:
            h ^= uint64_t(data2[0]);
            h *= MURMUR_PRIME;
        }

        h ^= h >> MURMUR_R;
        h *= MURMUR_PRIME;
        h ^= h >> MURMUR_R;
        return h;
    }

    // default values recommended by http://isthe.com/chongo/tech/comp/fnv/
    static const uint32_t FNV_PRIME = 0x01000193; //   16777619
    static const uint32_t FNV_SEED = 0x811C9DC5;  // 2166136261
    static const uint64_t FNV64_PRIME = 1099511628211UL;
    static const uint64_t FNV64_SEED = 14695981039346656037UL;
    static const uint64_t MURMUR_PRIME = 0xc6a4a7935bd1e995ULL;
    static const uint32_t MURMUR_SEED = 0xadc83b19ULL;
    // Implementation of the Fowler–Noll–Vo hash function.  This is not as performant
    // as boost's hash on int types (2x slower) but has bit entropy.
    // For ints, boost just returns the value of the int which can be pathological.
    // For example, if the data is <1000, 2000, 3000, 4000, ..> and then the mod of 1000
    // is taken on the hash, all values will collide to the same bucket.
    // For string values, Fnv is slightly faster than boost.
    static uint32_t fnv_hash(const void* data, int32_t bytes, uint32_t hash) {
        const uint8_t* ptr = reinterpret_cast<const uint8_t*>(data);

        while (bytes--) {
            hash = (*ptr ^ hash) * FNV_PRIME;
            ++ptr;
        }

        return hash;
    }

    static uint64_t fnv_hash64(const void* data, int32_t bytes, uint64_t hash) {
        const uint8_t* ptr = reinterpret_cast<const uint8_t*>(data);

        while (bytes--) {
            hash = (*ptr ^ hash) * FNV64_PRIME;
            ++ptr;
        }

        return hash;
    }

    // Computes the hash value for data.  Will call either CrcHash or FnvHash
    // depending on hardware capabilities.
    // Seed values for different steps of the query execution should use different seeds
    // to prevent accidental key collisions. (See IMPALA-219 for more details).
    static uint32_t hash(const void* data, int32_t bytes, uint32_t seed) {
        // 支持sse4_2可以使用该指令集加速，但是懒得写
        return fnv_hash(data, bytes, seed);
    }

    static uint64_t hash64(const void* data, int32_t bytes, uint64_t seed) {
        // 支持sse4_2可以使用该指令集加速，但是懒得写
        uint64_t hash = 0;
        murmur_hash3_x64_64(data, bytes, seed, &hash);
        return hash;
    }


    // hash_combine is the same with boost hash_combine,
    // except replace boost::hash with std::hash
    template <class T>
    static inline void hash_combine(std::size_t& seed, const T& v) {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
};

// 2024年了，tm怎么还有人用这种版本？建议枪毙
#if __GNUC__ < 6 && !defined(__clang__) 
// Cause this is builtin function
template <>
struct std::hash<__int128> {
    std::size_t operator()(const __int128& val) const {
        return HashUtil::hash(&val, sizeof(val), 0);
    }
};
#endif
