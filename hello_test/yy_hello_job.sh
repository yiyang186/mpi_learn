#!/bin/sh -f

#PBS -N yy
#PBS -l nodes=5:ppn=2
#PBS -l walltime=00:01:00
#PBS -l mem=1mb
#PBS -q default

nprocs=`wc -l < $PBS_NODEFILE`
cd $PBS_O_WORKDIR
/usr/mpi/intel/openmpi-1.4.1/bin/mpirun -np $nprocs -machinefile $PBS_NODEFILE $PBS_O_WORKDIR/yy_mpi_hello
