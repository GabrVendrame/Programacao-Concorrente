// Nome: Gabriel de Souza Vendrame
// RA: 112681

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

    srand(7);

    for(linha = 0; linha < tamanho; linha++){
        for(coluna = 0; coluna < tamanho; coluna++){
            mat_A[linha][coluna] = ((float)rand() / RAND_MAX) * 10;
            mat_B[linha][coluna] = ((float)rand() / RAND_MAX) * 10;
        }
    }
}

void multiplicar_matrizes(){
    int linha, coluna, auxiliar;

    for (linha = 0; linha < tamanho; linha++){
        for (coluna = 0; coluna < tamanho; coluna++){
            for (auxiliar = 0; auxiliar < tamanho; auxiliar++){
                mat_Resultado[linha][coluna] += mat_A[linha][auxiliar] * mat_B[auxiliar][coluna];
            }
        }
    }
}

int main(int argc, char *argv[]){
    tamanho = atoi(argv[1]);
    time_t tempo_inicial, tempo_final, tempo_de_execução;

    if(argc != 2){
        printf("Instruções de uso: %s tamanho\n", argv[0]);
        return 1;
    }

    aloca_matriz();
    preenche_matriz();

    tempo_inicial = time(NULL);

    multiplicar_matrizes();

    tempo_final = time(NULL);

    libera_matriz();

    tempo_de_execução = difftime(tempo_final, tempo_inicial);
    printf("Tempo de Execucao(aprox): %.2lds.\n", tempo_de_execução);
    return 0;
}