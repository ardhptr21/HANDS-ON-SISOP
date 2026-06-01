#include <stdio.h>
#include <string.h>

void secret_function() {
    printf("[!] KAMU BERHASIL MASUK KE FUNGSI RAHASIA (ARBITRARY CODE EXECUTION)!\n");
}

int main() {
    char password[8];
    printf("Masukkan sandi: ");
    
    // Fungsi rentan: tidak mengecek batas panjang input
    gets(password); 
    
    if(strcmp(password, "AAAA") == 0) {
        printf("[+] Sandi diterima, buffer aman!\n");
    } else {
        printf("[-] Sandi salah atau buffer meluber!\n");
    }
    
    return 0;
}
