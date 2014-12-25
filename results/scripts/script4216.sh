#!/bin/bash
#PBS -q auth
#PBS -N bitonic
#PBS -j oe
#PBS -l nodes=4:ppn=2
#PBS -l walltime=00:01:00

cd $PBS_O_WORKDIR
export NP=$(cat $PBS_NODEFILE | wc -l)

echo Master process running on `hostname`
echo Directory is `pwd`
echo PBS has allocated the following nodes:
echo `cat $PBS_NBODEFILE`
NPROCS=`wc -l < $PBS_NODEFILE`
echo This job has allocated $NPROCS nodes

q=16
echo Q is $q
echo nodes is 4
echo ppn is 2
export I2G_MPI_TYPE=mpich2
export I2G_MPI_APPLICATION=bitonic.out
export I2G_MPI_APPLICATION_ARGS=$q
$I2G_MPI_START