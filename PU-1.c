#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define MAXRANDOMVALUE 3
#define MAXPREV 500

/*============ Variable Global ============*/
int arr[4][4]={0},c[4],temp=0,len=0,score=0,highscore=0,count=0,ch=0;//COUNT WILL COUNT THE NO OF STEPS

int i,j,k,papan;

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

void papan();

void movevalue(int k)
{
    int i;
    if(k==3 )
    {
        return;
    }
    for(i=k;i<4;i++)
    {
        if(c[i]!=0)
        {
            movevalue(i+1);
            for(;i<4;i++)
            {
                if(c[i+1]!=0)
                {
                    break;
                }
                    c[i+1]=c[i];
                    c[i]=0;
            }


        }
    }
}
int kosong(int n)
{

        if(n==0)
        {

            return len;
        }
        else
        {
            len++;
            kosong(n/10);
        }
}
void angkaacak()
{
    int no;
     srand(time(NULL));
    int i,j; //RANDOM INDEX
    do
    {
    i=(rand ())%(MAXRANDOMVALUE+1);
    j=(rand ())%(MAXRANDOMVALUE+1);
    }
    while(arr[i][j]!=0);
   //printf("%d %d",i,j);
    no=2*((rand ()%10)+1);
    if(no==3 || no==2)
    {
        arr[i][j]=2;
    }
    else
    {
        arr[i][j]=2;
    }
}
void rupdate()
{
    int i,j;
    for(i=3;i>0;i--)
    {
        if(c[i]==c[i-1] )
        {
            c[i]+=c[i-1];
            score=score+c[i];
            if(score>highscore)
            {

            }
            temp=1;
            c[i-1]=0;
        }
        else if(c[i-1]==0 && c[i]!=0 )
        {
            c[i-1]=c[i];
            c[i]=0;
            temp=1;
        }
        else if(c[i]==0)
        {
            temp=1;
        }
    }
        movevalue(0);

}
void createprev(int ***p)
{
      int i,j,k;
      FILE *ptr;
      ptr=fopen("hstr.txt","a");
      fprintf(ptr,"%d ",score);
      fclose(ptr);

    if(count==MAXPREV+1)
    {
        for(i=MAXPREV;i>0;i--)
        {
            for(j=0;j<4;j++)
            {
                for(k=0;k<4;k++)
                {
                        p[i][j][k]=p[i-1][j][k];
                }
            }

        }
        count=MAXPREV;
    }

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            p[MAXPREV-count][i][j]=arr[i][j];
        }

    }
}
void updatearrtoprev(int ***p)
{
    int data,i,j;
    if(count==0)
    {
        printf("\n\t\t\t\t\t******FURTHER MORE PREV NOT POSSIBLE********");
        return;
    }
    FILE *ptr=fopen("hstr.txt","r+");
        for(i=0;i<count;i++)
        {
            fscanf(ptr,"%d ",&data);
        }
        score=data;

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            arr[i][j]=p[MAXPREV-count][i][j];
        }
    }
    count--;



}
void resetgame()
{
            int i,j;
            for(i=0;i<4;i++)
            {
                for(j=0;j<4;j++)
                {
                    arr[i][j]=0;

                }
            }
            system("cls") ;
            score=0;
            angkaacak();

}

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

void Permainan(){
    system("cls") ;
    int i,j,k,m,n,same=0;
    char choise,s=-33,reschk;
    int ***p;
    p=(int ***)malloc(sizeof(int *)*(MAXPREV+1));
    for(int i=0;i<MAXPREV+1;i++)
    {
        *(p+i)=(int **)malloc(sizeof(int *)*4);
    }
    for(int i=0;i<MAXPREV+1;i++)
    {
        for(int j=0;j<4;j++)
        {
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
    papan();
    while(1)
    {
            if(score>highscore)
            {

            ptr=fopen("highscore.txt","w");
            fprintf(ptr,"%d",score);
            fclose(ptr);
            }
        choise=getch();
        if(choise=='D' || choise =='d')
        {
            count++;ch++;
              createprev(p);
            for(i=0;i<4;i++)
            {
                for(j=0;j<4;j++)
                {
                    c[j]=arr[i][j];
                }
                    rupdate();
                for(k=0;k<4;k++)
                {
                    arr[i][k]=c[k];
                }
            }
        }
        else if(choise=='a' || choise=='A')
        {
            count++;
            ch++;
            createprev(p);
            for(i=0;i<4;i++)
            {
                for(j=3;j>=0;j--)
                {
                    c[3-j]=arr[i][j];
                }
                rupdate();
                for(k=0;k<4;k++)
                {
                    arr[i][3-k]=c[k];
                }
            }
        }
        else if(choise=='s' || choise =='S')
        {
            count++;ch++;

               createprev(p);
            for(i=0;i<4;i++)
            {
                for(j=0;j<4;j++)
                {
                    c[j]=arr[j][i];
                }
                rupdate();
                for(k=0;k<4;k++)
                {
                    arr[k][i]=c[k];
                }
            }
        }
        else if(choise=='w' || choise=='W')
        {
            count++;ch++;

              createprev(p);
            for(i=0;i<4;i++)
            {
                for(j=3;j>=0;j--)
                {
                    c[3-j]=arr[j][i];
                }
                rupdate();
                for(k=0;k<4;k++)
                {
                  arr[3-k][i]=c[k];
                }
            }
        }
        else if(choise=='p' || choise =='p')
        {

            updatearrtoprev(p);

            temp=8;
        }
        else if(choise=='R' || choise=='r')
        {
            count=0;
            resetgame();
            papan();
            continue;
        }
        else if(choise=='u'||choise=='U')
        {
            exit(0);
        }

            if(temp==1)
            {
                temp=0;
                system("cls") ;
                printf("\n%c\n",choise);
                angkaacak();
                papan();

            }
            else if(temp==8)
            {
                temp=0;
                papan();
            }
            else
            {
                for(m=0;m<4;m++)
                {
                    for(n=3;n>0;n--)
                    {
                        if(arr[m][n]==arr[m][n-1] || arr[m][n]==0 || arr[m][n-1]==0)
                        {
                                same=1;
                                break;
                        }
                        if(arr[n][m]==arr[n-1][m] || arr[m][n]==0 || arr[m][n-1]==0)
                        {
                            same=1;
                            break;
                        }
                    }
                    if(same==1)
                        break;
                }
               if(same==1)
                {
                    printf("\n\t\t\t\t\t============INVALID KEY==========\n");
                    same=0;


                }
                else
                {
                    printf("\n\t\t\t\t\t=============GAME OVER============");
                    printf("\n\n\t\t\t\t\tWANT TO PLAY MORE?? Y/N??\n\t\t\t\t\t");
                    reschk=getch();
                    switch (reschk)
                    {
                        case 'Y':
                        case 'y':resetgame(); papan();break;
                        case 'n':
                        case 'N':exit(0);
                    }
                    continue;

                }
            }
    }
    // return 0;
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

void papan()
{
        int i,j,k,papan;

        printf("\n\t\t\t\t\t===============2048==============\n");
          printf("\t\t\t\t\tYOUR SCORE=%d\n\t\t\t\t\t",score);
          if(score<highscore)
          {
              printf("HIGH SCORE=%d\t\t\t\t\t\n",highscore);
          }
          else
          {
              highscore=score;
              printf("HIGH SCORE=%d\t\t\t\t\t\n",highscore);
          }
    printf("\t\t\t\t\t---------------------------------\n");
    for (i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(j==0)
            {
                printf("\t\t\t\t\t|");
            }
            if(arr[i][j]!=0)
            {
                papan=kosong(arr[i][j]);
                //printf("%d:",len);

                for(k=0;k<4-len;k++)
                {
                    printf(" ");
                }
                printf("%d",arr[i][j]);

                for(k=0;k<4-len;k++)
                {
                    printf(" ");
                }
                for(k=0;k<len-1;k++)
                {
                    printf(" ");
                }
                printf("|");
            }
            else
            {
                for(k=0;k<8-2*len-1;k++){
                printf(" ");}printf("|");
            }
            len=0;
        }
        if(i!=3)
        {
        printf("\n");
    printf("\t\t\t\t\t---------------------------------\n");
        }

    }
    printf("\n\t\t\t\t\t---------------------------------\n");
     printf("\t\t\t\t\tPREV-> P\t\t\t\t\t\n");
     printf("\t\t\t\t\tRESTART-> R\t\t\t\t\t\n");
     printf("\t\t\t\t\tEXIT-> U\t\t\t\t\t\n");
    printf("\t\t\t\t\tENTER YOUR CHOISE -> W,S,A,D\n\t\t\t\t\t");

}