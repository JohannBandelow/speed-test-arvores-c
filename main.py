import csv
import time
import subprocess
import matplotlib.pyplot as plt
import random

INSERTION_TIMES_CSV = 'generated/insertion_times.csv'
DELETION_TIMES_CSV = 'generated/deletion_times.csv'
INSERCAO_JPG = 'generated/insercao.jpg'
DELECAO_JPG = 'generated/delecao.jpg'
FATOR_DE_SUAVIZACAO = 100

def main():
    print("Criando diretório de build")
    subprocess.run(["mkdir", "-p", "build"])

    print("Compilando códigos C")
    subprocess.run(["gcc", "-o", "build/avl-tree", "avl-tree.c", "utils.c"])
    subprocess.run(["gcc", "-o", "build/b-tree", "b-tree.c", "utils.c"])
    subprocess.run(["gcc", "-o", "build/red-black-tree", "red-black-tree.c", "utils.c"])

    with open(INSERTION_TIMES_CSV, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['Quantidade', 'Árvore AVL', 'Árvore Rubro-Negra', 'Árvore B (ordem 1)', 'Árvore B (ordem 5)', 'Árvore B (ordem 10)'])

        print("Iniciando teste de inserção")
        for i in range(10):
            quantity = (i + 1) * 1000
            print("Criando valores para o teste, quantidade: " + str(quantity))
            create_dataset(quantity)
            roda_rotina_insercao(quantity, writer)

    with open(DELETION_TIMES_CSV, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['Quantidade', 'Árvore AVL', 'Árvore Rubro-Negra', 'Árvore B (ordem 1)', 'Árvore B (ordem 5)', 'Árvore B (ordem 10)'])

        print("Iniciando teste de deleção")
        for i in range(10):
            quantity = (i + 1) * 1000
            print("Criando valores para o teste, quantidade: " + str(quantity))
            create_dataset(quantity)
            roda_rotina_delecao(quantity, writer)


def roda_rotina_delecao(quantity, writer):
    avl_times = []
    red_black_times = []
    b1_times = []
    b5_times = []
    b10_times = []

    for _ in range(FATOR_DE_SUAVIZACAO):
        start_time = time.time()
        run_avl_tree(2)
        avl_times.append(to_millis(time.time() - start_time))

        start_time = time.time()
        run_red_black_tree(2)
        red_black_times.append(to_millis(time.time() - start_time))

        start_time = time.time()
        run_b_tree(2, 2)
        b1_times.append(to_millis(time.time() - start_time))

        start_time = time.time()
        run_b_tree(5, 2)
        b5_times.append(to_millis(time.time() - start_time))

        start_time = time.time()
        run_b_tree(10, 2)
        b10_times.append(to_millis(time.time() - start_time))

    avl_insertion_time = sum(avl_times) / len(avl_times)
    red_black_time = sum(red_black_times) / len(red_black_times)
    b1_tree_time = sum(b1_times) / len(b1_times)
    b5_tree_time = sum(b5_times) / len(b5_times)
    b10_tree_time = sum(b10_times) / len(b10_times)

    writer.writerow([quantity, avl_insertion_time, red_black_time, b1_tree_time, b5_tree_time, b10_tree_time])

def roda_rotina_insercao(quantity, writer):
    avl_times = []
    red_black_times = []
    b1_times = []
    b5_times = []
    b10_times = []

    for _ in range(FATOR_DE_SUAVIZACAO):
        start_time = time.time()
        run_avl_tree(1)
        avl_times.append(to_millis(time.time() - start_time))

        start_time = time.time()
        run_red_black_tree(1)
        red_black_times.append(to_millis(time.time() - start_time))

        start_time = time.time()
        run_b_tree(1, 1)
        b1_times.append(to_millis(time.time() - start_time))

        start_time = time.time()
        run_b_tree(5, 1)
        b5_times.append(to_millis(time.time() - start_time))

        start_time = time.time()
        run_b_tree(10, 1)
        b10_times.append(to_millis(time.time() - start_time))

    avl_insertion_time = sum(avl_times) / len(avl_times)
    red_black_time = sum(red_black_times) / len(red_black_times)
    b1_tree_time = sum(b1_times) / len(b1_times)
    b5_tree_time = sum(b5_times) / len(b5_times)
    b10_tree_time = sum(b10_times) / len(b10_times)

    writer.writerow([quantity, avl_insertion_time, red_black_time, b1_tree_time, b5_tree_time, b10_tree_time])

def plot_delete_graph():
    plt.clf()
    quantities = []
    avl_times = []
    red_black_times = []
    b1_times = []
    b5_times = []
    b10_times = []

    with open(DELETION_TIMES_CSV, 'r') as csvfile:
        reader = csv.reader(csvfile)
        next(reader)
        for row in reader:
            quantities.append(int(row[0]))
            avl_times.append(float(row[1]))
            red_black_times.append(float(row[2]))
            b1_times.append(float(row[3]))
            b5_times.append(float(row[4]))
            b10_times.append(float(row[5]))

    plt.plot(quantities, avl_times, label='Árvore AVL')
    plt.plot(quantities, red_black_times, label='Árvore Rubro-Negra')
    plt.plot(quantities, b1_times, label='Árvore B (ordem 1)')
    plt.plot(quantities, b5_times, label='Árvore B (ordem 5)')
    plt.plot(quantities, b10_times, label='Árvore B (ordem 10)')

    plt.xlabel('Quantidade')
    plt.ylabel('Tempo (ms)')
    plt.title('Tempo de deleção das árvores em função da quantidade')
    plt.legend()
    plt.show()
    plt.savefig(DELECAO_JPG)

def plot_graph():
    plt.clf()
    quantities = []
    avl_times = []
    red_black_times = []
    b1_times = []
    b5_times = []
    b10_times = []

    with open(INSERTION_TIMES_CSV, 'r') as csvfile:
        reader = csv.reader(csvfile)
        next(reader)
        for row in reader:
            quantities.append(int(row[0]))
            avl_times.append(float(row[1]))
            red_black_times.append(float(row[2]))
            b1_times.append(float(row[3]))
            b5_times.append(float(row[4]))
            b10_times.append(float(row[5]))

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
    plt.savefig(INSERCAO_JPG)

def to_millis(seconds):
    return seconds * 1000

def create_dataset(quantity):
    with open('build/values.txt', 'w') as file:
        for i in range(quantity):
            file.write(f'{random.randint(1, 200000)}\n')

def run_red_black_tree(rotina):
    subprocess.run(["./build/red-black-tree", str(rotina)])

def run_b_tree(ordem, rotina):
    subprocess.run(["./build/b-tree", str(ordem), str(rotina)])

def run_avl_tree(rotina):
    subprocess.run(["./build/avl-tree", str(rotina)])

if __name__ == '__main__':
    main()
    plot_graph()
    plot_delete_graph()
