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
}
