import subprocess

algoritmos = ["AVLTree", "BinarySearch", "BinarySearchTree", "LinearSearch", "RedBlackTree", "Treap"]

geradores = ["/gerar_resultado_rapido.py", "/gerar_resultado_medio.py", "/gerar_resultado_lento.py"]

scripts = []

for alg in algoritmos:
    for ger in geradores: 
        rodando = f"./aeed-p2/{alg+ger}"
        scripts.append(rodando)

for script in scripts:
    subprocess.run(["python", script])
