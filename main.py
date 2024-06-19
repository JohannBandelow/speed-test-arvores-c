import csv
import time
import subprocess
import matplotlib.pyplot as plt
import random

EXECUTION_TIMES_CSV = 'generated/execution_times.csv'
PLOT_JPG = 'generated/plot.jpg'

def main():
    print("Criando diretório de build")
    subprocess.run(["mkdir", "-p", "build"])

    print("Compilando códigos C")
    subprocess.run(["gcc", "-o", "build/avl-tree", "avl-tree.c", "utils.c"])
    subprocess.run(["gcc", "-o", "build/b-tree", "b-tree.c", "utils.c"])
    subprocess.run(["gcc", "-o", "build/red-black-tree", "red-black-tree.c", "utils.c"])

    with open(EXECUTION_TIMES_CSV, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['Execução', 'Quantidade', 'Árvore AVL', 'Árvore Rubro-Negra', 'Árvore B (ordem 1)', 'Árvore B (ordem 5)', 'Árvore B (ordem 10)'])

        print("Iniciando teste")
        for i in range(10):
            quantity = (i + 1) * 1000
            print("Criando valores para o teste, quantidade: " + str(quantity))
            create_dataset(quantity)

            avl_tree_times = []
            red_black_times = []
            b1_tree_times = []
            b5_tree_times = []
            b10_tree_times = []

            for _ in range(10):
                start_time = time.time()
                run_avl_tree()
                avl_tree_times.append(to_millis(time.time() - start_time))

                start_time = time.time()
                run_red_black_tree()
                red_black_times.append(to_millis(time.time() - start_time))

                start_time = time.time()
                run_b_tree(1)
                b1_tree_times.append(to_millis(time.time() - start_time))

                start_time = time.time()
                run_b_tree(5)
                b5_tree_times.append(to_millis(time.time() - start_time))

                start_time = time.time()
                run_b_tree(10)
                b10_tree_times.append(to_millis(time.time() - start_time))

            avl_tree_time = sum(avl_tree_times) / len(avl_tree_times)
            red_black_time = sum(red_black_times) / len(red_black_times)
            b1_tree_time = sum(b1_tree_times) / len(b1_tree_times)
            b5_tree_time = sum(b5_tree_times) / len(b5_tree_times)
            b10_tree_time = sum(b10_tree_times) / len(b10_tree_times)

            writer.writerow([i, quantity, avl_tree_time, red_black_time, b1_tree_time, b5_tree_time, b10_tree_time])

def plot_graph():
    quantities = []
    avl_times = []
    red_black_times = []
    b1_times = []
    b5_times = []
    b10_times = []

    with open(EXECUTION_TIMES_CSV, 'r') as csvfile:
        reader = csv.reader(csvfile)
        next(reader)  # Skip header row
        for row in reader:
            quantities.append(int(row[1]))
            avl_times.append(float(row[2]))
            red_black_times.append(float(row[3]))
            b1_times.append(float(row[4]))
            b5_times.append(float(row[5]))
            b10_times.append(float(row[6]))

    plt.plot(quantities, avl_times, label='Árvore AVL')
    plt.plot(quantities, red_black_times, label='Árvore Rubro-Negra')
    plt.plot(quantities, b1_times, label='Árvore B (ordem 1)')
    plt.plot(quantities, b5_times, label='Árvore B (ordem 5)')
    plt.plot(quantities, b10_times, label='Árvore B (ordem 10)')

    plt.xlabel('Quantidade')
    plt.ylabel('Tempo (ms)')
    plt.title('Tempo de execução das árvores em função da quantidade')
    plt.legend()
    plt.show()
    plt.savefig(PLOT_JPG)

def to_millis(seconds):
    return seconds * 1000

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
    plot_graph()
