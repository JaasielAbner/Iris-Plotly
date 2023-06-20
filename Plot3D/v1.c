#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "matrixFunctions.c"


int main()
{
    float **Mat;
    float **MatDe;

    Mat = init_database("IrisDataset.csv");

    MatDe = euclidian_distance(Mat);

    free(Mat);

    normalize_matrix(MatDe, 0.0065);

    //funcoes de saida
    int colors[MATRIX_SIZE] = {0};
    BFS(MatDe, colors);
    
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        printf("%d\n", colors[i]);
    }
    

    // print_matrix(MatDe);
    make_txt(MatDe);
    // teste(MatDe);

    return 0;
}
