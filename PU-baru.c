#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define MAXRANDOMVALUE 3
#define MAXPREV 500

/*============ Variable Global ============*/
int c[4],temp=0,len=0,score=0,highscore=0,count=0,ch=0;//COUNT WILL COUNT THE NO OF STEPS

int i,j,k,papan;

typedef struct{
    int skor;
    int highscore;
}player;

typedef struct {
    int Papan;
    char Inputan;
}games;

#define UKURAN_PAPAN 4
// mendeklarasikan konstanta untuk ukuran papan permainan

/*============ Deklarasi Modul ===========*/
int Papan[UKURAN_PAPAN][UKURAN_PAPAN]={0};
// mendeklarasikan array 2D untuk papan permainan

void DisplayPapan();
/*Prosedur menampilkan papan permainan 2048*/

void DisplayAwal();
/*Prosedur menampilkan tampilan menu awal permainan 2048*/

void DisplayCaraBermain();
/*Prosedur menampilkan aturan atau cara bermain permainan 2048*/

void ReadCaraBermain(char *cara);

char isValidCara(char isok[3]);

void gotoxy(int x, int y);

void loading(int bg, int fg, int panjang, int delay, int simbol[20]);

void Permainan();
/*Prosedur menampilkan permainan*/

void DisplayMenang();
/*Prosedur menampilkan tampilan menang permainan 2048*/

void DisplayKeluar();
/*Prosedur menampilkan tampilan sebelum pemain benar-benar keluar permainan 2048 di tengah jalannya games*/

void DisplayKalah();
/*Prosedur menampilkan tampilan ketika player kalah permainan 2048*/

void ReadAwal(char HowBegin[15]);

void DisplayLoading();
/*Prosedur menampilkan tampilan animasi loading*/

void papanmain();

void movevalue(int k);

int kosong(int n);

void angkaacak();

void rupdate();

void createprev(int ***p);

void updatearrtoprev(int ***p);

void UlangPermainan();

char GetAwal(char HowBegin[15]);

/*============ Body Program ============*/
int main(){
    system("color 8");
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
            Permainan();
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
    "> u -> ulang permainan\n" \
    "> m -> mundur langkah\n" \
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

int bg, fg, delay, panjang;
int simbol[20] = {2,3,4,5,6,14,16,22,35,36,62,64,158,174,175,176,177,178,219};
void DisplayLoading(){
    system("cls");
   loading(20 - 1, 19 - 1, 30 , 1, simbol);
   gotoxy(48,10);
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

void movevalue(int k){
    int i;
    if(k==3){
        return;
    }
    for(i=k;i<4;i++){
        if(c[i]!=0){
            movevalue(i+1);
            for(;i<4;i++){
                if(c[i+1]!=0){
                    break;
                }
                c[i+1]=c[i];
                c[i]=0;
            }
        }
    }
}

int kosong(int n){
    if(n==0){
        return len;
    }else{
        len++;
        kosong(n/10);
    }
}

void angkaacak(){
    int no;
    srand(time(NULL));
    int i,j; //RANDOM INDEX
    do{
    i=(rand ())%(MAXRANDOMVALUE+1);
    j=(rand ())%(MAXRANDOMVALUE+1);
    }while(Papan[i][j]!=0);

    no=((rand ()%10)+1);      //membuat angka random dari 1-10
    if (no>=1 && no<=10){
        Papan[i][j]=2;
    }
}

void rupdate(){
    int i,j;
    for(i=3;i>0;i--){
        if(c[i]==c[i-1]){
            c[i]+=c[i-1];                   //+=, isi sekaligus tambah
            score=score+c[i];
            if(score>highscore){

            }
            temp=1;
            c[i-1]=0;
        }else if(c[i-1]==0 && c[i]!=0){
            c[i-1]=c[i];
            c[i]=0;
            temp=1;
        }else if(c[i]==0){
            temp=1;
        }
    }
    movevalue(0);
}

void createprev(int ***p){
      int i,j,k;
      FILE *ptr;
      ptr=fopen("hstr.txt","a");
      fprintf(ptr,"%d ",score);
      fclose(ptr);

    if(count==MAXPREV+1){
        for(i=MAXPREV;i>0;i--){
            for(j=0;j<4;j++){
                for(k=0;k<4;k++){
                        p[i][j][k]=p[i-1][j][k];
                }
            }
        }
        count=MAXPREV;
    }
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            p[MAXPREV-count][i][j]=Papan[i][j];
        }
    }
}

void updatearrtoprev(int ***p){
    int data,i,j;
    if(count==0){
        printf("\n\t\t\t\t\t-------LANGKAH SEBELUMNYA TIDAK ADA-------");
        return;
    }
    FILE *ptr=fopen("hstr.txt","r+");
        for(i=0;i<count;i++){
            fscanf(ptr,"%d ",&data);
        }
        score=data;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            Papan[i][j]=p[MAXPREV-count][i][j];
        }
    }
    count--;
}

void UlangPermainan(){
    int i,j;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            Papan[i][j]=0;
        }
    }
    system("cls") ;
    score=0;
    angkaacak();
}

void Permainan(){
    system("cls") ;
    int i,j,k,m,n,same=0;
    char choice,s=-33,reschk;
    int ***p;
    p=(int ***)malloc(sizeof(int *)*(MAXPREV+1));
    for(int i=0;i<MAXPREV+1;i++){
        *(p+i)=(int **)malloc(sizeof(int *)*4);
    }
    for(int i=0;i<MAXPREV+1;i++){
        for(int j=0;j<4;j++){
            p[i][j]=(int *)malloc(sizeof(int)*4);
        }
    }
    createprev(p);

    FILE *ptr;
    ptr=fopen("highscore.txt","r");
    fscanf(ptr,"%d",&highscore);
    fclose(ptr);
    ptr=fopen("hstr.txt","w");
    fclose(ptr);
    angkaacak();
    papanmain();
    while(1){
        if(score>highscore){
            ptr=fopen("highscore.txt","w");
            fprintf(ptr,"%d",score);
            fclose(ptr);
        }
        choice=getch();
        if(choice=='D' || choice =='d'){
            count++;ch++;
              createprev(p);
            for(i=0;i<4;i++){
                for(j=0;j<4;j++){
                    c[j]=Papan[i][j];
                }
                rupdate();
                for(k=0;k<4;k++){
                    Papan[i][k]=c[k];
                }
            }
        }else if(choice=='a' || choice=='A'){
            count++;
            ch++;
            createprev(p);
            for(i=0;i<4;i++){
                for(j=3;j>=0;j--){
                    c[3-j]=Papan[i][j];
                }
                rupdate();
                for(k=0;k<4;k++){
                    Papan[i][3-k]=c[k];
                }
            }
        }else if(choice=='s' || choice =='S'){
            count++;ch++;
               createprev(p);
            for(i=0;i<4;i++){
                for(j=0;j<4;j++){
                    c[j]=Papan[j][i];
                }
                rupdate();
                for(k=0;k<4;k++){
                    Papan[k][i]=c[k];
                }
            }
        }else if(choice=='w' || choice=='W'){
            count++;ch++;
              createprev(p);
            for(i=0;i<4;i++){
                for(j=3;j>=0;j--){
                    c[3-j]=Papan[j][i];
                }
                rupdate();
                for(k=0;k<4;k++){
                  Papan[3-k][i]=c[k];
                }
            }
        }else if(choice=='m' || choice =='M'){
            updatearrtoprev(p);
            temp=8;
        }else if(choice=='u' || choice=='U'){
            count=0;
            UlangPermainan();
            papanmain();
            continue;
        }else if(choice=='k'||choice=='K'){
            exit(0);
        }
        if(temp==1){
            temp=0;
            system("cls") ;
            printf("\n%c\n",choice);
            angkaacak();
            papanmain();
        }else if(temp==8){
                temp=0;
                papanmain();
        }else{
            for(m=0;m<4;m++){
                for(n=3;n>0;n--){
                    if(Papan[m][n]==Papan[m][n-1] || Papan[m][n]==0 || Papan[m][n-1]==0){
                        same=1;
                        break;
                    }if(Papan[n][m]==Papan[n-1][m] || Papan[m][n]==0 || Papan[m][n-1]==0){
                        same=1;
                        break;
                    }
                }
                if(same==1)
                    break;
            }
            if(same==1){
                printf("\n\t\t\t\t\t============INVALID KEY==========\n");
                same=0;
            }else{
                printf("\n\t\t\t\t\t=============GAME OVER============");
                printf("\n\n\t\t\t\t\tWANT TO PLAY MORE?? Y/N??\n\t\t\t\t\t");
                reschk=getch();
                switch (reschk){
                    case 'Y':
                    case 'y':UlangPermainan(); papanmain();break;
                    case 'n':
                    case 'N':exit(0);
                }
                continue;
            }
        }
    }
    // return 0;
}

void papanmain(){
        int i,j,k,papan;
        printf("\n\t\t\t\t\t---------------2048---------------\n\n"); 
    printf("\t\t\t\t\t=================================\n");
    for (i=0;i<4;i++){
        for(j=0;j<4;j++){
            if(j==0){
                printf("\t\t\t\t\t|");
            }
            if(Papan[i][j]!=0){
                papan=kosong(Papan[i][j]);
                //printf("%d:",len);
                for(k=0;k<4-len;k++){
                    printf(" ");
                }
                printf("%d",Papan[i][j]);

                for(k=0;k<4-len;k++){
                    printf(" ");
                }
                for(k=0;k<len-1;k++){
                    printf(" ");
                }
                printf("|");
            }else{
                for(k=0;k<8-2*len-1;k++){
                printf(" ");}printf("|");
            }
            len=0;
        }
        if(i!=3){
            printf("\n");
            printf("\t\t\t\t\t=================================\n");
        }
    }
    printf("\n\t\t\t\t\t=================================\n");
    printf("\t\t\t\t\tSkor=%d\n\t\t\t\t\t",score);

          if(score<highscore){
              printf("High Score=%d\t\t\t\t\t\n",highscore);
          }else{
              highscore=score;
              printf("High Score=%d\t\t\t\t\t\n",highscore);
          }

    printf("\t\t\t\t\tMundur-> M\t\t\t\t\t\n");
    printf("\t\t\t\t\tUlangi-> U\t\t\t\t\t\n");
    printf("\t\t\t\t\tKeluar-> K\t\t\t\t\t\n");
    printf("\t\t\t\t\t(Masukkan: w | a | s | d )-->\n\t\t\t\t\t");
}

void DisplayPapan(){
    system("cls");
    printf("\n");
    printf("=====================\n");
    for (int i = 0; i < UKURAN_PAPAN; i++){
        for (int j = 0; j <UKURAN_PAPAN; j++){
            printf("|%4d", Papan[i][j]);
        }
        printf("|\n");
        printf("=====================\n");
    }
    printf("Skor :\n");
    printf("High Score :");
    printf("(Masukkan: w | a | s | d | k )--> \n");
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