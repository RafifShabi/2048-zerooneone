#include <stdio.h>
#include <stdlib.h>

/*int main (int argc, char *argv[]){
    int x = 10;
    int *px1;
    int **px2;
    int ***px3;
    px1=&x;
    px2=&px1;
    px3=&px2;
    printf("Hasil menggunakan 1 pointer\n");
    printf("Nilai x = %i\n",*px1);
    printf("Alamat x = %p\n",px1);
    printf("Alamat px1 = %p\n\n",&px1);

    printf("Hasil menggunakan pointer ke pointer\n");
    printf("Nilai x = %i\n",**px2);
    printf("Alamat x = %p\n",*px2);
    printf("Alamat px1 = %p\n\n",px2);

    printf("Hasil menggunakan pointer ke pointer\n");
    printf("Nilai x = %i\n",***px3);
    printf("Alamat x = %p\n",**px3);
    printf("Alamat px1 = %p\n\n",px3);

    return 0;
}*/

#define MAXPREV 500
int main(){
   int i,j,k,m,n,same=0; //var buat affh
    char choice,s=-33,reschk; //affh
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
    printf("i = %i\n",i);
    printf("j = %i\n",j);
    printf("k = %i\n",k);
    printf("m = %i\n",m);
    printf("n = %i\n",n);

    for(int i=0;i<MAXPREV+1;i++){
        for(int j=0;j<4;j++){
            p[i][j]=(int *)malloc(sizeof(int)*4);
            printf("")
        }
    }    
}    