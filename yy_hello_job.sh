#!/bin/sh -f

#PBS -N yycpitest
#PBS -l nodes=2:ppn=8
#PBS -l walltime=00:01:00
#PBS -l mem=12mb
#PBS -q default

nprocs=`wc -l < $PBS_NODEFILE`
cd $PBS_O_WORKDIR

# 使用以太网传输数据
/usr/mpi/intel/openmpi-1.4.1/bin/mpirun -np $nprocs -machinefile $PBS_NODEFILE \
$PBS_O_WORKDIR/yy_mpi_hello

# Infiniband网传输数据
# /usr/mpi/intel/mvapich-1.2.0/bin/mpirun_rsh -np $nprocs -hostfile $PBS_NODEFILE\
# $PBS_O_WORKDIR/yy_mpi_hello