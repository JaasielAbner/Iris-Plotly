#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define LIN 150
#define COL 4
#define MATRIX_SIZE 150

void normalize_matrix(float **matrix)
{
    float media = 1;
    float min = matrix[1][3];
    float max = 0;

    // Encontra o valor mínimo e o valor máximo da matriz
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = i + 1; j < MATRIX_SIZE; j++)
        {
            if (matrix[i][j] < min && matrix[i][j])
            {
                min = matrix[i][j];
            }
            if (matrix[i][j] > max)
            {
                max = matrix[i][j];
            }
            media += matrix[i][j];
        }
    }

    media = media / (MATRIX_SIZE * (MATRIX_SIZE + 1) / 2);
    // printf("%f %f %f\n", media, min, max);

    // Normaliza cada elemento da matriz
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = i + 1; j < MATRIX_SIZE; j++)
        {
            // int v = (matrix[i][j]) / (max);
            matrix[i][j] = (matrix[i][j] - min) / (max - min) <= 0.3;
        }
    }
}

void print_matrix(float **matrix)
{
    // printf("%d\n", q);
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = i + 1; j < MATRIX_SIZE; j++)
        {
            if (matrix[i][j])
            {
                printf("%d %d\n", i, j);
            }
        }
    }
}

void make_txt(float **matrix)
{

    FILE *o = fopen("out.txt", "w");

    // fprintf(o, "%d\n", MATRIX_SIZE);
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        fprintf(o, "%d", i + 1);
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            if (matrix[i][j])
            {
                fprintf(o, " %d", j + 1);
            }
        }
        fprintf(o, "\n");
    }
}

void teste(float **matrix)
{

    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = i + 1; j < MATRIX_SIZE; j++)
        {
            printf("%.0f ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{

    // ---------- Criando matriz a partir do arquivo CSV ---------- //

    // float Mat[LIN][COL];
    float **Mat;
    float **MatDe;
    int l, i, j;

    Mat = (float **)malloc(LIN * sizeof(float *));
    for (l = 0; l < LIN; l++)
    {
        Mat[l] = (float *)malloc(COL * sizeof(float));
    }

    FILE *fp;

    fp = fopen("IrisDataset.csv", "r");

    if (fp == NULL)
    {
        printf("Arquivo nao encontrado");
        exit(0);
    }

    float d1, d2, d3, d4;
    char line[100];
    char *sp;
    int x = 0;

    fgets(line, 100, fp);
    while (fgets(line, 100, fp) != NULL)
    {
        sp = strtok(line, ",");
        d1 = atof(sp);

        sp = strtok(NULL, ",");
        d2 = atof(sp);

        sp = strtok(NULL, ",");
        d3 = atof(sp);

        sp = strtok(NULL, ",");
        d4 = atof(sp);

        Mat[x][0] = d1;
        Mat[x][1] = d2;
        Mat[x][2] = d3;
        Mat[x][3] = d4;

        x++;
        // printf("\n %0.1f , %0.1f , %0.1f , %0.1f ",d1,d2,d3,d4);
        // printf("\n");
    }

    fclose(fp);

    // ---------- Criando matriz de Distâncias Euclidianas ---------- //

    MatDe = (float **)malloc(MATRIX_SIZE * sizeof(float *));
    for (l = 0; l < MATRIX_SIZE; l++)
    {
        MatDe[l] = (float *)malloc(MATRIX_SIZE * sizeof(float));
    }

    float v1, v2, v3, v4, v;

    for (i = 0; i < MATRIX_SIZE; i++)
    {
        for (j = 0; j < MATRIX_SIZE; j++)
        {
            // Calculo euclidiano
            v1 = Mat[i][1] - Mat[j][1];
            v2 = Mat[i][2] - Mat[j][2];
            v3 = Mat[i][3] - Mat[j][3];
            v4 = Mat[i][4] - Mat[j][4];
            v = pow(v1, 2) + pow(v2, 2) + pow(v3, 2) + pow(v4, 2);
            MatDe[i][j] = (sqrt(v));
        }
    }
    free(Mat);

    normalize_matrix(MatDe);

    //funcoes de saida
    print_matrix(MatDe);
    make_txt(MatDe);
    // teste(MatDe);

    return 0;
}
