import pandas as pd
import os

df = pd.read_csv("vgsales.csv")

# All numeric columns in vgsales
numeric_cols = [
    "Rank", "Year",
    "NA_Sales", "EU_Sales", "JP_Sales",
    "Other_Sales", "Global_Sales"
]

# Fill NaN and force correct types
df[numeric_cols] = df[numeric_cols].fillna(0)

df["Rank"] = df["Rank"].astype(int)
df["Year"] = df["Year"].astype(int)

for col in ["NA_Sales", "EU_Sales", "JP_Sales", "Other_Sales", "Global_Sales"]:
    df[col] = df[col].astype(float)

# Output folder
os.makedirs("datasets", exist_ok=True)

for n in range(10, 101, 10):
    for i in range(1, 11):
        sample_df = df.sample(n=n, replace=False, random_state=42 + i)
        sample_df.to_csv(
            f"datasets/R_No_20_P2_IradriDas_data_{n}_{i}.csv",
            index=False
        )

print("CSV datasets generated successfully.")
