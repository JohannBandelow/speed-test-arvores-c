import csv
import time
import subprocess
import random

def setup(quantity):
    with open('build/values.txt', 'w') as file:
        for i in range(quantity):
            file.write(f'{random.randint(-20000, 20000)}\n')

def run_b_tree():
    #subprocess.run(["gcc", "-o", "build/b-tree", "b-tree.c", "utils.c"])
    #subprocess.run(["./build/b-tree"])
    pass

def run_avl_tree():
    subprocess.run(["./build/avl-tree"])

def main():
    print("Criando diretório de build")
    subprocess.run(["mkdir", "-p", "build"])
    print("Compilando códigos C")
    subprocess.run(["gcc", "-o", "build/avl-tree", "avl-tree.c", "utils.c"])

    with open('execution_times.csv', 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['Execução', 'Quantidade', 'Árvore AVL'])

        print("Iniciando teste")
        for i in range(10):
            quantity = (i + 1) * 1000
            print("Criando valores para o teste, quantidade: " + str(quantity))
            setup(quantity)

            start_time = time.time()
            run_avl_tree()
            avl_tree_time = (time.time() - start_time) * 1000

            start_time = time.time()
            run_b_tree()
            b_tree_time = (time.time() - start_time) * 1000

            writer.writerow([i, quantity, avl_tree_time])

if __name__ == '__main__':
    main()