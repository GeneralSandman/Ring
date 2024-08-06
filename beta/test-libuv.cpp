#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/event.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // 打开文件
    int fd = open(argv[1], O_RDONLY);
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
    struct kevent event;
    EV_SET(&event, fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    if (kevent(kq, &event, 1, NULL, 0, NULL) == -1) {
        perror("kevent");
        close(fd);
        close(kq);
        return 1;
    }

    struct timespec timeout = {
        .tv_sec  = 5,
        .tv_nsec = 0};

    // 异步读取文件
    char    buffer[BUFFER_SIZE];
    ssize_t all_size = 0;

    while (1) {
        printf("------\n");
        struct kevent events[1];
        int           nEvents = kevent(kq, NULL, 0, events, 1, &timeout);
        if (nEvents == -1) {
            perror("kevent");
            break;
        }

        if (nEvents == 0) {
            continue;
        }

        ssize_t bytesRead = read(events[0].ident, buffer, sizeof(buffer));
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
        // fwrite(buffer, 1, bytesRead, stdout);
    }

    close(fd);
    close(kq);
    return 0;
}

// g++ -std=c++11 -o a test-libuv.cpp && ./a ./test-libuv.cpp