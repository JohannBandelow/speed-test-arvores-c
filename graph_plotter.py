import csv
import matplotlib.pyplot as plt

def plot_comp_effort_graph(csv_file, jpg_file, title):
    plt.clf()
    quantities = []
    avl_effort = []
    red_black_effort = []
    b1_effort = []
    b5_effort = []
    b10_effort = []

    with open(csv_file, 'r') as csvfile:
        reader = csv.reader(csvfile)
        next(reader)
        for row in reader:
            quantities.append(int(row[0]))
            avl_effort.append(float(row[2]))
            red_black_effort.append(float(row[4]))
            b1_effort.append(float(row[6]))
            b5_effort.append(float(row[8]))
            b10_effort.append(float(row[10]))

    plt.plot(quantities, avl_effort, label='Árvore AVL')
    plt.plot(quantities, red_black_effort, label='Árvore Rubro-Negra')
    plt.plot(quantities, b1_effort, label='Árvore B (ordem 1)')
    plt.plot(quantities, b5_effort, label='Árvore B (ordem 5)')
    plt.plot(quantities, b10_effort, label='Árvore B (ordem 10)')

    plt.xlabel('Quantidade')
    plt.yscale("log")
    plt.ylabel('Esforço')
    plt.title(title)
    plt.legend()
    plt.savefig(jpg_file)

def plot_time_graph(csv_file, jpg_file, title):
    plt.clf()
    quantities = []
    avl_times = []
    red_black_times = []
    b1_times = []
    b5_times = []
    b10_times = []

    with open(csv_file, 'r') as csvfile:
        reader = csv.reader(csvfile)
        next(reader)
        for row in reader:
            quantities.append(int(row[0]))
            avl_times.append(float(row[1]))
            red_black_times.append(float(row[3]))
            b1_times.append(float(row[5]))
            b5_times.append(float(row[7]))
            b10_times.append(float(row[9]))

    plt.plot(quantities, avl_times, label='Árvore AVL')
    plt.plot(quantities, red_black_times, label='Árvore Rubro-Negra')
    plt.plot(quantities, b1_times, label='Árvore B (ordem 1)')
    plt.plot(quantities, b5_times, label='Árvore B (ordem 5)')
    plt.plot(quantities, b10_times, label='Árvore B (ordem 10)')

    plt.xlabel('Quantidade')
    plt.ylabel('Tempo (ms)')
    plt.title(title)
    plt.legend()
    plt.savefig(jpg_file)
