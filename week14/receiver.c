#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_NAME "pipe"
#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];

    mkfifo(FIFO_NAME, 0666);

    printf("Receiver aktif...\n");
    printf("Menunggu pesan...\n");

    while (1) {
        int fd = open(FIFO_NAME, O_RDONLY);

        int bytes = read(fd, buffer, BUFFER_SIZE);

        if (bytes > 0) {
            buffer[bytes] = '\0';

            if (strcmp(buffer, "exit") == 0) {
                printf("Receiver berhenti\n");
                close(fd);
                break;
            }

            printf("Pesan diterima: %s\n", buffer);
        }

        close(fd);
    }

    unlink(FIFO_NAME);

    return 0;
}
