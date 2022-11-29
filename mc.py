import pandas as pd
import sys
import numpy as np
from matplotlib import pyplot as plt, patches

# fname = './output/q6.csv'
def foo(x):
    fname = f'./output/mc{x}.csv'
    df = pd.read_csv(fname, dtype=str)

    c1 = list(map(int, df['1\'s action'][1:].tolist()))
    c2 = list(map(int, df['2\'s action'][1:].tolist()))

    return np.average(c1), np.average(c2)


fig = plt.figure()
ax = fig.add_subplot()
    
for i in range(1, 501):
    x, y = foo(i)
    # print(foo(i))
    circle1 = patches.Circle((x, y), radius=np.random.exponential(0.05), color='green', alpha=0.1)
    ax.add_patch(circle1)

plt.xlim([1, 2])
plt.ylim([1, 2])
plt.xlabel('1\'s average action in 500 tests')
plt.ylabel('2\'s average action in 500 tests')
plt.show()