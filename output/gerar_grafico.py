import sys
import pandas as pd
import matplotlib.pyplot as plt
import os

def gerar_grafico_margem_lucro(csv_file, mes_ano):
    if not os.path.exists(csv_file):
        print(f"Arquivo {csv_file} não encontrado.")
        return
    
    # Lendo o arquivo CSV
    df = pd.read_csv(csv_file, sep=';')
    
    # Filtrando os dados pelo mês e ano especificados
    df['Data'] = pd.to_datetime(df['Data'], format='%d/%m/%Y')
    df_filtrado = df[df['Data'].dt.strftime('%m/%Y') == mes_ano]

    if df_filtrado.empty:
        print(f"Não há dados para {mes_ano}.")
        return

    # Agrupando os dados pela categoria e calculando o lucro total
    df_agrupado = df_filtrado.groupby('Categoria')['LucroTotal'].sum()

    # Gerando o gráfico de barras
    plt.figure(figsize=(10, 6))
    plt.bar(df_agrupado.index, df_agrupado, color='skyblue')
    plt.xlabel('Categoria')
    plt.ylabel('Lucro Total')
    plt.title(f'Margem de Lucro por Categoria - {mes_ano}')
    plt.xticks(rotation=45)
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Uso: python gerar_grafico.py <mes/ano>")
    else:
        mes_ano = sys.argv[1]
        arquivo_csv = "margem_lucro.csv"  # Ajuste o caminho se necessário
        gerar_grafico_margem_lucro(arquivo_csv, mes_ano)
