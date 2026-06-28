import os
import random

def gerar_grafo(nome_arquivo, num_vertices, num_arestas):
    os.makedirs('inputs', exist_ok=True)
    caminho = os.path.join('inputs', nome_arquivo)
    
    arestas = set()
    max_arestas = num_vertices * (num_vertices - 1)
    num_arestas = min(num_arestas, max_arestas)
    
    print(f"Gerando {caminho} (V={num_vertices}, E={num_arestas})...")
    
    while len(arestas) < num_arestas:
        u = random.randint(0, num_vertices - 1)
        v = random.randint(0, num_vertices - 1)
        if u != v:
            arestas.add((u, v))
            
    with open(caminho, 'w') as f:
        # CORREÇÃO: Escreve APENAS o número de vértices na primeira linha
        f.write(f"{num_vertices}\n")
        
        for u, v in arestas:
            f.write(f"{u} {v}\n")

if __name__ == '__main__':
    gerar_grafo("esparso_100.txt", 100, 250)
    gerar_grafo("esparso_250.txt", 250, 600)
    gerar_grafo("esparso_500.txt", 500, 1200)
    gerar_grafo("esparso_1000.txt", 1000, 2500)
    gerar_grafo("denso_100.txt", 100, 8000)
    gerar_grafo("denso_250.txt", 250, 55000)
    gerar_grafo("denso_500.txt", 500, 220000)