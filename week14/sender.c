#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_NAME "pipe"
#define BUFFER_SIZE 1024

int main() {
    char message[BUFFER_SIZE];

    printf("Sender aktif\n");

    while (1) {
        printf("Masukkan pesan: ");

        fgets(message, BUFFER_SIZE, stdin);

        message[strcspn(message, "\n")] = '\0';

        int fd = open(FIFO_NAME, O_WRONLY);

        write(fd, message, strlen(message));

        close(fd);

        if (strcmp(message, "exit") == 0)
            break;
    }

    return 0;
}
