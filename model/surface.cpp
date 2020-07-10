#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main()
{

    int sx = 200;
    int nx= 400;
    int offset = 100;


    arma::Col<float> geo_line_all(nx,fill::zeros);
    arma::Col<float> geo_line(offset*2,fill::zeros);

    geo_line_all.load("./surface_all.dat",raw_binary);

for(int ix=0; ix<offset; ix++)
{
    geo_line(ix*2) = ix;
    geo_line(ix*2+1) = geo_line_all(sx-offset/2+ix);
}

    geo_line.save("./surface_singal_ASCII.dat",raw_ascii);


    return 0;
}
