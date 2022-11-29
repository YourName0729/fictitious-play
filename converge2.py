import pandas as pd
import sys
import numpy as np
from matplotlib import pyplot as plt, patches

# fname = './output/q6.csv'
fname = f'./output/q{sys.argv[1]}.csv'
df = pd.read_csv(fname, dtype=str)

c1 = list(map(int, df['1\'s action'][1:].tolist()))
c2 = list(map(int, df['2\'s action'][1:].tolist()))

p1 = np.zeros(len(c1))
p2 = np.zeros(len(c2))

p1[0] = c1[0]
p2[0] = c2[0]
for i in range(1, len(c1)):
    p1[i] = (p1[i - 1] * i + c1[i]) / (i + 1)
    p2[i] = (p2[i - 1] * i + c2[i]) / (i + 1)

fig = plt.figure()
ax = fig.add_subplot()
for i in range(len(p1)):
    circle1 = patches.Circle((p1[i], p2[i]), radius=np.power(0.7, i + 1), color='green', alpha=0.2)
    ax.add_patch(circle1)

# circle1 = patches.Circle((0.2, 0.2), radius=0.5, color='green')
# ax.add_patch(circle1)

    # plt.add_artist(plt.Circle((p1[i], p2[i])))

# plt.plot(p1, p2)
plt.xlim([1, 2])
plt.ylim([1, 2])
plt.xlabel('1\'s average action')
plt.ylabel('2\'s average action')
plt.show()

# print(c1, c2)
# print(p1, p2)