#ifndef MATRIZ
#define MATRIZ
#define posicao(I, J, COLUNAS) ((I)*(COLUNAS) + (J))
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "auxFunc.h"

/**
 * Função para ler a matriz guardada no arquivo e mover para o programa
 * @param args estrutura parametrosThread em casting para void*
 */
void* leituraMatriz (void* args);

/**
 * Função de leitura das matrizes A e B
 * @param matrizA vetor da matriz A
 * @param matrizB vetor da matriz B
 * @param arquivoA arquivo da matriz A
 * @param arquivoB arquivo da matriz B
 * @param tamanho tamanho da dimensão da matriz
 * @param nThreads número de threads de processamento
 */
void passo1 (int *matrizA, int *matrizB, FILE *arquivoA, FILE *arquivoB, int tamanho, int nThreads);

/**
 * Função para gravar a matriz do programa para um arquivo
 * @param args estrutura parametrosThread em casting para void*
 */
void* gravacaoMatriz (void* args);

/**
 * Função de leitura da matriz C e gravação da matriz D
 * @param matrizC vetor da matriz C
 * @param matrizD vetor da matriz D
 * @param arquivoC arquivo da matriz C
 * @param arquivoD arquivo da matriz D
 * @param tamanho tamanho da dimensão da matriz
 * @param nThreads número de threads de processamento
 */
void passo3passo4 (int *matrizD, int *matrizC, FILE *arquivoD, FILE *arquivoC, int tamanho, int nThreads);

/**
 * Função para realizar a soma de matrizes
 * @param args estrutura parametrosThread em casting para void*
 */
void *thrdSoma (void* args);

/**
 * Função para preparar os parametros da soma das matrizes A e B
 * @param matrizC vetor da matriz C
 * @param matrizD vetor da matriz D
 * @param arquivoC arquivo da matriz C
 * @param arquivoD arquivo da matriz D
 * @param tamanho tamanho da dimensão da matriz
 * @param nThreads número de threads de processamento
 */
void soma (int *matrizA, int *matrizB, int *matrizC, int tamanho, int nThreads);

/**
 * Função para realizar multiplicação de matrizes
 * @param args estrutura parametrosThread em casting para void*
 */
void *thrdMultiplicacao (void *args);

/**
 * Função para preparar os parametros da multiplicação das matrizes C e D
 * @param matrizC vetor da matriz C
 * @param matrizD vetor da matriz D
 * @param arquivoC arquivo da matriz C
 * @param arquivoD arquivo da matriz D
 * @param tamanho tamanho da dimensão da matriz
 * @param nThreads número de threads de processamento
 */
void multiplicacao (int* matrizC, int* matrizD, int* matrizE, int tamanho, int nThreads);

/**
 * Função para fazer a redução total ou parcial de uma matriz
 * @param args estrutura parametrosThread em casting para void*
 */
void *thrdReducao (void *args);

/**
 * Função para preparar os parametros da gravação e redução da matriz E
 * @param matrizE vetor da matriz E
 * @param arquivoE arquivo da matriz E
 * @param tamanho tamanho da dimensão da matriz
 * @param nThreads número de threads de processamento
 */
long int reducao (int *matrizE, FILE *arquivoE, int tamanho, int nThreads);

#endif