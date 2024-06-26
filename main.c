#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "auxFunc.h"
#include "matriz.h"

int main(int argc, char* argv[])
{
    if (argc != 8) {
        printf("Numero de argumentos incorreto.\n"); 
        exit(EXIT_FAILURE);
    } 

    int nThreads = atoi(argv[1]);

    if (nThreads <= 0|| nThreads > 4 || nThreads == 3) {
        printf("Numero de threads incorreto.\n"); 
        exit(EXIT_FAILURE);
    }

    int tamanho = atoi(argv[2]);

    if (tamanho <= 0) {
        printf("Tamanho da matriz incorreto.\n"); 
        exit(EXIT_FAILURE);
    }

    // Abrindo os arquivos
    FILE* arquivoA = fopen(argv[3], "r");
    FILE* arquivoB = fopen(argv[4], "r");
    FILE* arquivoC = fopen(argv[5], "r");
    FILE* arquivoD = fopen(argv[6], "w");
    FILE* arquivoE = fopen(argv[7], "w");

    // Alocando dinamicamente as matrizes
    int *matrizA = alocarMatriz(tamanho);
    int *matrizB = alocarMatriz(tamanho);
    int *matrizC = alocarMatriz(tamanho);
    int *matrizD = alocarMatriz(tamanho);
    int *matrizE = alocarMatriz(tamanho);

    clock_t inicio_soma, fim_soma, inicio_multiplicacao, fim_multiplicacao, inicio_reducao, fim_reducao;

    passo1 (matrizA, matrizB, arquivoA, arquivoB, tamanho, nThreads);

    inicio_soma = clock();
    soma(matrizA, matrizB, matrizD, tamanho, nThreads);
    fim_soma = clock() - inicio_soma;

    passo3passo4 (matrizD, matrizC, arquivoD, arquivoC, tamanho, nThreads);

    inicio_multiplicacao = clock();
    multiplicacao(matrizD, matrizC, matrizE, tamanho, nThreads);
    fim_multiplicacao = clock() - inicio_multiplicacao;

    inicio_reducao = clock();
    long int reduc = reducao(matrizE, arquivoE, tamanho, nThreads);
    fim_reducao = clock() - inicio_reducao;

    double tempo_soma = ((double) fim_soma)/CLOCKS_PER_SEC;
    double tempo_multiplicacao = ((double) fim_multiplicacao)/CLOCKS_PER_SEC;
    double tempo_reducao = ((double) fim_reducao)/CLOCKS_PER_SEC;
    double tempo_total = tempo_soma + tempo_multiplicacao + tempo_reducao;

    printf("Reducao: %ld\n", reduc);
    printf("Tempo soma: %lf segundos.\n", tempo_soma);
    printf("Tempo multiplicacao: %lf segundos.\n", tempo_multiplicacao);
    printf("Tempo reducao: %lf segundos.\n", tempo_reducao);
    printf("Tempo total: %lf segundos.\n", tempo_total);

    return 0;
}
