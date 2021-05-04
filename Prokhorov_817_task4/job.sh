#!/bin/bash

#PBS -l walltime=00:01:00,nodes=2:ppn=2
#PBS -N hello
#PBS -q batch

#cd $PBS_O_WORKDIR
#mpirun --hostfile $PBS_NODEFILE -np 4 ./series 100

mpirun -np 7 ./series 40