#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double get_time_in_seconds() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec + t.tv_nsec * 1e-9;
}

#define ARRAY_SIZE 1000000

int main() {
    int *data = (int *)malloc(sizeof(int) * ARRAY_SIZE);
    int *result = (int *)malloc(sizeof(int) * ARRAY_SIZE);

    if (!data || !result) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize random seed
    srand(time(NULL));

    // Initialize data with random numbers between 0 and 1
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        data[i] = rand() % 2;
    }

    double start_time = get_time_in_seconds();

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (data[i]) {
            result[i] -= 7;
        } else {
            result[i] += 6;
        }
    }

    double end_time = get_time_in_seconds();

    printf("Computation completed\n");
    printf("Time taken: %f seconds\n", end_time - start_time);

    free(data);
    free(result);

    return 0;
}
