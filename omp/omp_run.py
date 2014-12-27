import os
from subprocess import call
from math import log

script_src=r'''#!/bin/bash
#PBS -q auth
#PBS -N omp
#PBS -j oe
#PBS -l nodes=1:ppn=32
#PBS -l walltime=00:0{1}:00

cd $PBS_O_WORKDIR
export NP=$(cat $PBS_NODEFILE | wc -l)

echo Master process running on `hostname`
echo Directory is `pwd`
echo PBS has allocated the following nodes:
echo `cat $PBS_NBODEFILE`
NPROCS=`wc -l < $PBS_NODEFILE`
echo This job has allocated $NPROCS NPROCS

q={0}
echo Q is $q
./omp.out $q
'''

Q = range(16, 29)
#~ src = r'/mnt/scratchdir/home/orestisf/omp_tests/'
src = r'/tmp/run_test/'
os.chdir(src)

for q in Q:
    final_size = q
    if final_size < 25:
        time = 1
    elif final_size < 26:
        time = 2
    else:
        time = 5
    script = script_src.format(q, time)
    filename = "script{0}.sh".format(q)
    with open(filename, "w") as f:
        f.write(script)
    #~ call("qsub " + filename, shell=True)
    print "qsub " + filename
