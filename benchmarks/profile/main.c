#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

struct Node {
    int wt;
    struct Node* next;
};

struct Node* build_list(int64_t N, double percent_positive) {
    struct Node* head = NULL;
    struct Node* current = NULL;
    int64_t i;

    for (i = 0; i < N; i++) {
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        if (new_node == NULL) {
            fprintf(stderr, "Memory allocation failed at node %" PRId64 "\n", i);
            exit(EXIT_FAILURE);
        }

        if ((rand() / (double)RAND_MAX) < percent_positive) {
            new_node->wt = rand() % 100 + 1;
        } else {
            new_node->wt = -(rand() % 100 + 1);
        }
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
            current = new_node;
        } else {
            current->next = new_node;
            current = new_node;
        }
    }
    return head;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s N percent_positive\n", argv[0]);
        printf("Example: %s 1000000 0.99\n", argv[0]);
        return 1;
    }

    int64_t N = atoll(argv[1]);
    double percent_positive = atof(argv[2]);

    printf("Processing %" PRId64 " nodes (%.2f positive)\n", N, percent_positive);
    srand(time(NULL));
    struct Node* ptr = build_list(N, percent_positive);

    int64_t avg = 0;
    int64_t weight = 0;
    int64_t count = 0;

    struct timespec start_time, end_time;
    double elapsed_time;

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    while (ptr != NULL) {
        count++;
        if(ptr->wt < 0) {
            weight -= ptr->wt;
        } else {
            weight += ptr->wt;
        }
        struct Node* temp = ptr;
        ptr = ptr->next;
        free(temp);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                   (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    if(count != 0) {
        avg = weight / count;
    }
    printf("Average weight: %" PRId64 "\n", avg);
    printf("Processing time: %.6f seconds\n", elapsed_time);
    return 0;
}
