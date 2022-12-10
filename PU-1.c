#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>


/*============ Variable Global ============*/
char how_or_begin[15];

typedef struct{
    int skor;
    int highscore;
}player;

typedef struct {
    int Papan;
    char Inputan;
}games;

int bg, fg, delay, panjang;
int simbol[20] = {2,3,4,5,6,14,16,22,35,36,62,64,158,174,175,176,177,178,219};

void gotoxy(int x, int y);
void loading(int bg, int fg, int panjang, int delay, int simbol[20]);

#define UKURAN_PAPAN 4
// mendeklarasikan konstanta untuk ukuran papan permainan

int Papan[UKURAN_PAPAN][UKURAN_PAPAN];
// mendeklarasikan array 2D untuk papan permainan

/*============ Deklarasi Modul ===========*/

void DisplayPapan();
/*Prosedur menampilkan papan permainan 2048*/

void DisplayAwal();
/*Prosedur menampilkan tampilan menu awal permainan 2048*/

void DisplayCaraBermain();
/*Prosedur menampilkan aturan atau cara bermain permainan 2048*/

void ReadCaraBermain(char *cara);

char isValidCara(char isok[3]);

void DisplayMenang();
/*Prosedur menampilkan tampilan menang permainan 2048*/

void DisplayKeluar();
/*Prosedur menampilkan tampilan sebelum pemain benar-benar keluar permainan 2048 di tengah jalannya games*/

void DisplayKalah();
/*Prosedur menampilkan tampilan ketika player kalah permainan 2048*/

void ReadAwal(char HowBegin[15]);

void DisplayLoading();
/*Prosedur menampilkan tampilan animasi loading*/

char GetAwal(char HowBegin[15]);

/*============ Body Program ============*/
int main(){
    system("color 8");
    gotoxy(40,40);
    char opsi, hb[15],cr[5];
        start:
    ReadAwal(hb);
    opsi = GetAwal(hb);
    // while(opsi=='A' || opsi=='B' || opsi=='C'){
        switch (opsi){
          case 'A': 
            ReadCaraBermain(cr);
            goto start;
          break;
          case 'B':
            DisplayLoading();
            DisplayPapan();
          break;
          default: printf("Masukkan Tidak Valid");
          getch();
          goto start;
          break;
        }
        // ReadAwal(hb);
        // opsi = GetAwal(hb);
    // }
}


/*============ Body Modul ============*/
void DisplayAwal(){
    system("cls");
    printf(" \n \
   _ _ _ _    _ _ _ _                 _ _ _ _\n" \
"           |  |       |   |       |   |       |\n" \
"           |  |       |   |       |   |       |\n" \
"    _ _ _ _|  |       |   |_ _ _ _|   |_ _ _ _|\n" \
"   |          |       |           |   |       |\n" \
"   |          |       |           |   |       |\n" \
"   |_ _ _ _   |_ _ _ _|           |   |_ _ _ _|\n" \
" \n" \
"               ------------------\n" \
"                      MAIN \n" \
"               ------------------ \n" \
" \n" \
"Ketik 'mulai' atau 'cara bermain': ");
}

void ReadAwal(char HowBegin[15]){
    DisplayAwal();
    scanf(" %[^\n]%*c", HowBegin);
}

char GetAwal(char HowBegin[15]){
    char how[]="cara bermain";
    char begin[]="mulai";
    char result;
    if (strcmp(HowBegin,how)==0){
        result='A';
    } else if (strcmp(HowBegin,begin)==0){
        result='B';
    } else{
        result='C';
    }
    return(result);
}

void DisplayCaraBermain(){
    system("cls");
    printf("\n| CARA BERMAIN |\n" \
    "\n" \
    "> w -> up\n" \
    "> s -> down\n" \
    "> d -> right\n" \
    "> a -> left\n" \
    "> k -> keluar\n" \
    "> tekan tombol enter untuk eksekusi\n" \
    "\n" \
    "Ketik 'ok' jika mengerti: ");
}

void ReadCaraBermain(char *cara){
    char isok[3];
    char NotOk='X',ok;
    do{
    DisplayCaraBermain();
    scanf( "%[^\n]%*c",isok);
    ok = isValidCara(isok);
    }while (ok == NotOk);
}

char isValidCara(char isok[3]){
    char valid[]="ok";
    int ok;
    if (strcmp(isok,valid)==0){
        return 'V';
    }else if(strcmp(isok,valid)!=0){
        return 'X';
    }
}

void DisplayLoading(){
    system("cls");
   loading(20 - 1, 19 - 1, 30 , 1, simbol);
   gotoxy(48,10);
//    printf("TEKAN ENTER UNTUL KELUAR");
//    getch();
}

void loading(int bg, int fg, int panjang, int delay, int simbol[20]){
 int k, l;
   for (k=0; k<=panjang; k+=2)
   {
      gotoxy(48,10);
      printf("\n\tLOADING\n\t");
      for (l=0; l<k; l++){
         printf("%c", simbol[fg]);
      }
      for (l=0; l<panjang-1; l++){
         printf("%c", simbol[bg]);
      Sleep(delay);
      }
   }
}

void gotoxy(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void DisplayPapan(){
    system("cls");
    printf("\n");
    printf("=====================\n");
  for (int i = 0; i < UKURAN_PAPAN; i++) {
    for (int j = 0; j <UKURAN_PAPAN; j++) {
      printf("|%4d", Papan[i][j]);
    }
    printf("|\n");
    printf("=====================\n");
  }
    printf("(Masukkan: w | a | s | d | k )--> \n");
    printf("Skor :\n");
    printf("High Skor :");
  getch();
}

void DisplayMenang(){
    system("cls");
    printf("\n" \
    " =========================\n" \
"|                         |\n" \
"|   WoooW kamu berhasil   |\n" \
"|     keren banget!!      |\n" \
"|       (～￣▽￣)/        |\n" \
"|                         |\n" \
" =========================\n");
}

void DisplayKeluar(){
    system("cls");
    printf("\n" \
    " =========================\n" \
"|                         |\n" \
"|    Apakah kamu yakin?   |\n" \
"|                         |\n" \
"|      Ketik (y/n):       |\n" \
"|                         |\n" \
" =========================\n");
}

void DisplayKalah(){
    system("cls");
    printf("\n" \
    " =========================\n" \
"|                         |\n" \
"|    Yaahhh kamu kalah    |\n" \
"| coba lagi permainannya! |\n" \
"|      skor kamu          |\n" \
"|                         |\n" \
" =========================\n");
}