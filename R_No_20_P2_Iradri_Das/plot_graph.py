import pandas as pd
import matplotlib.pyplot as plt
import os


def plot_comparisons(csv_file, title, output_image):

    # Read the CSV
    df = pd.read_csv(csv_file)

    # Pull out columns explicitly
    x = df["n"].values
    y_avg_comp = df["avg_comparisons"].values

    # Create plot
    fig, ax = plt.subplots()

    ax.plot(x, y_avg_comp, marker="o", label="Average Comparisons")

    # Labels and title
    ax.set_xlabel("n (number of records)")
    ax.set_ylabel("Operation Count")
    ax.set_title(title)
    ax.grid(True)

    ax.legend()

    # Save and close
    fig.savefig(output_image)
    fig.show()
    plt.close(fig)


# Create output directory safely
os.makedirs("plots", exist_ok=True)


# Comparisons and Assignments plot for Insertion Sort: By Age
plot_comparisons(
    "R_No_20_P1_IradriDas_results_age.csv",
    "Insertion Sort by Age",
    os.path.join("plots", "R_No_20_P1_IradriDas_plot_avg_comparisons_byAge.png"),
)
