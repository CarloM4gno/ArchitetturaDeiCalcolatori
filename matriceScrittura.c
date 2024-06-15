#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("matrices.bin", "wb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // Define the first matrix
    int rows1 = 2, cols1 = 3;
    int matrix1[] = {
        1, 2, 3,
        4, 5, 6
    };

    // Define the second matrix
    int rows2 = 3, cols2 = 2;
    int matrix2[] = {
        7, 8,
        9, 10,
        11, 12
    };

    // Write the first matrix to the file
    fwrite(&rows1, sizeof(int), 1, file);
    fwrite(&cols1, sizeof(int), 1, file);
    fwrite(matrix1, sizeof(int), rows1 * cols1, file);

    // Write the second matrix to the file
    fwrite(&rows2, sizeof(int), 1, file);
    fwrite(&cols2, sizeof(int), 1, file);
    fwrite(matrix2, sizeof(int), rows2 * cols2, file);

    fclose(file);

    return 0;
}