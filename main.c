#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "distribution.h"
#include "sorting.h"

int main(int argc, char** argv) {
    int n = 1 << 20;
    int threads = 8;
    char dist = 'u';

    if (argc >= 2) n = atoi(argv[1]);
    if (argc >= 3) threads = atoi(argv[2]);
    if (argc >= 4) dist = argv[3][0];

    if (dist != 'u' && dist != 'n' && dist != 'e') {
        fprintf(stderr, "distribution must be one of: u (uniform), n (normal), e (exponential)\n");
        return 1;
    }

    double* data = (double*)malloc((size_t)n * sizeof(double));
    if (!data) {
        fprintf(stderr, "failed to allocate data\n");
        return 1;
    }

    if (!fill_input_data(data, n, dist)) {
        fprintf(stderr, "failed to generate input data\n");
        free(data);
        return 1;
    }

    const double t0 = omp_get_wtime();
    if (!ParallelQuicksort(data, n, threads)) {
        free(data);
        return 1;
    }
    const double t1 = omp_get_wtime();
    printf("%.3f\n", t1-t0);

    free(data);
    return 0;
}
