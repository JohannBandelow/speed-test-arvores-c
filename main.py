import csv
import time
import subprocess
import random

def main():
    print("Criando diretório de build")
    subprocess.run(["mkdir", "-p", "build"])

    print("Compilando códigos C")
    subprocess.run(["gcc", "-o", "build/avl-tree", "avl-tree.c", "utils.c"])
    subprocess.run(["gcc", "-o", "build/b-tree", "b-tree.c", "utils.c"])
    subprocess.run(["gcc", "-o", "build/red-black-tree", "red-black-tree.c", "utils.c"])

    with open('execution_times.csv', 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['Execução', 'Quantidade', 'Árvore AVL', 'Árvore Rubro-Negra', 'Árvore B (ordem 1)', 'Árvore B (ordem 5)', 'Árvore B (ordem 10)'])

        print("Iniciando teste")
        for i in range(10):
            quantity = (i + 1) * 1000
            print("Criando valores para o teste, quantidade: " + str(quantity))
            create_dataset(quantity)

            start_time = time.time()
            run_avl_tree()
            avl_tree_time = to_millis(time.time() - start_time)

            start_time = time.time()
            run_red_black_tree()
            red_black_time = to_millis(time.time() - start_time)

            start_time = time.time()
            run_b_tree(1)
            b1_tree_time = to_millis(time.time() - start_time)

            start_time = time.time()
            run_b_tree(5)
            b5_tree_time = to_millis(time.time() - start_time)

            start_time = time.time()
            run_b_tree(10)
            b10_tree_time = to_millis(time.time() - start_time)

            writer.writerow([i, quantity, avl_tree_time, red_black_time, b1_tree_time, b5_tree_time, b10_tree_time])

def to_millis(seconds):
    return f'{seconds * 1000:.3f} ms'

def create_dataset(quantity):
    with open('build/values.txt', 'w') as file:
        for i in range(quantity):
            file.write(f'{random.randint(1, 200000)}\n')

def run_red_black_tree():
    subprocess.run(["./build/red-black-tree"])

def run_b_tree(ordem):
    subprocess.run(["./build/b-tree", str(ordem)])

def run_avl_tree():
    subprocess.run(["./build/avl-tree"])

if __name__ == '__main__':
    main()
