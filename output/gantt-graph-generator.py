"""
	Este script gera os gráficos de execução (gráfico de gantt) dos algoritmos de 
	escalonamento vistos no Capítulo 6. Para seu correto funcionamento, você deve
	passar o caminho para um arquivo que esteja no formato de saída descrito na 
	especificação da atividade de SO.
	
	*** Requisitos mínimos de instalação: Python3, matplotlib e numpy	
	*** Para executar: python3 gantt-graph-generator.py

			 _   _                  /\/|       _ 
			/ \ | |_ ___ _ __   ___|/\/_  ___ | |
		   / _ \| __/ _ \ '_ \ / __/ _` |/ _ \| |
		  / ___ \ ||  __/ | | | (_| (_| | (_) |_|
		 /_/   \_\__\___|_| |_|\___\__,_|\___/(_)
								)_)              
		Não modifique este arquivo, visto que o mesmo 
		serve apenas para testar os arquivos de saída 
		dos algoritmos.
"""

import matplotlib.pyplot as plt
from sys import exit
from numpy import arange
from random import randint

# ----------------------------------------------------------------------
"""
	A função abaixo gera de forma aleatória uma cor no formato hexadecimal. Ex.: #316ad0
"""
def gnHex():
	r = randint(1,255)
	g = randint(1,255)
	b = randint(1,255)
	return '#'+f"{hex(r)[2:]:02}"+f"{hex(g)[2:]:02}"+f"{hex(b)[2:]:02}"
# ----------------------------------------------------------------------

# ----------------------------------------------------------------------
# lê caminho do arquivo fornecido pelo usuário
path = input("Insira o caminho do arquivo (Ex.: 1.out): ")

"""
	O trecho de código abaixo lê os dados do arquivo e cria um dicionário de tempos:
	Ex.: Para o arquivo 1.out de exemplo, o resultado será:
    {'1': [[1, 2], [7, 8], [14]], '2': [[3, 4]], '3': [[5, 6], [12, 13]], '4': [[9]], '5': [[10, 11]]}	
"""
try:
	file = open(path, 'r') # abre arquivo
	
	titulo = file.readline() # lê título do gráfico
	
	n_tarefas = int(file.readline()) # lê quantidade de tarefas	
	
	tempos = {} #dict representa os tempos de cada tarefa
	# inicializa dict de tempos
	for i in range(1, n_tarefas + 1, 1):    
		tempos[str(i)] = []
		
	# pega os tempos de ingresso
	ingresso = [int(str(next(file)).strip()) for _ in range(n_tarefas)]
	
	# lê os dados de processamento
	count = 0
	for line in file:
		if len(tempos[line.strip()]) == 0 or (count - tempos[line.strip()][-1][-1]) > 1:
			tempos[line.strip()].append([count])
			
		for t in tempos[line.strip()]:			
			for sub_t in t:			
				if count - 1 == t[-1]:
					t.append(count)									
									
		count += 1
		
	file.close() # fecha arquivo
	
except FileNotFoundError:
        print(f"Arquivo '{path}' não encontrado")
        exit(0)
except PermissionError:
        print(f"Você não possui permissão para ler o arquivo '{path}'")
        exit(0)
except IOError:
        print(f"Ocorreu um erro ao tentar ler o arquivo '{path}'")
        exit(0)
# ----------------------------------------------------------------------

# ----------------------------------------------------------------------
# Gera o gráfico com tempos de espera e de execução com base nos dados lidos
for i in range(1, n_tarefas + 1, 1):		
	tarefa = f"$t_{str(i)}$"
	cor = gnHex()
		
	#plota tempos de espera
	for j in range(len(tempos[str(i)])):		
		sub_t = tempos[str(i)][j]
		fim = sub_t[0]
		if j == 0: # tempo de espera inicial
			inicio = ingresso[i - 1]
			duracao = fim - inicio
		else: # demais tempos
			sub_t_ant = tempos[str(i)][j - 1]
			inicio = sub_t_ant[-1] + 1
			duracao = fim - inicio

		plt.barh(tarefa, duracao, left=inicio, zorder=3, color='#fff', edgecolor= '#000')
			
	# plota tempos de execução
	for sub_t in tempos[str(i)]:
		inicio = sub_t[0]
		fim = (sub_t[-1] + 1)
		duracao = fim - inicio
		plt.barh(tarefa, duracao, left=inicio, zorder=3, color=cor, edgecolor= '#000')		

# Configuração de rótulos, título, grid e eixos	
plt.xlabel('Duração')
plt.ylabel('Tarefas')	
left, right = plt.xlim() # limites em x
plt.xticks(arange(right)) # intervalos em x
plt.grid(color='#000', linestyle='dotted', axis='x', linewidth=.5, dashes=(1,5), zorder=0)
plt.title(titulo)
#exibe o gráfico completo
plt.show()	
# ----------------------------------------------------------------------
