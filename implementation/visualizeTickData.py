import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("../build/Debug/marketData.csv", header=None, names=["Price"])
plt.figure(figsize=(20,10))
plt.plot(df.index, df["Price"], linestyle='-', color='blue')

print("Data preview:\n", df.head())
print("Number of rows:", len(df))

plt.title("Stock Price (last traded price)")
plt.ylabel("price")
plt.xlabel("tick")
plt.grid(True)

plt.tight_layout()
plt.show()