/**
 * @file random.h
 * @author Gyeongtae Kim(dev-dasae) <codingpelican@gmail.com>
 *
 * @brief Provides a random number generator using the xorshift128+ algorithm.
 * @details This file defines a set of macros and functions for generating random numbers
            using the xorshift128+ algorithm. The random_generate() function returns a
            64-bit random number, and the random_xorShift128Plus() function is a helper
            function that implements the xorshift128+ algorithm.
 * @version 0.1
 * @date 2024-02-02
 *
 * @copyright Released under the MIT License. See LICENSE file for details.
 */


#ifndef RANDOM_H
#define RANDOM_H

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)


#include <stdint.h>
#include <time.h>


#define random_kLeftShiftAmount   (23ULL)
#define random_kRightShiftXAmount (17ULL)
#define random_kRightShiftYAmount (26ULL)
#define random_kRawSeedFirst      (0x8a5cd789635d2dffULL)
#define random_kRawSeedSecond     (0x121fd2155c472f96ULL)


/**
 * @brief Implements the xorshift128+ algorithm to generate a random number.
 * @param seed An array of two 64-bit integers representing the seed.
 * @return The generated random number.
 * @details This function implements the xorshift128+ algorithm to generate a random number.
            - It takes an array of two 64-bit integers as the seed, and updates the seed values as part of the algorithm.
 */
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
#endif // __GNUC__

/**
 * @brief Generates a 64-bit random number using the xorshift128+ algorithm.
 * @return A 64-bit random number.
 * @details This function generates a 64-bit random number using the xorshift128+ algorithm.
            - It initializes the seed using the current time and clock, and then calls the random_xorShift128Plus() function to generate the random number.
 */
static inline uint64_t random_generate() {
    uint64_t seed[2] = {
        random_kRawSeedFirst ^ (uint64_t)time(NULL) ^ (uint64_t)clock(),
        random_kRawSeedSecond ^ (uint64_t)clock()
    };
    return random_xorShift128Plus(seed);
}

#ifdef __GNUC__
#  pragma GCC diagnostic pop
#endif // __GNUC__


#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

#endif // !RANDOM_H
