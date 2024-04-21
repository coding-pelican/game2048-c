#ifndef DH_RANDOM_H
#define DH_RANDOM_H

#define DH_RANDOM_LEFT_SHIFT_AMOUNT    (23ULL)
#define DH_RANDOM_RIGHT_SHIFT_X_AMOUNT (17ULL)
#define DH_RANDOM_RIGHT_SHIFT_Y_AMOUNT (26ULL)
#define DH_RANDOM_RAW_SEED_FIRST       (0x8a5cd789635d2dffULL)
#define DH_RANDOM_RAW_SEED_SECOND      (0x121fd2155c472f96ULL)

#include <stdint.h>
#include <time.h>

static inline uint64_t xorshift128plus(uint64_t seed[2]) {
    uint64_t x = seed[0];
    uint64_t y = seed[1];
    seed[0] = y;
    x ^= x << DH_RANDOM_LEFT_SHIFT_AMOUNT;
    seed[1] = x ^ y ^ (x >> DH_RANDOM_RIGHT_SHIFT_X_AMOUNT) ^ (y >> DH_RANDOM_RIGHT_SHIFT_Y_AMOUNT);
    return seed[1] + y;
}

// Suppress unused function warning for genRand in GCC
#ifdef __GNUC__
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wunused-function"
#endif

static inline uint64_t genRand() {
    uint64_t seed[2] = {
        DH_RANDOM_RAW_SEED_FIRST ^ (uint64_t)time(NULL) ^ (uint64_t)clock(),
        DH_RANDOM_RAW_SEED_SECOND ^ (uint64_t)clock()
    };
    return xorshift128plus(seed);
}

#ifdef __GNUC__
#  pragma GCC diagnostic pop
#endif

#endif // !DH_RANDOM_H
