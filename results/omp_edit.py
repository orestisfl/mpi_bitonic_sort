from itertools import groupby
import os
import re
from math import log
from numpy import float64

src = r'results'
#~ os.chdir(src)
os.chdir(r'/home/orestis/bak/results/omp_results/')
full_path = os.getcwd()

target = 'omp'
file_names = [i for i in os.listdir() if i.startswith(target)]

patterns = {
    "Q": r"q is (\d{1,})",
    "qsort": r"Quicksort  wall clock time = (\d*[.]?\d+)",
    "ibsort": r"Imperative wall clock time = (\d*[.]?\d+)",
    "omp": r"Parallel\(OMP\) Imperative wall clock time = (\d*[.]?\d+)",
    "rbsort": r"Recursive wall clock time = (\d*[.]?\d+)"
}

handling = {
    "Q": int,
    "qsort": float64,
    "ibsort": float64,
    "omp": float64,
    "rbsort": float64,
}

r = {
    "Q": [],
    "qsort": [],
    "ibsort": [],
    "omp": [],
    "rbsort": [],
}

for file_name in file_names:
    with open(file_name) as file:
        f_str = file.read()
        for name, pattern in patterns.items():
            tmp = re.search(pattern, f_str, flags=re.IGNORECASE)
            if tmp:
                res = tmp.groups()[0]
                value = handling[name](res)
                r[name].append(value)
    
t=sorted(zip(r["Q"], r["qsort"], r["ibsort"], r["omp"], r["rbsort"]))

r["Q"]     = [a for a,b,c,d,e in t]
r["qsort"] = [b for a,b,c,d,e in t]
r["ibsort"] = [c for a,b,c,d,e in t]
r["omp"]   = [d for a,b,c,d,e in t]
r["rbsort"] = [e for a,b,c,d,e in t]

print(r)

import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
t = plt.subplots(nrows=1)
fig = t[0]
ax = t[1]

x = np.array(r["Q"])
xticks = np.array(r["Q"])

qsort = np.array(r["qsort"])
ibsort = np.array(r["ibsort"])/qsort
omp = np.array(r["omp"])/qsort
rbsort= np.array(r["rbsort"])/qsort

ax.plot(x, ibsort, linewidth=2, label="imperative serial bitonic", color="k")
ax.plot(x, omp,    linewidth=2, label="imperative openmp (32 threads) bitonic",    color="b")
ax.plot(x, rbsort, linewidth=2, label="recursive serial bitonic", color="y")

ax.set_title("serial and omp implementations' time divided by qsort time")
ax.grid(aa=True)
ax.set_ylabel("func time / qsort time")
ax.set_xlabel("Q")
ax.xaxis.set_ticks(xticks)
handles, labels = ax.get_legend_handles_labels()
#~ tmp = sorted(zip(labels, handles), key=lambda x: int(x[0]))
#~ labels = [x for x,y in tmp]
#~ handles = [y for x,y in tmp]
[legobj.set_linewidth(5.0) for legobj in ax.legend(handles, labels, loc='upper right').legendHandles]


fig.set_size_inches(20, 20)
fig.savefig('res.png',dpi=100)
