#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILE_PATH "test_mmap.txt"

int main() {
    int fd;
    char *mapped_mem;
    struct stat file_info;
    const char *text = "HALO INI ADALAH TEKS ASLI DARI FILE SEBELUM DI-MMAP.\n";
    
    printf("=== SIMULASI MEMORY-MAPPED FILE ===\n\n");
    
    // 1. Buat file dummy
    fd = open(FILE_PATH, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) { perror("open"); return 1; }
    write(fd, text, strlen(text));
    
    // Dapatkan ukuran file
    fstat(fd, &file_info);
    printf("1. File '%s' dibuat dengan isi:\n   -> %s", FILE_PATH, text);
    
    // 2. Map file ke memori (Virtual Address Space)
    mapped_mem = mmap(NULL, file_info.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_mem == MAP_FAILED) { perror("mmap"); close(fd); return 1; }
    printf("\n2. File dipetakan ke alamat memori: %p\n", mapped_mem);
    
    // 3. Ubah isi file via POINTER MEMORI (Tanpa fungsi write!)
    printf("\n3. Mengubah isi file langsung melalui pointer memori...\n");
    const char *new_text = "TEKS INI BERUBAH KARENA DI-MODIFIKASI MELALUI MMAP!!";
    
    // Menggunakan memcpy/strncpy untuk mengubah memory
    strncpy(mapped_mem, new_text, strlen(new_text));
    
    // 4. Unmap dan tutup
    munmap(mapped_mem, file_info.st_size);
    close(fd);
    
    // 5. Buktikan isi file di disk ikut berubah
    printf("\n4. Membaca ulang isi file dari disk:\n");
    fd = open(FILE_PATH, O_RDONLY);
    if (fd == -1) { perror("open read"); return 1; }
    
    char buffer[100] = {0};
    read(fd, buffer, sizeof(buffer));
    printf("   -> %s\n", buffer);
    close(fd);
    
    printf("\n[Kesimpulan]: File di disk ikut berubah padahal kita hanya memodifikasi array di memori!\n");
    
    return 0;
}
