import random

# Gera múltiplas arestas saindo de cada nó com cabeça aleatória
num_nodes = 10000
maximo_de_aresta_por_no = 5
minimo_de_aresta_por_no = 1
ponderado = False
peso_minimo = 50
peso_maximo = 500

caminho=""

if ponderado:
    caminho = "instancias_grafo_ponderados/intancia_customizada.txt"
else:
    caminho = "instancias_grafos_n_ponderados/intancia_customizada.txt"

with open(caminho, "w") as file:
    for tail in range(1, num_nodes + 1):
        edges_from_node = random.randint(minimo_de_aresta_por_no, maximo_de_aresta_por_no)  # Define quantas arestas saem do nó
        for _ in range(edges_from_node):
            head = random.randint(1, num_nodes)
            if tail != head:
                weight = random.randint(peso_minimo, peso_maximo)
                if ponderado:
                    file.write(f"{tail} {head}  {weight}\n")
                else:
                    file.write(f"{tail} {head}\n")