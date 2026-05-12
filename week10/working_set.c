#include <stdio.h>
#include <stdbool.h>

#define DELTA 4
#define REF_STR_LEN 15

int main() {
    int ref_string[REF_STR_LEN] = {2, 6, 1, 5, 7, 7, 7, 5, 1, 6, 2, 3, 4, 1, 2};
    
    printf("=== SIMULASI WORKING SET MODEL ===\n");
    printf("Reference String Length : %d\n", REF_STR_LEN);
    printf("Window Size (DELTA)     : %d\n\n", DELTA);
    
    printf("Time(t)\t | Window Content\t\t | Working Set\t | WSS (Size)\n");
    printf("-----------------------------------------------------------------------\n");
    
    for (int t = 0; t < REF_STR_LEN; t++) {
        int ws[DELTA];
        int wss = 0;
        
        // Populate window
        int window_start = (t - DELTA + 1 > 0) ? (t - DELTA + 1) : 0;
        
        printf("t=%-6d | [", t);
        
        // Print window content
        for (int i = window_start; i <= t; i++) {
            printf("%d ", ref_string[i]);
            
            // Check if page is already in Working Set
            bool found = false;
            for(int j = 0; j < wss; j++) {
                if(ws[j] == ref_string[i]) {
                    found = true;
                    break;
                }
            }
            if(!found) {
                ws[wss++] = ref_string[i];
            }
        }
        
        // Padding for formatting
        for (int i = 0; i < DELTA - (t - window_start + 1); i++) printf("  ");
        printf("]\t\t | {");
        
        // Print Working set
        for(int i = 0; i < wss; i++) {
            printf("%d", ws[i]);
            if (i < wss - 1) printf(",");
        }
        
        // Padding for formatting
        for (int i = 0; i < (DELTA*2) - (wss*2); i++) printf(" ");
        
        printf("}\t | %d\n", wss);
    }
    
    printf("\n[Analisis]:\n");
    printf("- Perhatikan bagaimana WSS berubah membesar dan mengecil tergantung lokasi referensi.\n");
    printf("- Thrashing terjadi jika Total WSS dari semua proses > Total Frame Fisik.\n");

    return 0;
}
