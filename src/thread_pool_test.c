#include "ring.h"
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void task(void* arg) {
    printf("Thread #%u working on %d\n", (int)pthread_self(), (int)arg);
    sleep(2);
}

void print_working_threads(void* arg) {
    while (1) {
        printf("working threads :%d\n", thpool_num_threads_working((threadpool)(arg)));
        sleep(4);
    }
}


int main() {
    puts("Making threadpool with 20 threads");
    threadpool thpool = thpool_init(5);

    thpool_add_work(thpool, print_working_threads, (void*)thpool);

    puts("Adding 40 tasks to threadpool");
    int i;
    for (i = 0; i < 40; i++) {
        thpool_add_work(thpool, task, (void*)(uintptr_t)i);
    };

    thpool_wait(thpool);
    puts("Killing threadpool");
    thpool_destroy(thpool);

    return 0;
}
