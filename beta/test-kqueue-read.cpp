#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/event.h>
#include <unistd.h>
#include <vector>

#define BUFFER_SIZE 100


#define WRITE_BUFFER_SIZE (1024 * 1024 * 1024)

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // 打开文件
    int fd = open(argv[1], O_RDWR | O_NONBLOCK | O_APPEND);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // 创建 kqueue
    int kq = kqueue();
    if (kq == -1) {
        perror("kqueue");
        close(fd);
        return 1;
    }

    // 添加文件描述符到 kqueue 监听
    struct kevent events[10];
    unsigned int  event_index = 0;
    EV_SET(&events[event_index++], fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    // EV_SET(&events[event_index++], fd, EVFILT_VNODE, EV_ADD | EV_ENABLE, 0, 0, NULL);
    // EV_SET(&events[event_index++], fd, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);


    if (kevent(kq, events, event_index, events, event_index, NULL) == -1) {
        perror("kevent");
        exit(1);
    }

    struct timespec timeout = {
        .tv_sec  = 5,
        .tv_nsec = 0,
    };

    // 异步读取文件
    char    buffer[BUFFER_SIZE];
    ssize_t all_size    = 0;

    int     debug_count = 0;

    // write(fd, "hello world\n", 12);


    while (1) {
        debug_count++;
        if (debug_count > 10) {
            // exit(0);
        }


        printf("------\n");
        struct kevent active_events[2];
        int           nEvents = kevent(kq, NULL, 0, active_events, 2, &timeout);
        if (nEvents == -1) {
            perror("kevent");
            break;
        }
        if (nEvents == 0) {
            continue;
        }


        for (int i = 0; i < nEvents; i++) {
            printf("event[%d] happend: filter:%x, flag:%x, flags:%x\n", i, events[i].filter, events[i].flags, events[i].fflags);

            if (active_events[i].filter == EVFILT_READ) {
                printf("event[%d]: EVFILT_READ\n", i);

                ssize_t bytesRead = read(events[i].ident, buffer, sizeof(buffer));
                if (bytesRead == -1) {
                    perror("read");
                    break;
                }

                if (bytesRead == 0) {
                    printf("End of file reached\n");
                    break;
                }

                all_size += bytesRead;
                printf("read %zd bytes, all_size:%zd\n", bytesRead, all_size);
            } else if (active_events[i].filter == EVFILT_WRITE) {
                printf("event[%d]: EVFILT_WRITE\n", i);
                write(events[i].ident, "hello world\n", 12);
            } else if (active_events[i].filter == EVFILT_VNODE) {
                printf("event[%d]: EVFILT_VNODE\n", i);
                // 在这里处理定时器事件
            }
        }
    }

    close(fd);
    close(kq);
    return 0;
}

// g++ -std=c++11 -o test-kqueue ./test-kqueue.cpp  && ./test-kqueue ./tmp.txt