#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
int rows;
int cols;

}struttura;

int main(){
FILE*file;
file=fopen("matrices.bin","rb");
if(file==NULL){
    printf("errore nella apertura del file\n");
}
struttura matrice;
struttura matrice_2;
struttura *ptrS;
struttura *ptrS2;

/* allocazione di ptrS */
ptrS=&matrice;
ptrS2=&matrice_2;

printf("\n indirizzo di row %p",&matrice.rows);
printf("\n indirizzo di cols %p",&matrice.cols);
printf("\n indirizzo di ptrS %p",ptrS);
printf("\n indirizzo di ptrS2 %p",ptrS2);

/*essendo un valore e non un indirizzo questa scrittura è errata*/
printf("\n indirizzo di ptrS->row %p",ptrS->rows);

/*poiche fread come primo argomento si aspetta un puntatore uso ptrS->row, e poichè bisogna passare l'indirizzo e non il valore uso &*/
fread(&ptrS->rows,sizeof(int),1,file);
/*poichè voglio il valore contenuto in ptrS->row... */
printf("\n%d",ptrS->rows);
fread(&ptrS->cols,sizeof(int),1,file);
printf("\n%d",ptrS->cols);

/*leggere l'intera matrice*/
int dimMat1= matrice.rows*matrice.cols;
/*poichè mat1 deve ospitare più di un intero bisogna allocarlo*/
int*mat1=(int*)malloc(dimMat1*sizeof(int));
printf("\n indirizzo di mat1 %p",mat1);
fread(mat1,sizeof(int),dimMat1,file);
for(int i=0;i<dimMat1;i++){
printf("\n%d",mat1[i]);
}
printf("\n indirizzo di mat1[0] %p",mat1);


/*seconda parte*/
fread(&ptrS2->rows,sizeof(int),1,file);
fread(&ptrS2->cols,sizeof(int),1,file);
printf("\n%d",ptrS2->rows);
printf("\n%d",ptrS2->cols);


int **matrice2;
matrice2=(int**)malloc(ptrS2->rows*sizeof(int*));


size_t size= ptrS2->cols*sizeof(int)*ptrS2->rows*sizeof(int*);
printf("\n indirizzo di matrice2 e': %p\n",matrice2);
printf("\n la dimensione di matrice2 e': %zu byte \n",size);

for (int i = 0; i < ptrS2->rows; i++) {
    // Allocazione della memoria per la riga i
    matrice2[i] = (int*)malloc(ptrS2->cols * sizeof(int));
    
    // Lettura del puntatore alla riga i
    fread(matrice2[i], sizeof(int*), 1, file);
    
    // Lettura dei valori della riga i
    for (int j = 0; j < ptrS2->cols; j++) {
        fread(&matrice2[i][j], sizeof(int), 1, file);
        printf("%d ", matrice2[i][j]);
    }
    printf("\n");
}




}