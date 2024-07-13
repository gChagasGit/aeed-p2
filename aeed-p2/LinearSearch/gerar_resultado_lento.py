import subprocess
import os
import platform
import numpy as np

################
# INPUTS
################
N_REPETICOES = 1
rodar_algoritmos = [1, 2, 3, 4]
rodar_listas = [6]
nome_artefato = "lento"
nome_exe = "LinearSearch"

################
# CONSTANTES
################
raiz = os.path.abspath(os.path.dirname(__file__))

# Verificar o sistema operacional
sistema_operacional = platform.system()
if sistema_operacional == "Windows":
    nome_exe += ".exe"
    output_dir = os.path.join(raiz, "output")
    EXE = os.path.join(output_dir, nome_exe)
else:  # Assumimos que é Linux
    output_dir = raiz
    EXE = os.path.join(output_dir, nome_exe)

# print(f"Executável: {EXE}")

PATH_RESULTADOS = os.path.join(raiz, "resultados")
if not os.path.exists(PATH_RESULTADOS):
    os.makedirs(PATH_RESULTADOS)
ARQUIVO_FINAL = os.path.join(PATH_RESULTADOS, f'resultado_{nome_artefato}.txt')
dic_listas = {1: "ordenada", 2: "inversa", 3: "quase", 4: "aleatoria"}
dic_tamanho = {1: "1e1", 2: "1e2", 3: "1e3", 4: "1e4", 5: "1e5", 6: "1e6"}

#################
# RODAR ALGORITMO
#################
for algo in rodar_algoritmos:
    for qtde_lista in rodar_listas:
        print(f'RUN: {dic_listas[algo]} com {dic_tamanho[qtde_lista]} itens...')
        result_insercao = []
        result_busca = []
        result_remocao = []
        for _ in range(N_REPETICOES):
            try:
                print(f'"{nome_exe}" {algo} {qtde_lista}')
                output = subprocess.getoutput(f'"{EXE}" {algo} {qtde_lista}')
                metrica = output.split('\n')

                if len(metrica) < 3:
                    print(f'"{nome_exe}" {algo} {qtde_lista} | len(metrica) {len(metrica)} | metrica -> {metrica}')
                    raise ValueError(f"Saída inesperada do executável: {output}")
              
                # Parsing the output for insertion
                tempo_insercao = float(metrica[0].split('=')[1].split(';')[0])
                comp_insercao = int(metrica[0].split('=')[2].split(';')[0])
                result_insercao.append((tempo_insercao, comp_insercao))
                
                # Parsing the output for search
                tempo_busca = float(metrica[1].split('=')[1].split(';')[0])
                comp_busca = int(metrica[1].split('=')[2].split(';')[0])
                result_busca.append((tempo_busca, comp_busca))
                
                # Parsing the output for removal
                tempo_remocao = float(metrica[2].split('=')[1].split(';')[0])
                comp_remocao = int(metrica[2].split('=')[2].split(';')[0])
                result_remocao.append((tempo_remocao, comp_remocao))
                
            except Exception as e:
                print(f"Erro ao executar {nome_exe}: {e}")
                continue
            
        # print("-> calcular resultados")

        if len(result_insercao) == 0 or len(result_busca) == 0 or len(result_remocao) == 0:
            print("Nenhum resultado válido foi coletado.")
            continue

        result_insercao = np.array(result_insercao)
        result_busca = np.array(result_busca)
        result_remocao = np.array(result_remocao)

        # Inserção
        tempo_media_insercao = np.mean(result_insercao[:, 0])
        tempo_std_insercao = np.std(result_insercao[:, 0])
        comp_media_insercao = np.mean(result_insercao[:, 1])
        comp_std_insercao = np.std(result_insercao[:, 1])

        # Busca
        tempo_media_busca = np.mean(result_busca[:, 0])
        tempo_std_busca = np.std(result_busca[:, 0])
        comp_media_busca = np.mean(result_busca[:, 1])
        comp_std_busca = np.std(result_busca[:, 1])

        # Remoção
        tempo_media_remocao = np.mean(result_remocao[:, 0])
        tempo_std_remocao = np.std(result_remocao[:, 0])
        comp_media_remocao = np.mean(result_remocao[:, 1])
        comp_std_remocao = np.std(result_remocao[:, 1])

        # print("-> gerar txt")

        with open(ARQUIVO_FINAL, "a") as myfile:
            myfile.write(f"\n{dic_listas[algo]} {dic_tamanho[qtde_lista]}  \n")
            # Inserção
            myfile.write(f"TEMPO_INSERCAO: {tempo_media_insercao} e std:{tempo_std_insercao} \n")
            myfile.write(f"COMP_INSERCAO: {comp_media_insercao} e std:{comp_std_insercao} \n")
            myfile.write("------------------\n")
            # Busca
            myfile.write(f"TEMPO_BUSCA: {tempo_media_busca} e std:{tempo_std_busca} \n")
            myfile.write(f"COMP_BUSCA: {comp_media_busca} e std:{comp_std_busca} \n")
            myfile.write("------------------\n")
            # Remoção
            myfile.write(f"TEMPO_REMOCAO: {tempo_media_remocao} e std:{tempo_std_remocao} \n")
            myfile.write(f"COMP_REMOCAO: {comp_media_remocao} e std:{comp_std_remocao} \n")
            myfile.write("------------------\n")
