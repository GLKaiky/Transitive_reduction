import pandas as pd
import matplotlib.pyplot as plt

# 1. Lê o arquivo CSV gerado pelo seu programa em C++
df = pd.read_csv("resultados_benchmark.csv")

# 2. Separa os dados em dois grupos (Esparsos e Densos)
df_esparso = df[df['tipo_densidade'] == 'Esparso']
df_denso = df[df['tipo_densidade'] == 'Denso']

# 3. Prepara a janela com 2 gráficos (1 linha, 2 colunas)
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))

# ==========================================
# GRÁFICO 1: GRAFOS ESPARSOS
# ==========================================
# Filtra os tempos de cada estrutura
matriz_esp = df_esparso[df_esparso['algoritmo'] == 'Matriz']
lista_esp = df_esparso[df_esparso['algoritmo'] == 'Lista']

# Desenha as linhas
ax1.plot(matriz_esp['vertices'], matriz_esp['tempo_us'], label='Matriz - Solução de Aho (1972)', marker='o', color='red')
ax1.plot(lista_esp['vertices'], lista_esp['tempo_us'], label='Lista - Solução com Caminhamento', marker='o', color='blue')

# Configurações visuais
ax1.set_title('Cenário: Grafos Esparsos')
ax1.set_xlabel('Quantidade de Vértices')
ax1.set_ylabel('Tempo de Execução (µs)')
ax1.legend()
ax1.grid(True)

# ==========================================
# GRÁFICO 2: GRAFOS DENSOS
# ==========================================
# Filtra os tempos de cada estrutura
matriz_denso = df_denso[df_denso['algoritmo'] == 'Matriz']
lista_denso = df_denso[df_denso['algoritmo'] == 'Lista']

# Desenha as linhas
ax2.plot(matriz_denso['vertices'], matriz_denso['tempo_us'], label='Matriz - Solução de Aho (1972)', marker='s', color='red')
ax2.plot(lista_denso['vertices'], lista_denso['tempo_us'], label='Lista - Solução com Caminhamento', marker='s', color='blue')

# Configurações visuais
ax2.set_title('Cenário: Grafos Densos')
ax2.set_xlabel('Quantidade de Vértices')
ax2.set_ylabel('Tempo de Execução (µs)')
ax2.legend()
ax2.grid(True)

# ==========================================
# FINALIZAÇÃO
# ==========================================
plt.tight_layout() # Evita que os textos fiquem sobrepostos
plt.savefig("grafico_simples.png") # Salva a imagem na pasta
print("Gráfico salvo como 'grafico_simples.png'!")
plt.show() # Abre a janela na tela