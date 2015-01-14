import os
from subprocess import call
from math import log

#from: http://it.auth.gr/en/node/1548
script_src=r'''#!/bin/bash
#PBS -q auth
#PBS -N bitonic
#PBS -j oe
#PBS -l nodes={0}:ppn={1}
#PBS -l walltime=00:0{3}:00

cd $PBS_O_WORKDIR
export NP=$(cat $PBS_NODEFILE | wc -l)

echo Master process running on `hostname`
echo Directory is `pwd`
echo PBS has allocated the following nodes:
echo `cat $PBS_NBODEFILE`
NPROCS=`wc -l < $PBS_NODEFILE`
echo This job has allocated $NPROCS nodes

q={2}
echo Q is $q
echo nodes is {0}
echo ppn is {1}
export I2G_MPI_TYPE=mpich2
export I2G_MPI_APPLICATION=bitonic.out
export I2G_MPI_APPLICATION_ARGS=$q
$I2G_MPI_START'''

nodes = [1, 2, 4]
cores = [1,2,4,8,16, 32, 64]
Q = range(16, 21)
src = r'/mnt/scratchdir/home/orestisf/run_tests/'
os.chdir(src)

for n_nodes in nodes:
    for n_cores in cores:
        for q in Q:
            final_size = int(q + log(n_nodes * n_cores, 2))
            if final_size < 25:
                time = 1
            elif final_size < 26:
                time = 2
            else:
                time = 5
            script = script_src.format(n_nodes, n_cores, q, time)
            filename = "script{0}{1}{2}.sh".format(n_nodes, n_cores, q)
            with open(filename, "w") as f:
                f.write(script)
            #~ call("qsub " + filename, shell=True)
            print "qsub " + filename
