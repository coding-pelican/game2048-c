#ifndef RANDOM_H
#define RANDOM_H

#include <stdint.h>
#include <time.h>

#define random_kLeftShiftAmount   (23ULL)
#define random_kRightShiftXAmount (17ULL)
#define random_kRightShiftYAmount (26ULL)
#define random_kRawSeedFirst      (0x8a5cd789635d2dffULL)
#define random_kRawSeedSecond     (0x121fd2155c472f96ULL)


static inline uint64_t random_xorShift128Plus(uint64_t seed[2]) {
    uint64_t x = seed[0];
    uint64_t y = seed[1];
    seed[0]    = y;
    x ^= x << random_kLeftShiftAmount;
    seed[1] = x ^ y ^ (x >> random_kRightShiftXAmount) ^ (y >> random_kRightShiftYAmount);
    return seed[1] + y;
}

// Suppress unused function warning for genRand in GCC
#ifdef __GNUC__
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wunused-function"
#endif

static inline uint64_t random_generate() {
    uint64_t seed[2] = {
        random_kRawSeedFirst ^ (uint64_t)time(NULL) ^ (uint64_t)clock(),
        random_kRawSeedSecond ^ (uint64_t)clock()
    };
    return random_xorShift128Plus(seed);
}

#ifdef __GNUC__
#  pragma GCC diagnostic pop
#endif

#endif // !RANDOM_H
