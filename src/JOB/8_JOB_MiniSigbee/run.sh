set -x

NP=$1

nohup mpirun -np ${NP}  /home/ss/WINDOWS/ELASTIC_WAVE_FD/bin/ELASTIC_WAVE_FD.e  /home/ss/WINDOWS/ELASTIC_WAVE_FD/src/JOB/8_JOB_MiniSigbee/parameter.par > log.txt 2>&1 &

tail -f log.txt
