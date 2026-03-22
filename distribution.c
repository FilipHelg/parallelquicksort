#include "distribution.h"

#include <math.h>
#include <stdint.h>

static uint64_t splitmix64(uint64_t* state) {
    uint64_t z = (*state += 0x9e3779b97f4a7c15ULL);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
    z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
    return z ^ (z >> 31);
}

static double rand_uniform01(uint64_t* state) {
    const uint64_t r = splitmix64(state);
    return (double)(r >> 11) * (1.0 / 9007199254740992.0);
}

static double rand_normal01(uint64_t* state) {
    // Box-Muller transform
    double u1 = rand_uniform01(state);
    double u2 = rand_uniform01(state);
    if (u1 < 1e-12) u1 = 1e-12;
    return sqrt(-2.0 * log(u1)) * cos(2.0 * 3.14159265358979323846 * u2);
}

static double rand_exponential(uint64_t* state) {
    // lambda = 1.0
    double u = rand_uniform01(state);
    if (u < 1e-12) u = 1e-12;
    return -log(u);
}

int fill_input_data(double* data, int n, char dist) {
    uint64_t state = 0x123456789abcdef0ULL;

    if (dist == 'u') {
        for (int i = 0; i < n; i++) data[i] = rand_uniform01(&state);
        return 1;
    }
    if (dist == 'n') {
        for (int i = 0; i < n; i++) data[i] = rand_normal01(&state);
        return 1;
    }
    if (dist == 'e') {
        for (int i = 0; i < n; i++) data[i] = rand_exponential(&state);
        return 1;
    }

    return 0;
}
