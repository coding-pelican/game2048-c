#include "../include/game2048.h"
#include <stdatomic.h>
#include <stdlib.h>
#include <time.h>

void seedRandomByClock() {
    // Introduce a delay to ensure a different seed value for each run
    // Alternatively, you can use a more precise time measurement function
    // such as clock() to obtain a higher-resolution seed.
    unsigned int seed = (unsigned int)time(NULL);
    seed ^= (unsigned int)clock(); // XOR with clock() to enhance randomness
    srand(seed);
}

void seedRandomByAtomic() {
    // Seed the random number generator using a combination of time and atomic counter
    static atomic_uint counter = 0;
    unsigned int seed = (unsigned int)time(NULL) ^ atomic_fetch_add(&counter, 1);
    srand(seed);
}

int main() {
    seedRandomByAtomic();
    return run2048();
}
