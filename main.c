#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 100000000  // 100.000.000

long long soma_serial(int *vetor, int tamanho) {
    long long soma = 0;
    for (int i = 0; i < tamanho; i++) {
        soma += vetor[i];
    }
    return soma;
}

long long soma_paralela(int *vetor, int tamanho) {
    long long soma = 0;
    
    // reduction clause soma os valores parciais
    #pragma omp parallel for reduction(+:soma)
    for (int i = 0; i < tamanho; i++) {
        soma += vetor[i];
    }
    
    return soma;
}

int main() {
    printf("=== TESTE DE SOMA DE VETOR COM OpenMP ===\n");
    printf("Núm. de processadores disponíveis: %d\n", omp_get_num_procs());
    printf("Tamanho do vetor: %d elementos\n\n", N);
    
    // alocação de memória
    int *vetor = (int*)malloc(N * sizeof(int));
    if (vetor == NULL) {
        printf("Erro na alocação de memória!\n");
        return 1;
    }
    
    // inicialização com números aleatórios
    srand(time(NULL));
    printf("Inicializando vetor com números aleatórios...\n");
    for (int i = 0; i < N; i++) {
        vetor[i] = rand() % 100;
    }
    
    printf("\n--- VERSÃO SERIAL ---\n");
    double inicio = omp_get_wtime();
    long long resultado_serial = soma_serial(vetor, N);
    double tempo_serial = omp_get_wtime() - inicio;
    printf("Resultado: %lld\n", resultado_serial);
    printf("Tempo: %.6f segundos\n", tempo_serial);


    
    printf("\n--- VERSÕES PARALELAS ---\n");
    int threads_teste[] = {2, 4, 8, 16};
    int num_testes = sizeof(threads_teste) / sizeof(threads_teste[0]);
    
    for (int t = 0; t < num_testes; t++) {
        int num_threads = threads_teste[t];
        
        omp_set_num_threads(num_threads);
        
        printf("\nThreads: %d\n", num_threads);
        
        inicio = omp_get_wtime();
        long long resultado_paralelo = soma_paralela(vetor, N);
        double tempo_paralelo = omp_get_wtime() - inicio;
        
        printf("Resultado: %lld\n", resultado_paralelo);
        printf("Tempo: %.6f segundos\n", tempo_paralelo);
        
        if (resultado_paralelo == resultado_serial) {
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
        int chunk_size = N / num_threads;
        int inicio_chunk = thread_id * chunk_size;
        int fim_chunk = (thread_id == num_threads - 1) ? N : inicio_chunk + chunk_size;
        
        printf("Thread %d processando elementos %d a %d\n", thread_id, inicio_chunk, fim_chunk - 1);
    }
    
    free(vetor);
    return 0;
}