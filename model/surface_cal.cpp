#include<iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main()
{
    int nz=600;
    int nx=400;

    arma::Mat<float> model_ori(nz,nx,fill::zeros);
    arma::Mat<float> model_str(nz,nx,fill::zeros);

    model_ori.load("./model.dat",raw_binary);
    model_ori.reshape(nz,nx);

    for(int ix=0; ix<nx; ix++)
    {
        for(int iz=1; iz<nz; iz++)
        {
            if(model_ori(iz,ix)-model_ori(iz-1,ix)>20)
            {
                model_str(iz,ix)=1;
            }
        }
    }
    model_str.save("model_str.dat",raw_binary);




    return 0;
}
