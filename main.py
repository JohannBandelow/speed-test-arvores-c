import csv
import time
import subprocess

def setup():
    subprocess.run(["mkdir", "-p", "build"])

def run_b_tree():
    #subprocess.run(["gcc", "-o", "build/b-tree", "b-tree.c", "utils.c"])
    #subprocess.run(["./build/b-tree"])
    pass

def run_avl_tree():
    subprocess.run(["gcc", "-o", "build/avl-tree", "avl-tree.c", "utils.c"])
    subprocess.run(["./build/avl-tree"])

def main():
    setup()

    with open('execution_times.csv', 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['Execução', 'Árvore AVL', 'Árvore B'])

        for i in range(10):
            start_time = time.time()
            run_avl_tree()
            avl_tree_time = time.time() - start_time

            start_time = time.time()
            run_b_tree()
            b_tree_time = time.time() - start_time

            writer.writerow([i + 1, avl_tree_time, b_tree_time])

if __name__ == '__main__':
    main()