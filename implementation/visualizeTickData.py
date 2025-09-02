import pandas as pd
import matplotlib.pyplot as plt

id = 1592085374
df = pd.read_csv(f"../build/marketData{id}.csv", header=None, names=["Price"])
plt.figure(figsize=(100, 5))
start = 0
end = 100_000
slice = df["Price"][start:end]
plt.plot(df.index[start:end], slice, linestyle='-', color='blue')

print("Data preview:\n", df.head())
print("Number of rows:", len(df))

plt.title("Stock Price (last traded price)")
plt.ylabel("price")
plt.xlabel("tick")
plt.grid(True)

plt.tight_layout()
plt.show()
