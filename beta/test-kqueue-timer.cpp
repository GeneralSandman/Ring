#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* for strerror() */
#include <sys/event.h>
#include <sys/time.h>
#include <unistd.h>

/* function prototypes */
void diep(const char* s);

//
int main(void) {
    struct kevent change; /* event we want to monitor */
    struct kevent event;  /* event that was triggered */
    pid_t         pid;
    int           kq, nev;

    /* create a new kernel event queue */
    if ((kq = kqueue()) == -1)
        diep("kqueue()");

    /* initalise kevent structure */
    EV_SET(&change, 1, EVFILT_TIMER, EV_ADD | EV_ENABLE, 0, 5000, 0);

    /* loop forever */
    for (;;) {
        nev = kevent(kq, &change, 1, &event, 1, NULL);

        if (nev < 0) {
            diep("kevent()");

        }

        else if (nev > 0) {
            if (event.flags & EV_ERROR) { /* report any error */
                fprintf(stderr, "EV_ERROR: %s\n", strerror(event.data));
                exit(EXIT_FAILURE);
            }

            time_t res;
            res = time(nullptr);
            printf("time:%zd\n", res);


            // reset
            //  EV_SET(&change, 1, EVFILT_TIMER, EV_ADD | EV_ENABLE, 0, 1000, 0);
        }
    }

    close(kq);
    return EXIT_SUCCESS;
}

void diep(const char* s) {
    perror(s);
    exit(EXIT_FAILURE);
}

// g++ -std=c++11 -o test-kqueue-timer ./test-kqueue-timer.cpp  && ./test-kqueue-timer