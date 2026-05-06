#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES  50

int frames[MAX_FRAMES];
int last_used[MAX_FRAMES];
int num_frames;

int is_in_frames(int page, int *index) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == page) {
            *index = i;
            return 1;
        }
    }
    return 0;
}

int find_empty_frame() {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == -1)
            return i;
    }
    return -1;
}

int find_lru_frame() {
    int lru_idx  = 0;
    int min_time = last_used[0];

    for (int i = 1; i < num_frames; i++) {
        if (last_used[i] < min_time) {
            min_time = last_used[i];
            lru_idx  = i;
        }
    }

    return lru_idx;
}

void print_frames(int step, int page, int is_fault) {
    printf("Step %2d | Page: %d | Frames: [", step, page);

    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == -1)
            printf("  -");
        else
            printf("%3d", frames[i]);

        if (i < num_frames - 1)
            printf(" |");
    }

    printf(" ] %s\n", is_fault ? "<-- PAGE FAULT" : "");
}

int lru(int pages[], int n) {
    int time         = 0;
    int page_faults  = 0;

    /* init frame */
    for (int i = 0; i < num_frames; i++) {
        frames[i]    = -1;
        last_used[i] = 0;
    }

    printf("\n=== LRU PAGE REPLACEMENT (%d frames) ===\n",
           num_frames);

    printf("Reference string: ");
    for (int i = 0; i < n; i++)
        printf("%d ", pages[i]);

    printf("\n\n");

    for (int i = 0; i < n; i++) {
        int page      = pages[i];
        int is_fault  = 0;
        int idx;

        time++;

        /* PAGE HIT */
        if (is_in_frames(page, &idx)) {
            last_used[idx] = time;
        }

        /* PAGE FAULT */
        else {
            is_fault = 1;
            page_faults++;

            int empty = find_empty_frame();

            /* assign ke frame kosong */
            if (empty != -1) {
                frames[empty]    = page;
                last_used[empty] = time;
            }

            /* replace page lru */
            else {
                int lru_idx = find_lru_frame();

                printf("         Replace page %d "
                       "(frame %d)\n",
                       frames[lru_idx],
                       lru_idx);

                frames[lru_idx]    = page;
                last_used[lru_idx] = time;
            }
        }

        print_frames(i + 1, page, is_fault);
    }

    printf("\nTotal Page Faults  : %d\n", page_faults);
    printf("Total Hits         : %d\n", n - page_faults);
    printf("Page Fault Rate    : %.2f%%\n",
           (float) page_faults / n * 100);

    return page_faults;
}

int main() {
    int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};

    int n = sizeof(pages) / sizeof(pages[0]);

    /* test 3 frame */
    num_frames = 3;
    int faults_3 = lru(pages, n);

    /* test 4 frame */
    num_frames = 4;
    int faults_4 = lru(pages, n);

    printf("\n=== COMPARE ===\n");
    printf("3 frames: %d page faults\n", faults_3);
    printf("4 frames: %d page faults\n", faults_4);

    return 0;
}