#include "auxFunc.h"

int *alocarMatriz (int tamanho) {
    int *matriz;
    if ((matriz = (int *)malloc(sizeof(int) * tamanho * tamanho)) == NULL) {
        fprintf(stderr,"Problemas na alocacao do vetor\n");
        exit(EXIT_FAILURE);
    }
    return matriz;
}

pthread_t *alocaIdsThreads(unsigned int tamanho) {
    pthread_t *vetor;   
    if (tamanho<=0)
        return NULL;  
    
    if ((vetor = (pthread_t *) malloc(sizeof(pthread_t)*tamanho)) == NULL) {
        fprintf(stderr,"Problemas na alocacao do vetor\n");
        exit(EXIT_FAILURE);
    }
    return vetor;
}

parametrosThread *alocaVetorParametrosThreads(unsigned int tamanho) {
    parametrosThread *vetor;    
    if (tamanho<=0)
        return NULL;
    
    if ((vetor = (parametrosThread *) malloc(sizeof(parametrosThread)*tamanho)) == NULL) {
        fprintf(stderr,"Problemas na alocacao do vetor\n");
        exit(EXIT_FAILURE);
    }
    return vetor;
}