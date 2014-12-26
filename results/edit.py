from itertools import groupby
import os
import re
from math import log
from numpy import float64

src = r'results'
os.chdir(src)
full_path = os.getcwd()

target = 'bitonic'
file_names = [i for i in os.listdir() if i.startswith(target)]

patterns = {
    "Q": r"q is (\d{1,})",
    "nodes": r"nodes is (\d{1,})",
    "ppn": r"ppn is (\d{1,})",
    "comm_size": r"MPI says that comm_size is (\d{1,})",
    #~ "comm_size": r"mpi says comm size is (\d{1,})",
    "asc_comp": r"Ascending sort TEST (.{4})ed",
    "qsort_comp": r"qsort vs bsort (.{4})ED",
    "bsort": r"Total time of Parallel Bitonic Sort = (\d*[.]?\d+)",
    "qsort": r"Serial Quicksort Time = (\d*[.]?\d+)"
}

results=[]

handling = {
    "Q": int,
    "nodes": int,
    "ppn": int,
    "comm_size": int,
    "asc_comp": lambda x: x.lower()=="pass",
    "qsort_comp": lambda x: x.lower()=="pass",
    "bsort": float64,
    "qsort": float64,
}

for file_name in file_names:
    results.append({})
    with open(file_name) as file:
        f_str = file.read()
        for name, pattern in patterns.items():
            res = re.search(pattern, f_str, flags=re.IGNORECASE).groups()[0]
            value = handling[name](res)
            results[-1][name] = value


for idx, x in enumerate(results):
    if not x["asc_comp"]:
        print("ERROR: fail detected at asc_comp! check it out %d" % idx)
        exit()
    if not x["qsort_comp"]:
        print("ERROR: fail detected at qsort_comp! check it out %d" % idx)
        exit()
    if not x["nodes"] * x["ppn"] == x["comm_size"]:
        print("ERROR: not n*p==comm at %d" % idx)
        exit()
    del x["asc_comp"], x["qsort_comp"], x["comm_size"]
    

#~ import json
#~ with open("temp.json", "w") as f:
    #~ json.dump(results,f)

#~ print(results)


#~ for x in results:
    #~ end = (x["qsort"]<x["bsort"]) * " <----qsort faster" + "\n"
    #~ diff = (x["bsort"]-x["qsort"])/x["qsort"]*100
    #~ print(x["Q"],":", ("%0.2f"%x["bsort"]).zfill(5), ("%0.2f"%x["qsort"]).zfill(5), ("%0.2f"%diff).zfill(5) + "%", end=end)


per_node = {}
results.sort(key=lambda x: x["nodes"])
for nodes, value in groupby(results, lambda x: x["nodes"]):
    per_node[nodes] = list(value)
#~ print(per_node)

import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
t = plt.subplots(nrows=3)
fig = t[0]
axes = t[1]

x = np.array(range(16,21))
xticks = np.arange(min(x), max(x) + 1, 1)

colors = ["#727272",  "#f1595f", "#79c36a", "#599ad3", "#f9a65a","#9e66ab"]
for ax, nodes, value in zip(axes, per_node.keys(), per_node.values()):
    #~ if nodes==4:
        #~ break
    print("%d nodes:"%nodes)
    value.sort(key=lambda x: x["Q"])
    per_q = groupby(value, lambda x: x["Q"])
    ppn = {1:[], 2:[], 4:[], 8:[], 16:[], 32:[]}
    
    for Q, l in per_q:
        for element in list(l):
            ppn[element["ppn"]].append(element["bsort"]/element["qsort"])
    sub_plot = 0
    m=0
    for n, y in ppn.items():
        if len(x) != len(y):
            print(n)
            continue
        ax.plot(x, y, color=colors[sub_plot], linewidth=2, label=str(n))
        if max(y) > m:
            m=max(y)
        sub_plot+=1
    ax.set_ylim(ymin=0, ymax=m*1.13)
    ax.set_title("%d node%s:"%(nodes, 's'*(nodes>1)))
    ax.grid(aa=True)
    ax.set_ylabel("bsort time / qsort time")
    ax.set_xlabel("Q")
    ax.xaxis.set_ticks(xticks)
    handles, labels = ax.get_legend_handles_labels()
    tmp = sorted(zip(labels, handles), key=lambda x: int(x[0]))
    labels = [x for x,y in tmp]
    handles = [y for x,y in tmp]
    [legobj.set_linewidth(5.0) for legobj in ax.legend(handles, labels, loc='upper right').legendHandles]
    


fig.set_size_inches(20, 20)
fig.savefig('../res.png',dpi=100)

extent = axes[0].get_window_extent().transformed(fig.dpi_scale_trans.inverted())
fig.savefig('0.png', bbox_inches=extent.expanded(1.1, 1.2))
extent = axes[1].get_window_extent().transformed(fig.dpi_scale_trans.inverted())
fig.savefig('1.png', bbox_inches=extent.expanded(1.1, 1.2))
extent = axes[2].get_window_extent().transformed(fig.dpi_scale_trans.inverted())
fig.savefig('2.png', bbox_inches=extent.expanded(1.1, 1.2))
