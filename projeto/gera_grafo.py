import networkx as nx
import random

# Parâmetros
num_vertices = 100  # Número de vértices no grafo
probabilidade_conexao = 0.7  # Probabilidade de haver uma aresta entre dois vértices (ajuste conforme necessário)

# Crie um grafo aleatório densamente conectado
grafo = nx.fast_gnp_random_graph(num_vertices, probabilidade_conexao)

# Nome do arquivo de saída
nome_arquivo = "grafo_teste.txt"

# Abra o arquivo para escrita
with open(nome_arquivo, 'w') as arquivo:
    # Escreva a quantidade de vértices e número de arestas na primeira linha
    arquivo.write(f"{num_vertices} {grafo.number_of_edges()}\n")

    # Escreva as arestas no formato de lista de adjacência
    for aresta in grafo.edges():
        arquivo.write(f"{aresta[0]+1} {aresta[1]+1}\n")  # +1 para ajustar os índices (começando em 1)

print(f"Grafo densamente conectado gerado e salvo em '{nome_arquivo}'.")

# Image of the generated graph
import matplotlib.pyplot as plt

# Alterar edges do grafo para edge + 1
novas_arestas = [(u + 1, v + 1) for u, v in grafo.edges()]
novo_grafo = nx.Graph()
novo_grafo.add_edges_from(novas_arestas)
novo_grafo.add_nodes_from([n + 1 for n in grafo.nodes()])

# Desenhar o grafo
nx.draw(novo_grafo, with_labels=True)
plt.show()