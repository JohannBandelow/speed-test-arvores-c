import csv
import time
import subprocess
import random
from graph_plotter import plot_time_graph, plot_comp_effort_graph

INSERTION_TIMES_CSV = 'generated/insertion_times.csv'
DELETION_TIMES_CSV = 'generated/deletion_times.csv'
INSERCAO_JPG = 'generated/insercao.jpg'
DELECAO_JPG = 'generated/delecao.jpg'
FATOR_DE_SUAVIZACAO = 10

class Operation:
    INSERT = 1
    DELETE = 2

def main():
    print("Criando diretório de build")
    subprocess.run(["mkdir", "-p", "build"])
    subprocess.run(["rm", "-rf", "generated"])
    subprocess.run(["mkdir", "-p", "generated"])
    subprocess.run(["rm", "-rf", "build/*"])

    print("Compilando códigos C")
    subprocess.run(["gcc", "-o", "build/avl-tree", "avl-tree.c"])
    subprocess.run(["gcc", "-o", "build/b-tree", "b-tree.c"])
    subprocess.run(["gcc", "-o", "build/red-black-tree", "red-black-tree.c"])

    with open(INSERTION_TIMES_CSV, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['Quantidade', 'Tempo AVL', 'Esforço AVL', 'Tempo Rubro-Negra', 'Esforço Rubro-Negra', 'Tempo Árvore B(1)', 'Esforço Árvore B(1)', 'Tempo Árvore B(5)', 'Esforço Árvore B(5)', 'Tempo Árvore B(10)', 'Esforço Árvore B(10)'])

        print("Iniciando teste de inserção")
        for i in range(10):
            quantity = (i + 1) * 1000
            print("Criando valores para o teste, quantidade: " + str(quantity))
            create_dataset(quantity)
            roda_rotina(Operation.INSERT, quantity, writer)

    with open(DELETION_TIMES_CSV, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['Quantidade', 'Tempo AVL', 'Esforço AVL', 'Tempo Rubro-Negra', 'Esforço Rubro-Negra', 'Tempo Árvore B(1)', 'Esforço Árvore B(1)', 'Tempo Árvore B(5)', 'Esforço Árvore B(5)', 'Tempo Árvore B(10)', 'Esforço Árvore B(10)'])

        print("Iniciando teste de deleção")
        for i in range(10):
            quantity = (i + 1) * 1000
            print("Criando valores para o teste, quantidade: " + str(quantity))
            create_dataset(quantity)
            roda_rotina(Operation.DELETE, quantity, writer)


def roda_rotina(operation, quantity, writer):
    avl_times = []
    avl_efforts = []
    rb_times = []
    rb_efforts = []
    b1_times = []
    b1_efforts = []
    b5_times = []
    b5_efforts = []
    b10_times = []
    b10_efforts = []

    for _ in range(FATOR_DE_SUAVIZACAO):
        start_time = time.time()
        avl_efforts.append(run_avl_tree(operation))
        avl_times.append(to_millis(time.time() - start_time))

        start_time = time.time()
        rb_efforts.append(run_red_black_tree(operation))
        rb_times.append(to_millis(time.time() - start_time))

        start_time = time.time()
        b1_efforts.append(run_b_tree(2, operation))
        b1_times.append(to_millis(time.time() - start_time))

        start_time = time.time()
        b5_efforts.append(run_b_tree(5, operation))
        b5_times.append(to_millis(time.time() - start_time))

        start_time = time.time()
        b10_efforts.append(run_b_tree(10, operation))
        b10_times.append(to_millis(time.time() - start_time))

    avl_insertion_time = sum(avl_times) / FATOR_DE_SUAVIZACAO
    red_black_time = sum(rb_times) / FATOR_DE_SUAVIZACAO
    b1_tree_time = sum(b1_times) / FATOR_DE_SUAVIZACAO
    b5_tree_time = sum(b5_times) / FATOR_DE_SUAVIZACAO
    b10_tree_time = sum(b10_times) / FATOR_DE_SUAVIZACAO
    avl_effort = sum(avl_efforts) / FATOR_DE_SUAVIZACAO
    rb_effort = sum(rb_efforts) / FATOR_DE_SUAVIZACAO
    b1_effort = sum(b1_efforts) / FATOR_DE_SUAVIZACAO
    b5_effort = sum(b5_efforts) / FATOR_DE_SUAVIZACAO
    b10_effort = sum(b10_efforts) / FATOR_DE_SUAVIZACAO

    writer.writerow([quantity, avl_insertion_time, avl_effort, red_black_time, rb_effort, b1_tree_time, b1_effort, b5_tree_time, b5_effort, b10_tree_time, b10_effort])

def to_millis(seconds):
    return seconds * 1000

def create_dataset(quantity):
    with open('build/values.txt', 'w') as file:
        for i in range(quantity):
            file.write(f'{random.randint(1, 2000)}\n')

def run_red_black_tree(rotina):
    output = subprocess.run(["./build/red-black-tree", str(rotina)], capture_output=True, text=True)
    return int(output.stdout.strip())

def run_b_tree(ordem, rotina):
    output = subprocess.run(["./build/b-tree", str(ordem), str(rotina)], capture_output=True, text=True)
    return int(output.stdout.strip())

def run_avl_tree(rotina):
    output = subprocess.run(["./build/avl-tree", str(rotina)], capture_output=True, text=True)
    return int(output.stdout.strip())

if __name__ == '__main__':
    main()
    plot_time_graph(INSERTION_TIMES_CSV, INSERCAO_JPG, 'Tempo de inserção')
    plot_time_graph(DELETION_TIMES_CSV, DELECAO_JPG, 'Tempo de deleção')
    plot_comp_effort_graph(INSERTION_TIMES_CSV, 'generated/insercao_esforco.jpg', 'Esforço de inserção')
    plot_comp_effort_graph(DELETION_TIMES_CSV, 'generated/delecao_esforco.jpg', 'Esforço de deleção')
