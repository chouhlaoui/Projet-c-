import matplotlib.pyplot as plt
import numpy as np
import csv

# Charger les données depuis le fichier CSV
def load_data(filename):
    y1, y2, y3 = [], [], []
    with open(filename, newline='') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            y1.append(float(row[0]))
            y2.append(float(row[1]))
            y3.append(float(row[2]))
    return np.arange(len(y1)), np.array(y1), np.array(y2), np.array(y3)

# Tracer les trois fonctions
def plot_functions(x, y1, y2, y3):
    plt.figure(figsize=(10, 6))
    plt.plot(x, y1, label='Nombre d herbe', color='green')
    plt.plot(x, y2, label='Nombre de mouton', color='blue')
    plt.plot(x, y3, label='Nombre de loup', color='red')
    
    plt.xlabel('Indice')
    plt.ylabel('Valeur')
    plt.title('Affichage de trois fonctions')
    plt.legend()
    plt.grid()
    plt.show()

if __name__ == "__main__":
    filename = "Stats50_50_506_253.csv"  # Remplacez par le nom de votre fichier
    x, y1, y2, y3 = load_data(filename)
    plot_functions(x, y1, y2, y3)
