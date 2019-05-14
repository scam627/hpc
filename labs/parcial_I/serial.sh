#!/bin/bash
#SBATCH --partition=all  	#Seleccione los nodos para el trabajo de todos el conjunto de nodos de cómputo del cluster
#SBATCH -o Serial.%j.out    	#Nombre del archivo de salida
#SBATCH -J Serial	        #Nombre del trabajo

# source /usr/local/intel/parallel_studio_xe_2016.3.067/psxevars.sh intel64 2> /dev/null
# ulimit -s unlimited -c unlimited

N=100000
NSTEPS=1000

for i in `seq  1 10`
do
    for j in `seq 1 5`
    do  
        let n=$N+$i*2000
        echo $n
        ./jacobi1d $n $NSTEPS 1 timing_serial.out >> out_serial.csv
        ./jacobi1d $n $NSTEPS 0 timing_parallel.out >> out_parallel.csv
    done
done

# ./jacobi1d $N $NSTEPS 0 timing_parallel.out
