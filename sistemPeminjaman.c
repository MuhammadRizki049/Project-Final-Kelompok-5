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
        case 0:
            printf("Keluar dari menu user.\n");
            break;
        default:
            printf("Pilihan tidak valid.\n");
            goto ulang;
        }
    } while (menu != 0);
}

void menuAdmin() {
    int menu;
    do {
        printf("\n=== MENU ADMIN ===\n");
        printf("1. Lihat Alat\n");
        printf("2. Lihat Pinjaman\n");
        printf("3. Tambah Alat\n");
        printf("4. Hapus Alat\n");
        printf("5. Edit Alat\n");
        printf("0. Keluar Dari Menu Admin\n");
        ulang:
        printf("Pilih menu: ");
        scanf("%d", &menu);

        switch (menu) {
        case 1:
            listAlat();
            break;
        case 2:
            lihatAlat();
            break;
        case 3:
            tambahAlat();
            break;
        case 4:
            hapusAlat();
            break;
        case 5:
            editAlat();
            break;
        case 0:
            printf("Keluar dari menu admin.\n");
            break;
        default:
            printf("Pilihan tidak valid.\n");
            goto ulang;
        }
    } while (menu != 0);
}

void lihatAlat() {
    FILE *file;
    Alat alat;
    file = fopen("dipinjam.txt", "r");
    char baris[256];

    if (file == NULL) {
        printf("File dipinjam.txt tidak ditemukan atau belum ada yang dipinjam.\n");
        return;
}

    int c = fgetc(file);
    if (c == EOF) {
        fclose(file);
        printf("Belum ada yang dipinjam.\n");
        return;
    }
    ungetc(c, file);

    printf("=======================================================================================\n");
    printf("                          Data Alat Laboratorium Yang Dipinjam\n");
    printf("=======================================================================================\n");
    printf("%-3s | %-15s | %-10s | %-10s | %-10s | %-6s | %-8s\n",
            "Id", "Nama Alat", "Merek", "Model", "Tahun", "Jumlah", "Dipinjam");
    printf("=======================================================================================\n");
    while (fgets(baris, sizeof(baris), file)) {
        if (sscanf(baris, "%u|%49[^|]|%49[^|]|%49[^|]|%u|%u|%u",
                    &alat.id, alat.nama, alat.merek, alat.model,
                    &alat.tahun, &alat.jumlah, &alat.tersedia) == 7) {
            printf("%2u | %-13s | %-10s | %-9s | %-10u | %-6u | %-8u\n",
                    alat.id, alat.nama, alat.merek, alat.model,
                    alat.tahun, alat.jumlah, alat.tersedia);
        }
    }
    printf("=======================================================================================\n");
    fclose(file);
}
void listAlat() {
    FILE *file;
    file = fopen("alat.txt", "r");
    Alat alat;

    if (file == NULL) {
        printf("File alat.txt tidak dapat ditemukan\n");
        return;
    }
    printf("\n=== DAFTAR ALAT LABORATORIUM YANG TERSEDIA ===\n");
    printf("ID      | NAMA        | MEREK    | MODEL   | TAHUN PRODUKSI   | JUMLAH UNIT   | TERSEDIA   \n");

    while (fscanf(file, "%u|%49[^|]|%49[^|]|%49[^|]|%u|%u|%u\n",
                &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah, &alat.tersedia) == 7) {
        printf("%2u | %-13s | %-10s | %-9s | %-18u | %-15u | %-12u\n",
                alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah, alat.tersedia);
    }
    fclose(file);
}
void pinjamAlat() {
    Alat alat;
    unsigned int id;
    unsigned int jumlahInginDipinjam;
    listAlat();

    printf("Masukkan id alat yang ingin dipinjam: ");
    scanf("%u", &id);

    printf("Jumlah alat yang ingin dipinjam: ");
    scanf("%u", &jumlahInginDipinjam);

    FILE *fAlat = fopen("alat.txt", "r");
    if (fAlat == NULL) {
        printf("Gagal membuka file alat.txt!\n");
        return;
    }

    FILE *tempAlat = fopen("tempAlat.txt", "w");
    if (tempAlat == NULL) {
        printf("Gagal membuka file tempAlat.txt!\n");
        fclose(fAlat);
        return;
    }
int found = 0;
    while (fscanf(fAlat, "%u|%49[^|]|%49[^|]|%49[^|]|%u|%u|%u\n",
                &alat.id, alat.nama, alat.merek, alat.model, &alat.tahun, &alat.jumlah, &alat.tersedia) == 7) {
        if (alat.id == id && alat.tersedia >= jumlahInginDipinjam) {
            alat.tersedia -= jumlahInginDipinjam;
            found = 1;
        }
        fprintf(tempAlat, "%u|%s|%s|%s|%u|%u|%u\n",

    alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah, alat.tersedia);
    }
    fclose(fAlat);
    fclose(tempAlat);
    remove("alat.txt");
    rename("tempAlat.txt", "alat.txt");

    if (!found) {
        printf("Alat tidak ditemukan atau jumlah tersedia kurang!\n");
        return;
    }

    FILE *pinjam = fopen("dipinjam.txt", "r");
    FILE *tempPinjam = fopen("tempPinjam.txt", "w");
    if (tempPinjam == NULL) {
        printf("Gagal membuka file tempPinjam.txt!\n");
        if (pinjam) fclose(pinjam);
        return;
    }






