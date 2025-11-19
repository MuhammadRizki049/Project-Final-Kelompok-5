#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void menuUser();
void menuAdmin();
void tambahAlat();
void hapusAlat();
void editAlat();
void pinjamAlat();
void kembalikanAlat();
void lihatAlat();
void listAlat();

typedef struct {
    unsigned int id;
    char nama[50];
    char merek[50];
    char model[50];
    unsigned int tahun;
    unsigned int jumlah;
    unsigned int tersedia;
} Alat;

typedef struct {
    char simpan[100], nama[50], merek[50], model[50];
    unsigned int id, tahun, jumlah, tersedia;
} data;

int main(int argc, char *argv[]) {
    char username[50];
    char password[50];
    char role[10];

    FILE *fp = fopen("akun.txt", "r");
    if (fp == NULL) {
        printf("File akun.txt tidak ditemukan.\n");
        return 1;
    }
    int found = 0;
    while (fscanf(fp, "%s %s %s", username, password, role) == 3) {
        if (argc == 3 && strcmp(argv[1], username) == 0 && strcmp(argv[2], password) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (!found) {
        printf("Login gagal!\n");
        return 0;
    }
    printf("Login berhasil sebagai %s!\n", argv[1]);

    if (strcmp(role, "admin") == 0) {
        menuAdmin();
    } else if (strcmp(role, "user") == 0) {
        menuUser();
    }
    return 0;
}

void menuUser() {
    int menu;
    do {
 printf("\n=== MENU USER ===\n");
        printf("1. List Alat Yang Tersedia\n");
        printf("2. Peminjaman Alat\n");
        printf("3. List Alat Yang Dipinjam\n");
        printf("4. Pengembalian Alat\n");
        printf("0. Keluar Dari Menu User\n");
        ulang:
        printf("Pilih menu: ");
        scanf("%d", &menu);

        switch (menu) {
        case 1:
            listAlat();
            break;
        case 2:
            pinjamAlat();
            break;
        case 3:
            lihatAlat();
            break;
        case 4:
            kembalikanAlat();
            break;


