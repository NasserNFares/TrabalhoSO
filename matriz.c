#include "matriz.h"

// Função para alocar memória para uma matriz
int *alocarMatriz (int tamanho)
{
    int *matriz = (int *)malloc(tamanho * tamanho * sizeof(int));
    return matriz;
}

pthread_t *alocaIdsThreads(unsigned int tamanho)
{
    pthread_t *vetor;   
    if (tamanho<=0)
        return NULL;  
    
    if ((vetor = (pthread_t *) malloc(sizeof(pthread_t)*tamanho)) == NULL)
    {
      fprintf(stderr,"Problemas na alocacao do vetor\n");
      exit(EXIT_FAILURE);
    }
    return vetor;
}

parametrosThread *alocaVetorParametrosThreads(unsigned int tamanho)
{
    parametrosThread *vetor;    
    if (tamanho<=0)
        return NULL;  
    
    if ((vetor = (parametrosThread *) malloc(sizeof(parametrosThread)*tamanho)) == NULL)
    {
        fprintf(stderr,"Problemas na alocacao do vetor\n");
        exit(EXIT_FAILURE);
    }
    return vetor;
}

// Função para ler a matriz guardada no arquivo
void* leituraMatriz (void* args) {

    register int i, j, tamanho;
    int *vetor;
    FILE* arquivo;

    tamanho = ( (parametrosThread *) args)->tamanho;
    vetor  = ( (parametrosThread *) args)->vetorOrigem1;
    arquivo = ( (parametrosThread *) args)->arquivo;

    int item;
    for (i = 0; i < tamanho; i++) {
        for(j = 0; j < tamanho; j++) {
            fscanf(arquivo, "%d", &item);
            if (item != EOF) {
                vetor[posicao(i, j, tamanho)] = item;
            }
        }
    }
    return NULL;
}

void passo1 (int *matrizA, int *matrizB, FILE *arquivoA, FILE *arquivoB, int tamanho, int nThreads) {
    
    parametrosThread *parametros;
    pthread_t *idsThread;
    register int i = 0;
    int err;
    idsThread = alocaIdsThreads(2);
    parametros = alocaVetorParametrosThreads(2);

    parametros[0].tamanho = tamanho;
    parametros[0].vetorOrigem1 = matrizA;
    parametros[0].arquivo = arquivoA;

    parametros[1].tamanho = tamanho;
    parametros[1].vetorOrigem1 = matrizB;
    parametros[1].arquivo = arquivoB;

    if (nThreads==1) {

        leituraMatriz ((void *) &parametros[0]);
        leituraMatriz ((void *) &parametros[1]);
        return;
    }
    
    // Thread de leitura da matriz A
    err = pthread_create(&idsThread[0], NULL, leituraMatriz, (void *) &parametros[0]);
    if (err != 0)
    {
        fprintf(stderr,"Erro na criacao do thread %d\n", i);
        exit(EXIT_FAILURE);
    }

    // Thread de leitura da matriz B
    err = pthread_create(&idsThread[1], NULL, leituraMatriz, (void *) &parametros[1]);
    if (err != 0)
    {
        fprintf(stderr,"Erro na criacao do thread %d\n", i);
        exit(EXIT_FAILURE);
    }

    for (i=0; i<2; i++)
    {
        err = pthread_join(idsThread[i], NULL);

        if (err != 0)
        {
            fprintf(stderr,"Erro na juncao do thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    free(idsThread);
    free(parametros);
}

// Função para imprimir uma matriz em um arquivo
void* gravacaoMatriz (void* args) {

    register int i, j, tamanho;
    int *vetor;
    FILE* arquivo;

    tamanho = ( (parametrosThread *) args)->tamanho;
    vetor  = ( (parametrosThread *) args)->vetorOrigem1;
    arquivo = ( (parametrosThread *) args)->arquivo;

    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++) {
            fprintf(arquivo, "%d ", vetor[posicao(i, j, tamanho)]);
        }
        fprintf(arquivo, "\n");
    }
    return NULL;
}

void passo3passo4 (int *matrizD, int *matrizC, FILE *arquivoD, FILE *arquivoC, int tamanho, int nThreads) {
    
    parametrosThread *parametros;
    pthread_t *idsThread;
    register int i = 0;
    int err;
    idsThread = alocaIdsThreads(2);
    parametros = alocaVetorParametrosThreads(2);

    parametros[0].tamanho = tamanho;
    parametros[0].vetorOrigem1 = matrizD;
    parametros[0].arquivo = arquivoD;

    parametros[1].tamanho = tamanho;
    parametros[1].vetorOrigem1 = matrizC;
    parametros[1].arquivo = arquivoC;

    if (nThreads==1) {

        gravacaoMatriz ((void *) &parametros[0]);
        leituraMatriz ((void *) &parametros[1]);
        return;
    }
    
    // Thread de leitura da matriz A
    err = pthread_create(&idsThread[0], NULL, gravacaoMatriz, (void *) &parametros[0]);
    if (err != 0)
    {
        fprintf(stderr,"Erro na criacao do thread %d\n", i);
        exit(EXIT_FAILURE);
    }

    // Thread de leitura da matriz B
    err = pthread_create(&idsThread[1], NULL, leituraMatriz, (void *) &parametros[1]);
    if (err != 0)
    {
        fprintf(stderr,"Erro na criacao do thread %d\n", i);
        exit(EXIT_FAILURE);
    }

    for (i=0; i<2; i++)
    {
        err = pthread_join(idsThread[i], NULL);

        if (err != 0)
        {
            fprintf(stderr,"Erro na juncao do thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    free(idsThread);
    free(parametros);
}

void *thrdSoma (void* args) {
    register int i, j, inicio, final, tamanho;
    int *vetorOrigem1, *vetorOrigem2, *vetorDestino;
    inicio = ( (parametrosThread *) args)->posInicio;
    final  = ( (parametrosThread *) args)->posFinal;
    vetorOrigem1  = ( (parametrosThread *) args)->vetorOrigem1;
    vetorOrigem2 = ( (parametrosThread *) args)->vetorOrigem2;
    vetorDestino = ( (parametrosThread *) args)->vetorDestino;
    tamanho = ( (parametrosThread *) args)->tamanho;
    for (i = inicio; i <= final; i++)
        for (j = 0; j <= tamanho; j++)
            vetorDestino[posicao(i, j, tamanho)] = vetorOrigem1[posicao(i, j, tamanho)] + vetorOrigem2[posicao(i, j, tamanho)];

    return NULL;
}

void soma (int *matrizA, int *matrizB, int *matrizC, int tamanho, int nThreads) {

    parametrosThread *parametros;
    register int quantElementos = tamanho / nThreads;
    pthread_t *idsThread;
    register int i = 0;
    int err;
    idsThread = alocaIdsThreads(nThreads);
    parametros = alocaVetorParametrosThreads(nThreads);
    
    if (nThreads==1) {
        parametros[0].posInicio = 0;
        parametros[0].posFinal  = tamanho;
        parametros[0].vetorOrigem1 = matrizA;
        parametros[0].vetorOrigem2 = matrizB;
        parametros[0].vetorDestino = matrizC;
        parametros[0].tamanho = tamanho;
        thrdMultiplicacao((void *) &parametros[0]);
        return;
    }

    for (i=0; i<nThreads; i++) {
        parametros[i].posInicio = quantElementos * i;
        parametros[i].posFinal  = (quantElementos * (i+1)) - 1;
        parametros[i].vetorOrigem1 = matrizA;
        parametros[i].vetorOrigem2 = matrizB;
        parametros[i].vetorDestino = matrizC;
        parametros[i].tamanho = tamanho;

        err = pthread_create(&idsThread[i], NULL, thrdSoma, (void *) &parametros[i]);

        if (err != 0)
        {
            fprintf(stderr,"Erro na criacao do thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (i=0; i<nThreads; i++)
    {
        err = pthread_join(idsThread[i], NULL);

        if (err != 0)
        {
            fprintf(stderr,"Erro na juncao do thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    free(idsThread);
    free(parametros);
}

void *thrdMultiplicacao (void *args) {
    register int i, j, k, inicio, final, tamanho;
    int *vetorOrigem1, *vetorOrigem2, *vetorDestino;
    inicio = ( (parametrosThread *) args)->posInicio;
    final  = ( (parametrosThread *) args)->posFinal;
    vetorOrigem1  = ( (parametrosThread *) args)->vetorOrigem1;
    vetorOrigem2 = ( (parametrosThread *) args)->vetorOrigem2;
    vetorDestino = ( (parametrosThread *) args)->vetorDestino;
    tamanho = ( (parametrosThread *) args)->tamanho;

    for (i = inicio; i <= final; i++) {
        for (j = 0; j < tamanho; j++) {
            vetorDestino[posicao(i, j, tamanho)] = 0;
            for (k = 0; k < tamanho; k++)
            {
                vetorDestino[posicao(i, j, tamanho)] += vetorOrigem1[posicao(i, k, tamanho)] * vetorOrigem2[posicao(k, j, tamanho)];
            }
        }
    }
    return NULL;
}

void multiplicacao (int *matrizD, int *matrizC, int *matrizE, int tamanho, int nThreads) {

    parametrosThread *parametros;
    register int quantElementos = tamanho / nThreads;
    pthread_t *idsThread;
    register int i = 0;
    int err;
    idsThread = alocaIdsThreads(nThreads);
    parametros = alocaVetorParametrosThreads(nThreads);

    if (nThreads==1) {
        parametros[0].posInicio = 0;
        parametros[0].posFinal  = tamanho;
        parametros[0].vetorOrigem1 = matrizC;
        parametros[0].vetorOrigem2 = matrizD;
        parametros[0].vetorDestino = matrizE;
        parametros[0].tamanho = tamanho;
        thrdMultiplicacao((void *) &parametros[0]);
        return;
    }

    for (i=0; i<nThreads; i++) {
        parametros[i].posInicio = quantElementos * i;
        parametros[i].posFinal  = (quantElementos * (i+1)) - 1;
        parametros[i].vetorOrigem1 = matrizC;
        parametros[i].vetorOrigem2 = matrizD;
        parametros[i].vetorDestino = matrizE;
        parametros[i].tamanho = tamanho;

        err = pthread_create(&idsThread[i], NULL, thrdMultiplicacao, (void *) &parametros[i]);

        if (err != 0)
        {
            fprintf(stderr,"Erro na criacao do thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (i=0; i<nThreads; i++)
    {
        err = pthread_join(idsThread[i], NULL);

        if (err != 0)
        {
            fprintf(stderr,"Erro na juncao do thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    free(idsThread);
    free(parametros);
}

void *thrdSomaParcial(void *args)
{
    register unsigned int i, inicio, final;
    int *soma;
    int *vetor;

    inicio = ( (parametrosThread *) args)->posInicio;
    final  = ( (parametrosThread *) args)->posFinal;
    vetor  = ( (parametrosThread *) args)->vetorOrigem1;

    if ((soma = (int *) malloc(sizeof(int))) == NULL)
    {
        fprintf(stderr,"Problemas na alocacao para armazenamento da soma parcial\n");
        exit(EXIT_FAILURE);
    }

    *soma = 0;
    for (i=inicio; i<=final; i++)
        *soma += vetor[i];

    return ((void *) soma);
}

int reducao (int *matrizE, FILE *arquivoE, int tamanho, int nThreads)
{
    parametrosThread *parametros = alocaVetorParametrosThreads(nThreads+1);
    register int quantElementos = (tamanho * tamanho) / nThreads;
    pthread_t *idsThread = alocaIdsThreads(nThreads+1);
    void *somaParcial=NULL;
    register int i = 0;
    int soma=0;
    int err;

    // Parametros da gravação da matriz E
    parametros[nThreads].tamanho = tamanho;
    parametros[nThreads].vetorOrigem1 = matrizE;
    parametros[nThreads].arquivo = arquivoE;

    if (nThreads==1) {
        gravacaoMatriz((void *) &parametros[nThreads]);

        parametros[0].posInicio = 0;
        parametros[0].posFinal  = tamanho * tamanho;
        parametros[0].vetorOrigem1 = matrizE;
        soma = *(int*) thrdSomaParcial((void *) &parametros[0]);
        return soma;
    }

    // Thread de gravação da matriz E
    err = pthread_create(&idsThread[nThreads], NULL, gravacaoMatriz, (void *) &parametros[nThreads]);
    if (err != 0)
    {
        fprintf(stderr,"Erro na criacao do thread %d\n", i);
        exit(EXIT_FAILURE);
    }

    // Criação das threads de redução da matriz E
    for (i=0; i<nThreads; i++) {
        parametros[i].posInicio = quantElementos * i;
        parametros[i].posFinal  = (quantElementos * (i+1)) - 1;
        parametros[i].vetorOrigem1 = matrizE;

        err = pthread_create(&idsThread[i], NULL, thrdSomaParcial, (void *) &parametros[i]);

        if (err != 0)
        {
            fprintf(stderr,"Erro na criacao do thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Aguardando a thread de gravação
    err = pthread_join(idsThread[nThreads], NULL);

    if (err != 0)
    {
        fprintf(stderr,"Erro na juncao do thread %d\n", i);
        exit(EXIT_FAILURE);
    }

    // Aguardando as threads de redução e pegando a soma parcial
    for (i=0; i<nThreads; i++)
    {
        err = pthread_join(idsThread[i], &somaParcial);

        if (err != 0)
        {
            fprintf(stderr,"Erro na juncao do thread %d\n", i);
            exit(EXIT_FAILURE);
        }

        soma += *((int *) somaParcial);
        free(somaParcial);
    }
    free(idsThread);
    free(parametros);
    return soma;
}