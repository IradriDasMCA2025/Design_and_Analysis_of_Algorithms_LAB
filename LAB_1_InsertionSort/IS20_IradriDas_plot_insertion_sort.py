import pandas as pd
import matplotlib.pyplot as plt
import os


def plot_comparisons_and_assignments(csv_file, title, output_image):
    """
    Generic plotting function for insertion sort analysis.

    Parameters:
    - csv_file: path to CSV file
    - title: plot title
    - output_image: path to save the plot image
    """

    df = pd.read_csv(csv_file)

    # Extract data
    x = df["n"].values
    y_avg_comp = df["avg_comparisons"].values
    y_avg_assign = df["avg_assignment"].values

    # Create plot
    fig, ax = plt.subplots()

    ax.plot(x, y_avg_comp, marker="o", label="Average Comparisons")
    ax.plot(x, y_avg_assign, marker="s", label="Average Assignments")

    # Labels and title
    ax.set_xlabel("n (number of records)")
    ax.set_ylabel("Operation Count")
    ax.set_title(title)
    ax.grid(True)

    # Legend is REQUIRED when plotting multiple curves
    ax.legend()

    # Save and close
    fig.savefig(output_image)
    plt.close(fig)


# Create output directory safely
os.makedirs("plots", exist_ok=True)

# Comparisons and Assignments plot for InsertionSort_byAge
plot_comparisons_and_assignments(
    "IS20_IradriDas_results_age.csv",
    "Insertion Sort by Age",
    os.path.join("plots", "IS20_IradriDas_plot_avg_comparisons_byAge.png"),
)

# Comparisons and Assignments plot for InsertionSort_byName
plot_comparisons_and_assignments(
    "IS20_IradriDas_results_name.csv",
    "Insertion Sort by Name",
    os.path.join("plots", "IS20_IradriDas_plot_avg_comparisons_byName.png"),
)

# Comparisons and Assignments plot for InsertionSort_byAgeThenName
plot_comparisons_and_assignments(
    "IS20_IradriDas_results_age_name.csv",
    "Insertion Sort by Age then Name",
    os.path.join("plots", "IS20_IradriDas_plot_avg_comparisons_byAgeThenName.png"),
)