# OpenMP Performance Benchmarks

Atividades Ponderadas de Programação Paralela com OpenMP - comparação de performance entre algoritmos seriais e paralelos.

## Atividade 1: Soma de Vetores (main.c)

### Funcionalidades
- Soma de 100M elementos (serial vs paralelo)
- Teste com 2, 4, 8 e 16 threads
- Cálculo de speedup e eficiência
- Demonstração de divisão de trabalho entre threads

### Compilação e Execução
```bash
gcc -fopenmp -g main.c -o main
./main
```

### Exemplo de Output
```
=== TESTE DE SOMA DE VETOR COM OpenMP ===
Núm. de processadores disponíveis: 8
Tamanho do vetor: 100000000 elementos

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
```

## Atividade 2: Multiplicação de Matrizes (matrix.c)

### Funcionalidades
- Multiplicação de matrizes 1000x1000 (serial vs paralelo)
- Paralelização com `collapse(2)` para otimizar distribuição
- Teste com 2, 4, 8 e 16 threads
- Verificação de correção e análise de performance

### Compilação e Execução
```bash
gcc -fopenmp -g matrix.c -o matrix
./matrix
```

### Exemplo de Output
```
=== MULTIPLICAÇÃO DE MATRIZES COM OpenMP ===
Núm. de processadores disponíveis: 8
Dimensões: A(1000x1000) x B(1000x1000) = C(1000x1000)

--- VERSÃO SERIAL ---
Tempo: 2.451678 segundos

--- VERSÕES PARALELAS ---

Threads: 4
Tempo: 0.687432 segundos
✓ Resultado correto
Speedup: 3.57x
Eficiência: 89.2%
```

## Pré-requisitos
- GCC com suporte OpenMP

## Links dos Vídeos
- **Atividade 1 (Soma de Vetores)**: https://drive.google.com/file/d/1KmsLkpAVVH1mSvxm5fMHG40NL5IYADoX/view?usp=sharing
- **Atividade 2 (Multiplicação de Matrizes)**: https://drive.google.com/file/d/1sRj2IBRDIUY59XB6s1aP9uxRpBurk2X3/view?usp=sharing

## Conceitos Demonstrados
- **Atividade 1**: `reduction` clause para operações de soma
- **Atividade 2**: `collapse(2)` para paralelização de loops aninhados
- **Ambas**: Análise de speedup, eficiência e distribuição de carga