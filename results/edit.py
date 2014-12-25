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
    "asc_comp": r"Ascending sort TEST (.{4})ed",
    "qsort_comp": r"qsort vs bsort (.{4})ED",
    "btime": r"Total time of Parallel Bitonic Sort = (\d*[.]?\d+)",
    "qtime": r"Serial Quicksort Time = (\d*[.]?\d+)"
}

results = {
    "Q": [],
    "nodes": [],
    "ppn": [],
    "comm_size": [],
    "asc_comp": [],
    "qsort_comp": [],
    "btime": [],
    "qtime": [],
}

handling = {
    "Q": int,
    "nodes": int,
    "ppn": int,
    "comm_size": int,
    "asc_comp": lambda x: x.lower()=="pass",
    "qsort_comp": lambda x: x.lower()=="pass",
    "btime": float64,
    "qtime": float64,
}

for file_name in file_names:
    with open(file_name) as file:
        f_str = file.read()
        for name, pattern in patterns.items():
            res = re.search(pattern, f_str, flags=re.IGNORECASE).groups()[0]
            value = handling[name](res)
            results[name].append(value)

if not all(results["asc_comp"]):
    print("WARNING: fail detected at asc_comp! check it out")
del results["asc_comp"]
    
if not all(results["qsort_comp"]):
    print("WARNING: fail detected at qsort_comp! check it out")
del results["qsort_comp"]

#~ print(results)


for bsort, qsort in zip(results["btime"], results["qtime"]):
    end = (qsort<bsort) * " <----qsort faster" + "\n"
    diff = (bsort-qsort)/qsort*100
    print(("%0.2f"%bsort).zfill(5), ("%0.2f"%qsort).zfill(5), ("%0.2f"%diff).zfill(5) + "%", end=end)

