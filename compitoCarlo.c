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
struttura *ptrS;

/* allocazione di ptrS */
ptrS=&matrice;

/* l'operatore p ci permette di stampare l'indirizzo di un qualcosa, essendo matrice.rows un valore, serve prima citare l'indirizzo con apposito simbolo&*/
/* notiamo subito che l'indirizzo di row coincide con l'indirizzo di ptrS*/
printf("\n indirizzo di row %p",&matrice.rows);
printf("\n indirizzo di cols %p",&matrice.cols);
printf("\n indirizzo di ptrS %p",ptrS);

/*essendo un valore e non un indirizzo questa scrittura è errata*/
/* printf("\n indirizzo di ptrS->row %p",ptrS->rows);    */

/*poiche fread come primo argomento si aspetta un puntatore, uso ptrS->row, e poichè bisogna passare l'indirizzo e non il valore uso &*/
fread(&ptrS->rows,sizeof(int),1,file);
/*poichè voglio il valore contenuto in ptrS->row... */
printf("\n%d",ptrS->rows);
fread(&ptrS->cols,sizeof(int),1,file);
printf("\n%d",ptrS->cols);

/*leggere l'intera matrice*/
int dimMat1= matrice.rows*matrice.cols;
/*poichè mat1 deve ospitare più di un intero bisogna allocarlo*/
/* la sintassi di malloc è:  malloc ritorna un puntatore, bisogna quindi specificare il tipo castandolo con (cast*) poi bisogna specificare la dimensione in byte e se vogliamo che sia dinamico 
ciò deve avere una variabile, quindi specifichiamo il tipo con l'operatore sizeof*/

/* prima parte con serializzazione */
int*mat1=(int*)malloc(dimMat1*sizeof(int));
printf("\n indirizzo di mat1 %p",mat1);
fread(mat1,sizeof(int),dimMat1,file);
for(int i=0;i<dimMat1;i++){
printf("\n%d",mat1[i]);
}
printf("\n indirizzo di mat1[0] %p",mat1);


/*seconda parte*/
fread(&ptrS->rows,sizeof(int),1,file);
printf("\n%d",ptrS->rows);
fread(&ptrS->cols,sizeof(int),1,file);
printf("\n%d\n",ptrS->cols);



int **matrice2;
dimMat1= matrice.rows*matrice.cols;

/*
size_t size= dimMat1*sizeof(int*);
printf("\n indirizzo di matrice2 e': %p\n",matrice2);
printf("la dimensione di matrice2 e': %zu byte \n",size);
*/


/* allocazione totale */
matrice2=(int**)calloc(ptrS->rows,sizeof(int*));
for (int i = 0; i < ptrS->rows; i++) {
 /* Allocazione della memoria per la colonna  */
    matrice2[i] = (int*)calloc(ptrS->cols,sizeof(int));
    if(matrice2[i]==NULL){
        printf("\n Errore nell'allocazione");
    }
    // Lettura dei valori della riga i
    for (int j = 0; j < ptrS->cols; j++) {
        fread(&matrice2[i][j], sizeof(int), 1, file);
        printf("%d ", matrice2[i][j]);
    }
    printf("\n");
}

}

  



