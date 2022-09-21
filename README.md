# Laboratório de Programação Concorrente

Projetos realizados nas práticas de laboratório da disciplina de Programação Concorrente do curso de Ciência da Computação na UFRJ.

<br>

## Laboratório 1: Introdução ao uso de threads em C

### Introdução

O objetivo deste Laboratório é aprender como criar programas concorrentes em C, usando as funções principais da biblioteca *Pthread*. As seguintes funções serão usadas:

- `int pthread create`
- `void pthread exit`
- `int pthread join` 

### Atividade
***Objetivo***: Implementar o seu primeiro programa concorrente! Escreva um programa com ***duas*** threads (além da thread principal), para ***aumentar em 10%*** cada elemento de um vetor de 10000 elementos. (Para cada elemento a_i do vetor, calcular o novo valor e escrever o resultado na mesma posição do elemento.) 

<br>

## Laboratório 2: Implementação e avaliação de aplicações concorrente (parte 1)

### Introdução

O objetivo deste Laboratório é implementar uma versão sequencial do problema de multiplicação de matrizes e a partir dessa implementação avaliar a possibilidade de ganho de desempenho em uma futura implementação concorrente do problema. Usaremos a linguagem C.

### Atividade

**Objetivo:** Projetar e implementar uma **solução sequencial** para o problema de **multiplicação de matrizes**, coletar informações sobre o seu tempo de execução, e estimar o ganho de desempenho que poderá ser alcançado com uma futura implementação concorrente. 

### Dados levantados

A partir da avaliação dos tempos médios de execução, os resultados obtidos foram: 

- Em matrizes 500x500:
    - Tempo inicialização: 0,000966633s
    - Tempo multiplicação: 0,711159s
    - Tempo finalização: 0,00190033s

- Em matrizes 1000x1000:
    - Tempo inicialização: 0,00478033s
    - Tempo multiplicação: 5,68276s
    - Tempo finalização: 0,004895s

- Em matrizes 2000x2000:
    - Tempo inicialização: 0,025214s
    - Tempo multiplicação: 47,27125s
    - Tempo finalização: 0,029573s

Considerando a máquina utilizada, que contém 8 núcleos de CPU, os resultados de tempo sequencial, tempo concorrente e ganho de desempenho estimado obtidos foram: 

- Em matrizes 500x500: 
    - Tempo sequencial: 0,714025963s
    - Tempo concorrente: 0,091761843s
    - Ganho de desempenho estimado: 7,781294922334984

- Em matrizes 1000x1000: 
    - Tempo sequencial: 5,69243533s
    - Tempo concorrente: 0,72002033s
    - Ganho de desempenho estimado: 7,905936947641465s

- Em matrizes 2000x2000: 
    - Tempo sequencial: 47,326037s
    - Tempo concorrente: 5,96369325s
    - Ganho de desempenho estimado: 7,935692701833717s

<br>

## Laboratório 3: Implementação e avaliação de aplicações concorrente (parte 2)

### Introdução

O objetivo deste Laboratório é implementar uma ***versão concorrente do problema de multiplicação de matrizes*** e avaliar o ganho de desempenho obtido.

### Atividade

***Objetivo:*** Projetar e implementar uma solução concorrente para o problema de multiplicação de matrizes, coletar informações sobre o seu tempo de execução, e calcular o ganho de desempenho obtido em relação a versão sequencial previamente implementada.

