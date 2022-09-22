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

### Dados levantados

A partir da avaliação dos tempos médios de execução, os resultados obtidos foram: 

- Em matrizes 500x500:
    #### Sequencial 
    - Tempo inicialização: 0.0019277
    - Tempo processamento: 0.6991437
    - Tempo finalização: 0.0017117

    #### Concorrente com 1 thread

    - Tempo inicialização: 0.0015236
    - Tempo processamento: 0.7024403
    - Tempo finalização: 0.0019716

    #### Concorrente com 2 threads
    
    - Tempo inicialização: 0.0011446
    - Tempo processamento: 0.365737
    - Tempo finalização: 0.001898

    #### Concorrente com 4 threads
    
    - Tempo inicialização: 0.001016
    - Tempo processamento: 0.2007143
    - Tempo finalização: 0.0017343

    #### Concorrente com 8 threads
    
    - Tempo inicialização: 0.0011373
    - Tempo processamento: 0.1600483
    - Tempo finalização: 0.0015513


- Em matrizes 1000x1000:
    #### Sequencial 
    - Tempo inicialização: 0.0053513 
    - Tempo processamento: 5.658638
    - Tempo finalização: 0.004509

    #### Concorrente com 1 thread

    - Tempo inicialização: 0.00379
    - Tempo processamento: 5.686151
    - Tempo finalização: 0.004976

    #### Concorrente com 2 threads
    
    - Tempo inicialização: 0.0027156
    - Tempo processamento: 2.8758673
    - Tempo finalização: 0.0055546

    #### Concorrente com 4 threads
    
    - Tempo inicialização: 0.003112
    - Tempo processamento: 1.758017
    - Tempo finalização: 0.0057

    #### Concorrente com 8 threads
    
    - Tempo inicialização: 0.0029463
    - Tempo processamento: 1.1567823
    - Tempo finalização: 0.005535


- Em matrizes 2000x2000:

    #### Sequencial 
    - Tempo inicialização: 0.0136376
    - Tempo processamento: 29.105089
    - Tempo finalização: 0.0128883

    #### Concorrente com 1 thread

    - Tempo inicialização: 0.0158346
    - Tempo processamento: 29.8615773
    - Tempo finalização: 0.015561

    #### Concorrente com 2 threads
    
    - Tempo inicialização: 0.0140156
    - Tempo processamento: 16.005618
    - Tempo finalização: 0.0141126

    #### Concorrente com 4 threads
    
    - Tempo inicialização: 0.011113
    - Tempo processamento: 9.363465
    - Tempo finalização: 0.0137223

    #### Concorrente com 8 threads
    
    - Tempo inicialização: 0.0089146
    - Tempo processamento: 7.032961
    - Tempo finalização: 0.012217



Considerando a máquina utilizada, que contém ***8 núcleos de CPU***, os resultados de tempo sequencial, tempo concorrente e ganho de desempenho estimado obtidos foram: 

- Em matrizes 500x500: 
    ***Tempo sequencial:*** 0.7027831s
    #### Com 1 thread
    - Tempo concorrente: 0.7059355s
    - Ganho de desempenho: 0.99553443622

    #### Com 2 threads
    - Tempo concorrente: 0.3687796s
    - Ganho de desempenho: 1.90569950182

    #### Com 4 threads
    - Tempo concorrente: 0.2034646s
    - Ganho de desempenho: 3.45408046412

    #### Com 8 threads
    - Tempo concorrente: 0.1627369s
    - Ganho de desempenho: 4.31852333429


- Em matrizes 1000x1000: 
    ***Tempo sequencial:*** 5.6684983
    #### Com 1 thread
    - Tempo concorrente: 5.694917
    - Ganho de desempenho: 0.9953610035

    #### Com 2 threads
    - Tempo concorrente: 2.8841375
    - Ganho de desempenho: 1.96540501276

    #### Com 4 threads
    - Tempo concorrente: 1.766829
    - Ganho de desempenho: 3.208289144

    #### Com 8 threads
    - Tempo concorrente: 1.1652636
    - Ganho de desempenho: 4.86456309113


- Em matrizes 2000x2000: 
    ***Tempo sequencial:*** 29.1316149
    #### Com 1 thread
    - Tempo concorrente: 29.8929729
    - Ganho de desempenho: 0.9745305359

    #### Com 2 threads
    - Tempo concorrente: 16.0337462
    - Ganho de desempenho: 1.81689385229

    #### Com 4 threads
    - Tempo concorrente: 9.3883003
    - Ganho de desempenho: 3.10297007649

    #### Com 8 threads
    - Tempo concorrente: 7.0540926
    - Ganho de desempenho: 4.12974659561
