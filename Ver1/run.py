import os
from subprocess import call

script_src=r'''#!/bin/bash
#PBS -q auth
#PBS -N bitonic
#PBS -j oe
#PBS -l nodes={0}:ppn={1}
#PBS -l walltime=00:01:00

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
export I2G_MPI_TYPE=mpich2
export I2G_MPI_APPLICATION=bitonic.out
export I2G_MPI_APPLICATION_ARGS=$q
$I2G_MPI_START'''

nodes = [1, 2, 4]
cores = [1,2,4,8]
Q = range(16, 21)
src = r'/tmp/run_test'
os.chdir(src)

for n_nodes in nodes:
    for n_cores in cores:
        for q in Q:
            script = script_src.format(n_nodes, n_cores, q)
            filename = "script{0}{1}{2}.sh".format(n_nodes, n_cores, q)
            with open(filename, "w") as f:
                f.write(script)
            #~ call("qsub " + filename, shell=True)
            print "qsub " + filename
