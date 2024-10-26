#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void predicated_function(int *data, int size);
void speculative_function(int *data, int size);

double get_time_in_seconds() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec + t.tv_nsec * 1e-9;
}

int main() {
    const int size = 1000000;
    int *data = malloc(size * sizeof(int));
    if (!data) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        data[i] = rand() % 100;
    }

    double start_time = get_time_in_seconds();
    predicated_function(data, size);
    double end_time = get_time_in_seconds();
    printf("Predicated function took %f seconds\n", end_time - start_time);

    for (int i = 0; i < size; i++) {
        data[i] = rand() % 100;
    }

    start_time = get_time_in_seconds();
    speculative_function(data, size);
    end_time = get_time_in_seconds();
    printf("Speculative function took %f seconds\n", end_time - start_time);

    free(data);
    return 0;
}
