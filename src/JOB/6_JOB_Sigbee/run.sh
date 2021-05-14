set -x

NP=$1

nohup mpirun -np ${NP}  /home/ss/WINDOWS/ELASTIC_WAVE_FD/bin/ELASTIC_WAVE_FD.e  /home/ss/WINDOWS/ELASTIC_WAVE_FD/src/JOB/6_JOB_Sigbee/parameter.par > log.txt 2>&1 &

tail -f log.txt
