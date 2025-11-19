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

