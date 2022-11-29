import pandas as pd
import sys

# fname = './output/q6.csv'
fname = f'./output/q{sys.argv[1]}.csv'
df = pd.read_csv(fname, dtype=str)
col = df.columns
arr = df.to_numpy()

print('\\begin{center}')
print('\\begin{tabular}{|c||c|c|c|c|c|c|}')
print("\\hline")
print(" & ".join(col), "\\\\")
print("\\hline\\hline")
for a in arr:
    print(' & '.join(list(map(str, a))).replace('nan', ''), '\\\\')
print("\\hline")
print('\\end{tabular}')
print('\\end{center}')
