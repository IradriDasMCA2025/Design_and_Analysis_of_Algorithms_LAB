import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

import os


def plot_avg_assignments(csv_file, title, output_image):
    df = pd.read_csv(csv_file)  # Reads the CSV file into a Pandas DataFrame.

    # extracting x and y axis
    x = df["n"].values
    y = df["avg_assignment"].values

    fig, ax = plt.subplots()
    ax.plot(x, y, marker="o")


    ax.set_title(title)
    ax.set_xlabel("n (number of records)")
    ax.set_ylabel("Average number of assignments")
    ax.grid(True)

    # plt.show()
    fig.savefig(output_image)


def plot_avg_comparisions(csv_file, title, output_image):
    df = pd.read_csv(csv_file)  # Reads the CSV file into a Pandas DataFrame.

    # extracting x and y axis
    x = df["n"].values
    y = df["avg_comparisons"].values

    fig, ax = plt.subplots()
    ax.plot(x, y, marker="o")


    ax.set_title(title)
    ax.set_xlabel("n (number of records)")
    ax.set_ylabel("Average number of comparisons")
    ax.grid(True)

    # plt.show()
    fig.savefig(output_image)

    # fig, ax = plt.plot(x,y)
    # # ax.plot(x, y)
    # ax.scatter(x, y)
    # ax.xlabel("n (number of records)")
    # ax.ylabel("Average number of comparisons")
    # ax.title(title)

    # fig.show()
    # print(df)

    # plt.plot(x, y)
    # plt.scatter(x, y)
    # plt.xlabel("n (number of records)")
    # plt.ylabel("Average number of comparisons")
    # plt.title(title)
    # plt.grid(True)
    # plt.show()

    # plt.savefig(output_image)
    # plt.clf()


os.makedirs("plots")

# Plots for avg_comparisions
plot_avg_comparisions(
    "IS20_IradriDas_results_age.csv",
    "Insertion Sort by Age(plot for averege comparisions)",
    "plots\\IS20_IradriDas_plot_avg_comparisions_byAge.png",
)
plot_avg_comparisions(
    "IS20_IradriDas_results_name.csv",
    "Insertion Sort by Name(plot for averege comparisions)",
    "plots\\IS20_IradriDas_plot_avg_comparisions_byName.png",
)
plot_avg_comparisions(
    "IS20_IradriDas_results_age_name.csv",
    "Insertion Sort by Age then Name(plot for averege comparisions)",
    "plots\\IS20_IradriDas_plot_avg_comparisions_byAgeThenName.png",
)

# Plots for avg_assignments
plot_avg_assignments(
    "IS20_IradriDas_results_age.csv",
    "Insertion Sort by Age(plot for averege assignments)",
    "plots\\IS20_IradriDas_plot_avg_assignments_byAge.png",
)
plot_avg_assignments(
    "IS20_IradriDas_results_name.csv",
    "Insertion Sort by Name(plot for averege assignments)",
    "plots\\IS20_IradriDas_plot_avg_assignments_byName.png",
)
plot_avg_assignments(
    "IS20_IradriDas_results_age_name.csv",
    "Insertion Sort by Age then Name(plot for averege assignments)",
    "plots\\IS20_IradriDas_plot_avg_assignments_byAgeThenName.png",
)


# df = pd.read_csv("results_age.csv")
# # print(df)

# x = df["n"].values
# print(x)
# y = df["avg_comparisons"].values
# print(y)

# plt.plot(x, y)
# plt.scatter(x, y)
# plt.xlabel("n (number of records)")
# plt.ylabel("Average number of comparisons")
# plt.title("Insertion Sort by Age")
# plt.grid(True)
# plt.show()

# plt.savefig("plot_age.png")
# plt.clf()
