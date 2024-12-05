import networkx as nx

# Abrir o arquivo e pular a primeira linha
with open("grafo.txt", 'r') as arquivo:
    next(arquivo)  # Pula a primeira linha

    # Lê o grafo a partir das linhas restantes
    G = nx.parse_adjlist(arquivo)

# Encontrar todas as cliques maximais
cliques_maximais = list(nx.find_cliques(G))

# Encontrar a clique máxima (a maior)
clique_maxima = max(cliques_maximais, key=len)

# Salvar as cliques maximais em um arquivo
with open("verificacao.txt", 'w') as arquivo:
    arquivo.write(f"Cliques maximais encontradas\n")
    for clique in cliques_maximais:
        arquivo.write(f"{' '.join(map(str, clique))}\n")
    arquivo.write(f"\nClique máxima encontrada\n")
    arquivo.write(f"{len(clique_maxima)} = {' '.join(map(str, clique_maxima))}\n")
