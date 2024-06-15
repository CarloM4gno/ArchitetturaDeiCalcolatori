#include <stdio.h>
#include <stdlib.h>

/* a fine passaggio però è un puntatore di puntatore.. perchè?*/
/*passare l'indirizzo di un puntatore signfica creare un puntatore di puntatore, allo stesso modo passare l' indirizzo di una semplice varaibile significa passare un puntatore*/
void readMatrix(FILE *file, int **matrix, int *rows, int *cols) {
/*sintassi di fread, quello che voglio salvare( ma come puntatore) , dimensione dell elmento(tipo), quantità ,puntatore a file*/
/* int= 4 byte, double= 8 byte*/
/* * e & sono fratelli */
/*così gli diciamo di leggere un intero( il primo)*/
    fread(rows, sizeof(int), 1, file);
/*così gli diciamo di leggere un intero( il secondo)*/
    fread(cols, sizeof(int), 1, file);

/* un puntatore contiene l'indirizzo di memoria della prima cella del tipo a cui punta*/
/*
malloc(sizeof(int)) alloca quel numero di byte dall'heap e restituisce un puntatore al primo byte della memoria allocata.
(int *) è un cast per convertire il tipo di ritorno di malloc (void*) in un puntatore a int.
*/
    *matrix = (int *)malloc((*rows) * (*cols) * sizeof(int));
    fread(*matrix, sizeof(int), (*rows) * (*cols), file);
}


void printMatrix(int *matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}




int main() {
    FILE *file = fopen("matrices.bin", "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    int *matrix1 = NULL, *matrix2 = NULL;
    int rows1, cols1, rows2, cols2;

    /* gli passa il puntatore a file, l'indirizzo del puntatore a intero*/
    readMatrix(file, &matrix1, &rows1, &cols1);
    // Read the second matrix
    readMatrix(file, &matrix2, &rows2, &cols2);

    printf("Matrix 1:\n");
    printMatrix(matrix1, rows1, cols1);
    printf("Matrix 2:\n");
    printMatrix(matrix2, rows2, cols2);

    free(matrix1);
    free(matrix2);
    fclose(file);

    return 0;
}
