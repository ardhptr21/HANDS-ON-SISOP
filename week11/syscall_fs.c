#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {

    char buffer[100];

    printf("=== OPEN FILE ===\n");

    // OPEN / CREATE FILE
    int fd = open("demo.txt", O_CREAT | O_RDWR, 0644);

    printf("File Descriptor: %d\n", fd);

    printf("\n=== WRITE FILE ===\n");

    write(fd, "Hello Filesystem\n", 17);

    printf("Data written.\n");

    printf("\n=== RESET OFFSET ===\n");

    lseek(fd, 0, SEEK_SET);

    printf("\n=== READ FILE ===\n");

    int n = read(fd, buffer, sizeof(buffer));

    write(STDOUT_FILENO, buffer, n);

    printf("\n=== FILE METADATA ===\n");

    struct stat st;

    stat("demo.txt", &st);

    printf("Inode      : %ld\n", st.st_ino);
    printf("Size       : %ld bytes\n", st.st_size);
    printf("Permission : %o\n", st.st_mode & 0777);

    printf("\n=== PROCESS SLEEP 30s ===\n");

    printf("Check opened file using:\n");
    printf("ls -l /proc/%d/fd\n", getpid());

    sleep(30);

    printf("\n=== CLOSE FILE ===\n");

    close(fd);

    return 0;
}
