import matplotlib.pyplot as plt
import numpy as np

# --- Dados médios coletados de suas execuções com 10.000 elementos ---

# Métricas para Quick Sort
quick_sort_wall_time = 0.005169
quick_sort_memory_variation = 51.2 # KB (média)

# Métricas para Shell Sort
shell_sort_wall_time = 0.001867
shell_sort_memory_variation = 76.8 # KB (média)

# --- Gráfico de Barras para Tempo de Execução (Wall Clock Time) ---
labels = ['Quick Sort', 'Shell Sort']
wall_times = [quick_sort_wall_time, shell_sort_wall_time]

plt.figure(figsize=(8, 6))
bars = plt.bar(labels, wall_times, color=['skyblue', 'lightcoral'])
plt.ylabel('Tempo de Execução (segundos)')
plt.title('Comparação do Tempo de Execução (Wall Clock) para Array de 10.000 Elementos')
plt.ylim(0, max(wall_times) * 1.2) # Ajusta o limite Y para melhor visualização

# Adicionar valores nas barras
for bar in bars:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2, yval + 0.0005, round(yval, 6), ha='center', va='bottom')

plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.savefig('comparacao_tempo_10000_elementos.png') # Salva o gráfico como imagem
plt.show()

# --- Gráfico de Barras para Variação de Memória (RSS) ---
memory_variations = [quick_sort_memory_variation, shell_sort_memory_variation]

plt.figure(figsize=(8, 6))
bars = plt.bar(labels, memory_variations, color=['lightgreen', 'orange'])
plt.ylabel('Variação de Memória (KB)')
plt.title('Comparação da Variação de Memória (RSS) para Array de 10.000 Elementos')
plt.ylim(0, max(memory_variations) * 1.2) # Ajusta o limite Y

# Adicionar valores nas barras
for bar in bars:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2, yval + 5, round(yval, 2), ha='center', va='bottom')

plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.savefig('comparacao_memoria_10000_elementos.png') # Salva o gráfico como imagem
plt.show()

print("\nGráficos gerados e salvos como 'comparacao_tempo_10000_elementos.png' e 'comparacao_memoria_10000_elementos.png' na mesma pasta.")