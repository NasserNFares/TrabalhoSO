#ifndef AUX_H
#define AUX_H
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
   FILE *arquivo;
} parametrosThread;

/**
 * Função para alocar memória para uma matriz
 * @param tamanho tamanho da dimensão da matriz
 */
int *alocarMatriz (int tamanho);

/**
 * Função para alocar o vetor de id de threads
 * @param tamanho tamanho do vetor
 */
pthread_t *alocaIdsThreads(unsigned int tamanho);

/**
 * Vetor para alocar a estrutura parametrosThread
 * @param tamanho tamanho do vetor de estruturas
 */
parametrosThread *alocaVetorParametrosThreads(unsigned int tamanho);

#endif