#define FUSE_USE_VERSION 31
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

static const char *filepath = "/rahasia.txt";
static const char *filecontent = "Ini adalah dokumen rahasia negara!\n";

/* =========================================
   SIMULASI KONTROL AKSES DI LEVEL FUSE
   ========================================= */
static int xmp_getattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi)
{
    int res = 0;
    memset(stbuf, 0, sizeof(struct stat));

    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    } else if (strcmp(path, filepath) == 0) {
        // Cek apakah yang mengakses adalah UID 1000
        if (fuse_get_context()->uid != 1000) {
            return -EACCES; // Permission Denied!
        }
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen(filecontent);
    } else {
        res = -ENOENT;
    }
    return res;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                       off_t offset, struct fuse_file_info *fi,
                       enum fuse_readdir_flags flags)
{
    if (strcmp(path, "/") != 0) return -ENOENT;

    filler(buf, ".", NULL, 0, 0);
    filler(buf, "..", NULL, 0, 0);
    
    // Secara sengaja menampilkan file rahasia di folder
    // Namun akses membacanya (cat) akan ditolak oleh getattr jika UID salah
    filler(buf, filepath + 1, NULL, 0, 0);

    return 0;
}

static int xmp_open(const char *path, struct fuse_file_info *fi)
{
    if (strcmp(path, filepath) != 0) return -ENOENT;
    
    // Ekstra proteksi saat membuka file
    if (fuse_get_context()->uid != 1000) {
        return -EACCES;
    }
    return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
                    struct fuse_file_info *fi)
{
    if (strcmp(path, filepath) != 0) return -ENOENT;
    
    size_t len = strlen(filecontent);
    if (offset < len) {
        if (offset + size > len) size = len - offset;
        memcpy(buf, filecontent + offset, size);
    } else {
        size = 0;
    }
    return size;
}

static const struct fuse_operations xmp_oper = {
    .getattr    = xmp_getattr,
    .readdir    = xmp_readdir,
    .open       = xmp_open,
    .read       = xmp_read,
};

int main(int argc, char *argv[])
{
    return fuse_main(argc, argv, &xmp_oper, NULL);
}
