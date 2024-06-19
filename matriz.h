#ifndef MATRIZ
#define MATRIZ
#define posicao(I, J, COLUNAS) ((I)*(COLUNAS) + (J))
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct parametrosThread {
   unsigned int posInicio;
   unsigned int posFinal;
   unsigned int tamanho;
   int *vetorOrigem1;
   int *vetorOrigem2;
   int *vetorDestino;
   FILE* arquivo;
} parametrosThread;

int *alocarMatriz (int tamanho);

pthread_t *alocaIdsThreads(unsigned int tamanho);

parametrosThread *alocaVetorParametrosThreads(unsigned int tamanho);

void* leituraMatriz (void* args);

void passo1 (int *matrizA, int *matrizB, FILE *arquivoA, FILE *arquivoB, int tamanho, int nThreads);

void* gravacaoMatriz (void* args);

void passo3passo4 (int *matrizD, int *matrizC, FILE *arquivoD, FILE *arquivoC, int tamanho, int nThreads);

void *thrdSoma (void* args);

void soma (int *matrizA, int *matrizB, int *matrizC, int tamanho, int nThreads);

void *thrdMultiplicacao (void *args);

void multiplicacao (int* matrizC, int* matrizD, int* matrizE, int tamanho, int nThreads);

void *thrdSomaParcial(void *args);

int reducao (int *matrizE, FILE *arquivoE, int tamanho, int nThreads);

#endif