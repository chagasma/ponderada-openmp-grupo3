#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1000  // Linhas de A
#define M 1000  // Colunas de A / Linhas de B  
#define P 1000  // Colunas de B

void multiplica_serial(int **A, int **B, int **C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            C[i][j] = 0;
            for (int k = 0; k < M; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void multiplica_paralela(int **A, int **B, int **C) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            C[i][j] = 0;
            for (int k = 0; k < M; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int** aloca_matriz(int linhas, int colunas) {
    int **matriz = (int**)malloc(linhas * sizeof(int*));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int*)malloc(colunas * sizeof(int));
    }
    return matriz;
}

void libera_matriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void inicializa_matriz(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = rand() % 10;
        }
    }
}

int verifica_resultado(int **C1, int **C2) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            if (C1[i][j] != C2[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    printf("=== MULTIPLICAÇÃO DE MATRIZES COM OpenMP ===\n");
    printf("Núm. de processadores disponíveis: %d\n", omp_get_num_procs());
    printf("Dimensões: A(%dx%d) x B(%dx%d) = C(%dx%d)\n\n", N, M, M, P, N, P);
    
    // Alocação das matrizes
    int **A = aloca_matriz(N, M);
    int **B = aloca_matriz(M, P);
    int **C_serial = aloca_matriz(N, P);
    int **C_paralela = aloca_matriz(N, P);
    
    // Inicialização com valores aleatórios
    srand(time(NULL));
    printf("Inicializando matrizes com valores aleatórios...\n");
    inicializa_matriz(A, N, M);
    inicializa_matriz(B, M, P);
    
    printf("\n--- VERSÃO SERIAL ---\n");
    double inicio = omp_get_wtime();
    multiplica_serial(A, B, C_serial);
    double tempo_serial = omp_get_wtime() - inicio;
    printf("Tempo: %.6f segundos\n", tempo_serial);
    
    printf("\n--- VERSÕES PARALELAS ---\n");
    int threads_teste[] = {2, 4, 8, 16};
    int num_testes = sizeof(threads_teste) / sizeof(threads_teste[0]);
    
    for (int t = 0; t < num_testes; t++) {
        int num_threads = threads_teste[t];
        
        omp_set_num_threads(num_threads);
        
        printf("\nThreads: %d\n", num_threads);
        
        inicio = omp_get_wtime();
        multiplica_paralela(A, B, C_paralela);
        double tempo_paralelo = omp_get_wtime() - inicio;
        
        printf("Tempo: %.6f segundos\n", tempo_paralelo);
        
        if (verifica_resultado(C_serial, C_paralela)) {
            printf("✓ Resultado correto\n");
        } else {
            printf("✗ Erro no cálculo paralelo!\n");
        }
        
        double speedup = tempo_serial / tempo_paralelo;
        printf("Speedup: %.2fx\n", speedup);
        
        double eficiencia = speedup / num_threads * 100;
        printf("Eficiência: %.1f%%\n", eficiencia);
    }
    
    printf("\n--- DEMONSTRAÇÃO DE THREADS ---\n");
    omp_set_num_threads(4);
    
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        int linhas_por_thread = N / num_threads;
        int linha_inicio = thread_id * linhas_por_thread;
        int linha_fim = (thread_id == num_threads - 1) ? N : linha_inicio + linhas_por_thread;
        
        printf("Thread %d processando linhas %d a %d\n", thread_id, linha_inicio, linha_fim - 1);
    }
    
    // Liberação de memória
    libera_matriz(A, N);
    libera_matriz(B, M);
    libera_matriz(C_serial, N);
    libera_matriz(C_paralela, N);
    
    return 0;
}