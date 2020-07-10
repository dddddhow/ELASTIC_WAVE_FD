set -x

gcc vp2vs.c -o vp2vs.e
./vp2vs.e
rm vp2vs.e

icc vp2rho.c -o vp2rho.e
./vp2rho.e
rm vp2rho.e


