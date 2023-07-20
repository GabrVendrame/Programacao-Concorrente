// Nome: Gabriel de Souza Vendrame
// RA: 112681

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

float **mat_A;
float **mat_B;
float **mat_Resultado;
int tamanho;

void aloca_matriz(){
    int linha;
    mat_A = (float **)malloc(tamanho * sizeof(float *));
    mat_B = (float **)malloc(tamanho * sizeof(float *));
    mat_Resultado = (float **)malloc(tamanho * sizeof(float *));
    for(linha = 0; linha < tamanho; linha++){
        mat_A[linha] = (float *)malloc(tamanho * sizeof(float));
        mat_B[linha] = (float *)malloc(tamanho * sizeof(float));
        mat_Resultado[linha] = (float *)malloc(tamanho * sizeof(float));
    }
}

void libera_matriz(){
    int linha;
    for(linha = 0; linha < tamanho; linha++){
        free(mat_A[linha]);
        free(mat_B[linha]);
        free(mat_Resultado[linha]);
    }
    free(mat_A);
    free(mat_B);
    free(mat_Resultado);
}

void preenche_matriz(){
    int linha, coluna;
    srand(time(NULL));
    for(linha = 0; linha < tamanho; linha++){
        for(coluna = 0; coluna < tamanho; coluna++){
            mat_A[linha][coluna] = ((float)rand() / RAND_MAX) * 10;
            mat_B[linha][coluna] = ((float)rand() / RAND_MAX) * 10;
        }
    }
}

void *multiplicar_matrizes(void *arg){
    int thread_id = ((int*) arg)[0];
    int num_threads = ((int*) arg)[1];
    int linha, coluna, auxiliar;

    for (linha = thread_id; linha < tamanho; linha += num_threads){
        for (coluna = 0; coluna < tamanho; coluna++){
            for (auxiliar = 0; auxiliar < tamanho; auxiliar++){
                mat_Resultado[linha][coluna] += mat_A[linha][auxiliar] * mat_B[auxiliar][coluna];
            }
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    int num_threads = atoi(argv[2]);
    int *args[num_threads], i;
    time_t tempo_inicial, tempo_final, tempo_de_execucao;
    pthread_t threads[num_threads];
    tamanho = atoi(argv[1]);

    if(argc != 3){
        printf("Instruções de uso: %s tamanho threads\n", argv[0]);
        return 1;
    }

    aloca_matriz();
    preenche_matriz();

    tempo_inicial = time(NULL);

    for(i = 0; i < num_threads; i++){
        args[i] = malloc(sizeof(int)*2);
        args[i][0] = i;
        args[i][1] = num_threads;
        pthread_create(&threads[i], NULL, multiplicar_matrizes, (void*)args[i]);
    }
    
    for(i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }

    tempo_final = time(NULL);

    libera_matriz();

    tempo_de_execucao = difftime(tempo_final, tempo_inicial);
    printf("Tempo de Execucao(aprox): %.2lds.\n", tempo_de_execucao);
    return 0;
}
