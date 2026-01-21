import pandas as pd
import matplotlib.pyplot as plt
import os


def plot_comparisons_and_assignments(csv_file, title, output_image):

    # Read the CSV
    df = pd.read_csv(csv_file)

    # Pull out columns explicitly
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

    ax.legend()

    # Save and close
    fig.savefig(output_image)
    plt.close(fig)


# Create output directory safely
os.makedirs("plots", exist_ok=True)


# Comparisons and Assignments plot for Insertion Sort: By Age
plot_comparisons_and_assignments(
    "R_No_20_P1_IradriDas_results_age.csv",
    "Insertion Sort by Age",
    os.path.join("plots", "R_No_20_P1_IradriDas_plot_avg_comparisons_byAge.png"),
)


# Comparisons and Assignments plot for Insertion Sort: By Name
plot_comparisons_and_assignments(
    "R_No_20_P1_IradriDas_results_name.csv",
    "Insertion Sort by Name",
    os.path.join("plots", "R_No_20_P1_IradriDas_plot_avg_comparisons_byName.png"),
)

# Comparisons and Assignments plot for Insertion Sort: By Age then Name
plot_comparisons_and_assignments(
    "R_No_20_P1_IradriDas_results_age_name.csv",
    "Insertion Sort by Age then Name",
    os.path.join("plots", "R_No_20_P1_IradriDas_plot_avg_comparisons_byAgeThenName.png"),
)