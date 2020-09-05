set -x

g++ surface_modeling.cpp -o surface_modeling.exe -larmadillo

./surface_modeling.exe

rm surface_modeling.exe


g++ main.cpp -o  main.exe -larmadillo

./main.exe

rm main.exe
