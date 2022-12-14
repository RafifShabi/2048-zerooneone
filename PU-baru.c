#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

/*============ Variable Global ============*/
int c[4],temp=0,len=0,score=0,highscore=0,count=0,ch=0;

int i,j,k,papan;

typedef struct{
    int skor;
    int highscore;
}player;

typedef struct {
    int Papan;
    char Inputan;
}games;

#define MAXRANDOMVALUE 3
//mendeklarasikan konstanta untuk
#define MAXPREV 500
// mendeklarasikan konstanta untuk 
#define UKURAN_PAPAN 4
// mendeklarasikan konstanta untuk ukuran papan permainan

/*============ Deklarasi Modul ===========*/
int Papan[UKURAN_PAPAN][UKURAN_PAPAN]={0};
/*mendeklarasikan array 2D untuk papan permainan*/

void DisplayAwal();
/*Prosedur menampilkan tampilan menu awal permainan 2048*/

void ReadAwal(char HowBegin[15]);
/*Prosedur membaca perintah "mulai" atau "cara bermain"*/

char GetAwal(char HowBegin[15]);
/*Fungsi memproses perintah dari prosedur ReadAwal untuk dikonversi dan dipakai pada case*/

void DisplayCaraBermain();
/*Prosedur menampilkan aturan atau cara bermain permainan 2048*/

void ReadCaraBermain(char *cara);
/*Prosedur berisi kumpulan modul jika memilih perintah "cara bermain"*/

char isValidCara(char isok[3]);
/*Fungsi mengembalikan karakter tertentu jika masukan dari ReadCaraBermain adalah "ok"*/

void DisplayLoading();
/*Prosedur kumpulan modul untuk menampilkan tampilan loading*/

void loading(int bg, int fg, int panjang, int delay, int simbol[20]);
/*prosedur membentuk tampilan loading yang bergerak karena looping*/

void gotoxy(int x, int y);
/*Prosedur koordinat pada terminal ketika program dijalankan*/

void papanmain();
/*Prosedur menampilkan papan permainan 2048*/

void movevalue(int k);
/*prosedur */

int kosong(int n);
/*Prosedur */

void AcakAngka();
/*Prosedur mengacak angka dan indeks untuk memunculkan angka 2*/

void rupdate();

void createprev(int ***p);
/*Prosedur membuat riwayat jalannya permainan agar dapat melakukan mundur langkah*/

void updatearrtoprev(int ***p);
/*Prosedur memperbarui tampilan papan ketika pemain ingin mundur langkah*/

void UlangPermainan();
/*Prosedur untuk mengulangi permainan*/

void Permainan();
/*Prosedur menjalankan permainan mulai dari perintah (w, a, s, d, k, u, m) 
serta file untuk menyimpan highscore dan mundur langkah*/

void papanmain();
/*Prosedur menampilkan papan permainan*/

void DisplayMenang();
/*Prosedur menampilkan tampilan menang permainan 2048*/

void DisplayKeluar();
/*Prosedur menampilkan tampilan sebelum pemain benar-benar keluar dari permainan 2048 di tengah jalannya games*/

void DisplayKalah();
/*Prosedur menampilkan tampilan ketika player kalah permainan 2048*/

void GetKalah();
/*Prosedur menampilkan nilai yang diperoleh pemain ketika pemain kalah*/

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
\t\t\t\t    _ _ _ _    _ _ _ _                 _ _ _ _\n" \
"\t\t\t\t           |  |       |   |       |   |       |\n" \
"\t\t\t\t           |  |       |   |       |   |       |\n" \
"\t\t\t\t    _ _ _ _|  |       |   |_ _ _ _|   |_ _ _ _|\n" \
"\t\t\t\t   |          |       |           |   |       |\n" \
"\t\t\t\t   |          |       |           |   |       |\n" \
"\t\t\t\t   |_ _ _ _   |_ _ _ _|           |   |_ _ _ _|\n" \
" \n" \
"\t\t\t\t               ------------------\n" \
"\t\t\t\t                      MAIN \n" \
"\t\t\t\t               ------------------ \n" \
" \n" \
"\t\t\t\t   Ketik 'mulai' atau 'cara bermain': ");
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

void AcakAngka(){
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
        printf("\n\t\t\t\t\t-------LANGKAH SEBELUMNYA TIDAK ADA-------\n");
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
    system("cls");
    score=0;
    AcakAngka();
}

void Permainan(){
    system("cls") ;
    int i,j,k,m,n,same=0;
    char choice,s=-33,ynKeluar;
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
    AcakAngka();
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
            system("cls");
            updatearrtoprev(p);
            temp=8;
        }else if(choice=='u' || choice=='U'){
            count=0;
            UlangPermainan();
            papanmain();
            continue;
        }else if(choice=='k'||choice=='K'){
            DisplayKeluar();
            ynKeluar=getch();
            switch (ynKeluar){
                    case 'Y':
                    case 'y':exit(0);break;
                    case 'n':
                    case 'N':UlangPermainan(); papanmain();
            }
        }
        if(temp==1){
            temp=0;
            system("cls") ;
            printf("\n%c\n",choice);
            AcakAngka();
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
                printf("\n\t\t\t\t\t---------------PERINTAH TIDAK VALID---------------\n");
                same=0;
            }else{
                GetKalah();
                getch();
                exit(0);
            }
        }
        for(i=0;i<4;i++){
            for(k=0;k<4;k++){
                if(Papan[k][i]==2048){
                    GetKalah();
                    getch();
                    exit(0);
                }
            }
        }
    }
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
    printf("\t\t\t\t\tSkor:%d\n\t\t\t\t\t",score);

          if(score<highscore){
              printf("High Score:%d\t\t\t\t\t\n",highscore);
          }else{
              highscore=score;
              printf("High Score:%d\t\t\t\t\t\n",highscore);
          }

    printf("\t\t\t\t\tMundur-> M\t\t\t\t\t\n");
    printf("\t\t\t\t\tUlangi-> U\t\t\t\t\t\n");
    printf("\t\t\t\t\tKeluar-> K\t\t\t\t\t\n");
    printf("\t\t\t\t\t(Masukkan: w | a | s | d )-->\n\t\t\t\t\t");
}

void DisplayMenang(){
    system("cls");
    printf("\n" \
    "\t\t\t\t\t =========================\n" \
"\t\t\t\t\t|                         |\n" \
"\t\t\t\t\t|   WoooW kamu berhasil   |\n" \
"\t\t\t\t\t|     keren banget!!      |\n" \
"\t\t\t\t\t|           >.<           |\n" \
"\t\t\t\t\t|                         |\n" \
"\t\t\t\t\t =========================\n");
}

void DisplayKeluar(){
    system("cls");
    printf("\n" \
    "\t\t\t\t\t =========================\n" \
"\t\t\t\t\t|                         |\n" \
"\t\t\t\t\t|    Apakah kamu yakin?   |\n" \
"\t\t\t\t\t|                         |\n" \
"\t\t\t\t\t|       Ketik (y/n)       |\n" \
"\t\t\t\t\t|                         |\n" \
"\t\t\t\t\t =========================\n");
}

void DisplayKalah(){
    system("cls");
    printf("\n" \
    "\t\t\t\t\t =========================\n" \
"\t\t\t\t\t|                         |\n" \
"\t\t\t\t\t|    Yaahhh kamu kalah    |\n" \
"\t\t\t\t\t| coba lagi permainannya! |\n" \
"\t\t\t\t\t|        skor kamu        |\n" );
}

void GetKalah(){
    DisplayKalah();
    printf("\t\t\t\t\t|\t    %d\t  |",score);
    printf("\n\t\t\t\t\t|                         |");
    printf("\n\t\t\t\t\t =========================");
}