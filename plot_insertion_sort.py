import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

def plot_with_best_fit(csv_file, title, output_image):
    df = pd.read_csv(csv_file)

    x = df["n"].values
    y = df["avg_comparisons"].values

    # Scatter plot
    plt.scatter(x, y)

    # Quadratic best-fit curve
    coeffs = np.polyfit(x, y, 2)
    curve = np.poly1d(coeffs)

    x_curve = np.linspace(min(x), max(x), 200)
    y_curve = curve(x_curve)

    plt.plot(x_curve, y_curve)
    plt.xlabel("n (number of records)")
    plt.ylabel("Average number of comparisons")
    plt.title(title)
    plt.grid(True)
    plt.show()

    plt.savefig(output_image)
    plt.clf()

# Plots
plot_with_best_fit(
    "results_age.csv",
    "Insertion Sort by Age",
    "plot_age.png"
)

plot_with_best_fit(
    "results_name.csv",
    "Insertion Sort by Name",
    "plot_name.png"
)

plot_with_best_fit(
    "results_name_age.csv",
    "Insertion Sort by Name then Age",
    "plot_name_age.png"
)