#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_KELIME_UZUNLUK 30
#define MAX_KELIME_SAYISI 200
#define MAX_HATA 6

/* ---------- FONKSIYON PROTOTIPLERI ---------- */
void ekranTemizle();
void menuGoster();
int kategoriSec();
void kategoriDosyasiBul(int kategori, char dosyaAdi[]);
void kelimeleriOku(char dosyaAdi[], char kelimeler[][MAX_KELIME_UZUNLUK], int *kelimeSayisi);
void rastgeleKelimeSec(char kelimeler[][MAX_KELIME_UZUNLUK], int kelimeSayisi, char secilenKelime[]);
void gizliKelimeOlustur(char secilenKelime[], char gizliKelime[]);
void gizliKelimeYazdir(char gizliKelime[]);
int harfGecerliMi(char ch);
int dahaOnceGirildiMi(char girilenHarfler[], int girilenSayisi, char harf);
int harfKontrolEt(char secilenKelime[], char gizliKelime[], char harf);
int oyunBittiMi(char gizliKelime[]);
void adamCiz(int hata);
int rekorOku();
void rekorGuncelle(int yeniPuan);
void kullanilanHarfleriYazdir(char girilen[], int sayi);

/* ---------- MENU ---------- */
void menuGoster() {
    printf("====================================\n");
    printf("      KELIME BULMACA - ADAM ASMACA   \n");
    printf("====================================\n");
    printf("1) Meslekler\n");
    printf("2) Meyveler\n");
    printf("3) Sehirler\n");
    printf("4) Ulkeler\n");
    printf("------------------------------------\n");
    printf("Seciminiz (1-4): ");
}

int kategoriSec() {
    char satir[20];
    int secim;
    while (1) {
        menuGoster();
        fgets(satir, sizeof(satir), stdin);
        secim = atoi(satir);
        if (secim >= 1 && secim <= 4)
            return secim;
        printf("Hatali secim!\n");
    }
}

void kategoriDosyasiBul(int kategori, char dosyaAdi[]) {
    if (kategori == 1) strcpy(dosyaAdi, "meslekler.txt");
    else if (kategori == 2) strcpy(dosyaAdi, "meyveler.txt");
    else if (kategori == 3) strcpy(dosyaAdi, "sehirler.txt");
    else strcpy(dosyaAdi, "ulkeler.txt");
}

/* ---------- MAIN ---------- */
int main() {
    srand((unsigned)time(NULL));
    ekranTemizle();

    char dosyaAdi[50];
    char kategoriAdi[20];

    char kelimeler[MAX_KELIME_SAYISI][MAX_KELIME_UZUNLUK];
    int kelimeSayisi = 0;

    char secilenKelime[MAX_KELIME_UZUNLUK];
    char gizliKelime[MAX_KELIME_UZUNLUK];

    char girilenHarfler[30];
    int girilenSayisi = 0;

    int hata = 0;
    int puan = 0;

    int kategori = kategoriSec();
    kategoriDosyasiBul(kategori, dosyaAdi);

    if (kategori == 1) strcpy(kategoriAdi, "Meslekler");
    else if (kategori == 2) strcpy(kategoriAdi, "Meyveler");
    else if (kategori == 3) strcpy(kategoriAdi, "Sehirler");
    else strcpy(kategoriAdi, "Ulkeler");

    kelimeleriOku(dosyaAdi, kelimeler, &kelimeSayisi);

    if (kelimeSayisi == 0) {
        printf("HATA: dosyadan hic kelime okunamadi!\n");
        return 1;
    }

    rastgeleKelimeSec(kelimeler, kelimeSayisi, secilenKelime);
    gizliKelimeOlustur(secilenKelime, gizliKelime);

    char satir[20];
    char harf;
    int rekor;

    while (hata < MAX_HATA) {
        rekor = rekorOku();
        printf("\nKategori: %s | Puan: %d | Rekor: %d\n",
               kategoriAdi, puan, rekor);
        printf("-------------------------------------------\n");

        gizliKelimeYazdir(gizliKelime);
        kullanilanHarfleriYazdir(girilenHarfler, girilenSayisi);
        printf("-------------------------------------------\n");

        printf("Bir harf giriniz: ");
        fgets(satir, sizeof(satir), stdin);
        harf = satir[0];

        if (!harfGecerliMi(harf)) {
            printf("Uyari: Lutfen sadece harf giriniz!\n");
            continue;
        }

        if (harf >= 'a' && harf <= 'z')
            harf -= 32;

        if (dahaOnceGirildiMi(girilenHarfler, girilenSayisi, harf)) {
            printf("Bu harfi daha once girdiniz!\n");
            continue;
        }

        girilenHarfler[girilenSayisi++] = harf;

        int bulunan = harfKontrolEt(secilenKelime, gizliKelime, harf);

        if (bulunan > 0) {
            puan += bulunan * 10;
            printf("Dogru tahmin!\n");
        } else {
            hata++;
            puan -= 5;
            if (puan < 0) puan = 0;
            printf("Yanlis tahmin!\n");
            adamCiz(hata);
        }

        if (oyunBittiMi(gizliKelime)) {
            printf("\nTebrikler! Kazandiniz!\n");
            break;
        }
    }

    if (hata >= MAX_HATA) {
        printf("\nKaybettiniz!\n");
        printf("Dogru kelime: %s\n", secilenKelime);
    }

    printf("Final Puaniniz: %d\n", puan);

    rekor = rekorOku();
    if (puan > rekor) {
        printf("Yeni Rekor!\n");
        rekorGuncelle(puan);
    } else {
        printf("Onceki Rekor: %d\n", rekor);
    }

    return 0;
}

/* ---------- YARDIMCI FONKSIYONLAR ---------- */
void ekranTemizle() {
    system("clear");
}

void kelimeleriOku(char dosyaAdi[], char kelimeler[][MAX_KELIME_UZUNLUK], int *kelimeSayisi) {
    FILE *dosya = fopen(dosyaAdi, "r");
    char satir[MAX_KELIME_UZUNLUK];
    *kelimeSayisi = 0;

    if (!dosya) return;

    while (fgets(satir, sizeof(satir), dosya)) {
        satir[strcspn(satir, "\n")] = '\0';
        strcpy(kelimeler[*kelimeSayisi], satir);
        (*kelimeSayisi)++;
    }
    fclose(dosya);
}

void rastgeleKelimeSec(char kelimeler[][MAX_KELIME_UZUNLUK], int kelimeSayisi, char secilenKelime[]) {
    int index = rand() % kelimeSayisi;
    strcpy(secilenKelime, kelimeler[index]);
}

void gizliKelimeOlustur(char secilenKelime[], char gizliKelime[]) {
    int i;
    for (i = 0; secilenKelime[i]; i++)
        gizliKelime[i] = '_';
    gizliKelime[i] = '\0';
}

void gizliKelimeYazdir(char gizliKelime[]) {
    printf("KELIME: ");
    for (int i = 0; gizliKelime[i]; i++)
        printf("%c ", gizliKelime[i]);
    printf("\n");
}

int harfGecerliMi(char ch) {
    return isalpha(ch); 
}1 

int dahaOnceGirildiMi(char girilenHarfler[], int girilenSayisi, char harf) {
    for (int i = 0; i < girilenSayisi; i++)
        if (girilenHarfler[i] == harf) return 1;
    return 0;
}

int harfKontrolEt(char secilenKelime[], char gizliKelime[], char harf) {
    int bulunan = 0;3
    for (int i = 0; secilenKelime[i]; i++) {
        if (secilenKelime[i] == harf && gizliKelime[i] == '_') {
            gizliKelime[i] = harf;
            bulunan++;
        }
    }
    return bulunan;
}

int oyunBittiMi(char gizliKelime[]) {
    for (int i = 0; gizliKelime[i]; i++)
        if (gizliKelime[i] == '_') return 0;
    return 1;
}

void adamCiz(int hata) {
    if (hata >= 1) printf(" |\n");
    if (hata >= 2) printf(" O\n");
    if (hata >= 3) printf(" |\n");
    if (hata >= 4) printf("/| \n");
    if (hata >= 5) printf("/|\\\n");
    if (hata >= 6) printf("/ \\\n");
}

int rekorOku() {
    FILE *dosya = fopen("rekor.txt", "r");
    int r = 0;
    if (dosya) {
        fscanf(dosya, "%d", &r);
        fclose(dosya);
    }
    return r;
}

void rekorGuncelle(int yeniPuan) {
    FILE *dosya = fopen("rekor.txt", "w");
    if (dosya) {
        fprintf(dosya, "%d", yeniPuan);
        fclose(dosya);
    }
}

void kullanilanHarfleriYazdir(char girilen[], int sayi) {
    printf("Kullanilanlar: [ ");
    for (int i = 0; i < sayi; i++)
        printf("%c ", girilen[i]);
    printf("]\n");
}
