/**
 * @file main.c
 * @author Gyeongtae Kim(dev-dasae) <codingpelican@gmail.com>
 *
 * @brief 2048 Game
 * @details This is a simple implementation of the 2048 game in C.
 *
 * @version 0.1
 * @date 2024-02-02
 *
 * @copyright Released under the MIT License. See LICENSE file for details.
 */


#include "game2048.h"

#include <stdatomic.h>
#include <stdlib.h>
#include <time.h>


/**
 * @brief Seed the random number generator using a combination of the current time and a clock-based value.
 * @details Seed the random number generator using a combination of the current time and a clock-based value.
            - This function is used to initialize the random number generator with a unique seed value for each program
            execution.
            - It combines the current time obtained from `time(NULL)` with the current clock value obtained from `clock()`
            to generate a more random seed value.
            - The clock-based value is XOR'd with the time-based value to enhance the randomness of the seed.
 */
void seedRandomByClock() {
    // Introduce a delay to ensure a different seed value for each run
    // Alternatively, you can use a more precise time measurement function
    // such as clock() to obtain a higher-resolution seed.
    unsigned int seed = (unsigned int)time(NULL);
    seed ^= (unsigned int)clock(); // XOR with clock() to enhance randomness
    srand(seed);
}

/**
 * @brief Seed the random number generator using a combination of the current time and an atomic counter.
 * @details Seed the random number generator using a combination of the current time and an atomic counter.
            - This function is used to initialize the random number generator with a unique seed value for each program
            execution.
            - It combines the current time obtained from `time(NULL)` with an atomic counter value to generate a more
            random seed value.
            - The atomic counter is incremented after each call to ensure a different seed value.
 */
void seedRandomByAtomic() {
    // Seed the random number generator using a combination of time and atomic counter
    static atomic_uint counter = 0;
    unsigned int       seed    = (unsigned int)time(NULL) ^ atomic_fetch_add(&counter, 1);
    srand(seed);
}


int main() {
    seedRandomByAtomic();
    return Game_run2048();
}
