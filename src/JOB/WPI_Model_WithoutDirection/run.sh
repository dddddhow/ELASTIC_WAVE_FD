set -x

nohup ./../../../bin/ELASTIC_WAVE_FD.e  /home/ss/WINDOWS/ELASTIC_WAVE_FD/src/JOB/WPI_Model_WithoutDirection/parameter.par >& 1.log&

tail -f 1.log
