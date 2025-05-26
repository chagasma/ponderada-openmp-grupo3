# OpenMP Vector Sum Benchmark

Atividade Ponderada: Programação em OpenMP 1 - comparação de performance entre soma serial e paralela de vetores usando OpenMP.

Link do vídeo: https://drive.google.com/file/d/1KmsLkpAVVH1mSvxm5fMHG40NL5IYADoX/view?usp=sharing

## Funcionalidades
- Soma de 100M elementos (serial vs paralelo)
- Teste com 2, 4, 8 e 16 threads
- Cálculo de speedup e eficiência
- Demonstração de divisão de trabalho entre threads

## Pré-requisitos
- GCC com suporte OpenMP

## Compilação e Execução
```bash
gcc -fopenmp -g main.c -o main
./main
```

## Exemplo de output

```cmd
╭─inteli@Notebook-0213 ~/dev/experiments/test-openmp 
╰─$ ./main
=== TESTE DE SOMA DE VETOR COM OpenMP ===
Núm. de processadores disponíveis: 8
Tamanho do vetor: 100000000 elementos

Inicializando vetor com números aleatórios...

--- VERSÃO SERIAL ---
Resultado: 4950113584
Tempo: 0.319142 segundos

--- VERSÕES PARALELAS ---

Threads: 2
Resultado: 4950113584
Tempo: 0.125252 segundos
✓ Resultado correto
Speedup: 2.55x
Eficiência: 127.4%

Threads: 4
Resultado: 4950113584
Tempo: 0.145919 segundos
✓ Resultado correto
Speedup: 2.19x
Eficiência: 54.7%

Threads: 8
Resultado: 4950113584
Tempo: 0.123949 segundos
✓ Resultado correto
Speedup: 2.57x
Eficiência: 32.2%

Threads: 16
Resultado: 4950113584
Tempo: 0.112523 segundos
✓ Resultado correto
Speedup: 2.84x
Eficiência: 17.7%

--- DEMONSTRAÇÃO DE THREADS ---
Thread 0 processando elementos 0 a 24999999
Thread 1 processando elementos 25000000 a 49999999
Thread 2 processando elementos 50000000 a 74999999
Thread 3 processando elementos 75000000 a 99999999
```

