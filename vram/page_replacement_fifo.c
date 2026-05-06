#include <stdio.h>
#include <string.h>

#define MAX_FRAMES  10
#define MAX_PAGES   50

int frames[MAX_FRAMES];
int num_frames;

int is_in_frames(int page) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == page) return 1;
    }
    return 0;
}

void print_frames(int step, int page, int is_fault) {
    printf("Step %2d | Page: %d | Frames: [", step, page);
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == -1)
            printf("  -");
        else
            printf("%3d", frames[i]);
        if (i < num_frames - 1) printf(" |");
    }
    printf(" ] %s\n", is_fault ? "<-- PAGE FAULT" : "");
}

int fifo(int pages[], int n) {
    int pointer    = 0;   /* pointer (index) frame berikutnya yang akan diganti */
    int page_faults = 0;

    for (int i = 0; i < num_frames; i++)
        frames[i] = -1;

    printf("\n=== FIFO PAGE REPLACEMENT (%d frames) ===\n", num_frames);
    printf("Reference string: ");
    for (int i = 0; i < n; i++) printf("%d ", pages[i]);
    printf("\n\n");

    for (int i = 0; i < n; i++) {
        int page     = pages[i];
        int is_fault = 0;

        /* PAGE FAULT */
        if (!is_in_frames(page)) {
            frames[pointer] = page;
            pointer         = (pointer + 1) % num_frames;
            page_faults++;
            is_fault        = 1;
        }

        print_frames(i + 1, page, is_fault);
    }

    printf("\nTotal Page Faults  : %d\n", page_faults);
    printf("Total Hits         : %d\n", n - page_faults);
    printf("Page Fault Rate    : %.2f%%\n",
           (float)page_faults / n * 100);

    return page_faults;
}

int main() {
    int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int n       = sizeof(pages) / sizeof(pages[0]);

    /* test 3 frame */
    num_frames = 3;
    int faults_3 = fifo(pages, n);

    /* test 4 frame, terjadi Belady's anomaly */
    num_frames = 4;
    int faults_4 = fifo(pages, n);

    printf("\n=== COMPARE ===\n");
    printf("3 frames: %d page faults\n", faults_3);
    printf("4 frames: %d page faults\n", faults_4);
    printf("\n");
    if (faults_4 > faults_3)
        printf("Terjadi Belady's Anomaly!\n");
    else
        printf("Kondisi normal.\n");

    return 0;
}