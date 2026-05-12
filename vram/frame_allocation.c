#include <stdio.h>

#define TOTAL_FRAMES 64
#define NUM_PROCESSES 4

int main() {
    int process_sizes[NUM_PROCESSES] = {10, 120, 40, 30}; // MB or KB
    int total_size = 0;
    int equal_allocation[NUM_PROCESSES];
    int proportional_allocation[NUM_PROCESSES];

    // Calculate total size
    for (int i = 0; i < NUM_PROCESSES; i++) {
        total_size += process_sizes[i];
    }

    printf("=== SIMULASI ALOKASI FRAME ===\n");
    printf("Total Frame Tersedia: %d\n", TOTAL_FRAMES);
    printf("Jumlah Proses       : %d\n\n", NUM_PROCESSES);

    // Equal Allocation
    int equal_frames = TOTAL_FRAMES / NUM_PROCESSES;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        equal_allocation[i] = equal_frames;
    }

    // Proportional Allocation
    for (int i = 0; i < NUM_PROCESSES; i++) {
        proportional_allocation[i] = (process_sizes[i] * TOTAL_FRAMES) / total_size;
    }

    // Print Results
    printf("%-10s | %-15s | %-15s | %-20s\n", "Proses", "Ukuran (KB)", "Equal Alloc", "Proportional Alloc");
    printf("----------------------------------------------------------------------\n");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("Process %d  | %-15d | %-15d | %-20d\n", 
            i+1, process_sizes[i], equal_allocation[i], proportional_allocation[i]);
    }

    printf("\n[Analisis]:\n");
    printf("- Pada Equal Allocation, Proses 2 yang berukuran besar (120 KB) mendapat frame sama dengan Proses 1 yang kecil (10 KB).\n");
    printf("- Pada Proportional Allocation, pembagian lebih adil sesuai kebutuhan memori masing-masing proses.\n");

    return 0;
}
