# Escalonamento de Processos

Implementação de algoritmos de escalonamento de processos em C.

## Algoritmo implementado

- **FCFS** (First-Come, First-Served): algoritmo não-preemptivo que executa as tarefas na ordem em que chegam.

## Como compilar

```bash
gcc FCFS.c -o FCFS
```

## Como executar

```bash
./FCFS < 1.in
```

O programa lê os dados de entrada via redirecionamento e gera o arquivo `2.out` com o resultado do escalonamento.

## Como gerar o gráfico

```bash
python gantt-graph-generator.py
```

Quando solicitado, informe o arquivo de saída:

```
Insira o caminho do arquivo: 2.out
```

## Formato da entrada

```
<NUM_TAREFAS>
<tempos de ingresso>
<durações>
<prioridades>
```

## Formato da saída

```
FCFS
<NUM_TAREFAS>
<tempos de ingresso>
<índice da tarefa executada em cada instante de tempo>
```

## Requisitos

- GCC
- Python 3
- matplotlib
- numpy

## Integrantes

- Maria Luisa Sanches
- Pedro Prado
