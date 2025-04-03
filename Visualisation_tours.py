import matplotlib.pyplot as plt
import numpy as np
import csv

# Charger les données depuis le fichier CSV en utilisant NumPy pour plus d'efficacité
def load_data(filename):
    data = np.genfromtxt(filename, delimiter=',')
    return data[:, 0], data[:, 1], data[:, 2]

# Trouver la taille optimale des cellules
def find_cell_size(x, y):
    dx = np.min(np.diff(np.unique(x))) if len(np.unique(x)) > 1 else 1
    dy = np.min(np.diff(np.unique(y))) if len(np.unique(y)) > 1 else 1
    return dx, dy

# Afficher les données sous forme de quadrillage optimisé
def plot_data(x, y, z):
    dx, dy = find_cell_size(x, y)
    fig, ax = plt.subplots(figsize=(8, 6))
    
    # Création d'une grille
    xi = np.unique(x)
    yi = np.unique(y)
    zi = np.zeros((len(yi), len(xi)))
    zi[:] = np.nan
    
    for i in range(len(x)):
        xi_idx = np.where(xi == x[i])[0][0]
        yi_idx = np.where(yi == y[i])[0][0]
        zi[yi_idx, xi_idx] = z[i]
    
    # Affichage optimisé avec pcolormesh
    mesh = ax.pcolormesh(xi, yi, zi, cmap='gray', shading='auto')
    plt.colorbar(mesh, label='Valeur de Z')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Représentation des points avec quadrillage optimisé')
    
    # Ajouter une info-bulle dynamique
    annotation = ax.annotate("", xy=(0, 0), xytext=(10, 10), textcoords="offset points",
                             bbox=dict(boxstyle="round", fc="w"), visible=False)
    
    def on_hover(event):
        if event.inaxes == ax:
            xi_idx = np.argmin(np.abs(xi - event.xdata))
            yi_idx = np.argmin(np.abs(yi - event.ydata))
            if not np.isnan(zi[yi_idx, xi_idx]):
                annotation.set_text(f'Z: {zi[yi_idx, xi_idx]:.2f}')
                annotation.set_position((event.xdata, event.ydata))
                annotation.set_visible(True)
            else:
                annotation.set_visible(False)
            fig.canvas.draw_idle()
    
    fig.canvas.mpl_connect("motion_notify_event", on_hover)
    
    plt.show()

if __name__ == "__main__":
    filename = "10_10.csv"  # Remplacez par le nom de votre fichier
    x, y, z = load_data(filename)
    plot_data(x, y, z)
