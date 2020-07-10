#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main()
{
    int nx=400;
    int nz=600;
    arma::Mat<float> model_ori(nz,nx,fill::zeros);

    arma::Mat<float> model_sur(nz,nx,fill::zeros);

    arma::Col<float> surface(nx,fill::zeros);


    model_ori.load("./model_nz600_nx400.dat",raw_binary);
    model_ori.reshape(nz,nx);

    for (int ix=0; ix<nx ;ix++)
    {
        int flag = 0;

        for(int iz=1; iz<nz; iz++)
        {
            if(flag==0 &&  model_ori(iz,ix)>5*model_ori(iz-1,ix))
            {
                surface(ix)=iz;
                flag = 1;
            }
        }
    }

    float mean = arma::median(surface);

    for(int ix=0; ix<nx ;ix++)
    {
        for(int iz=0; iz<nz;iz++)
        {
            if (iz<surface(ix))
            {
                model_sur(iz,ix)=model_ori(iz,ix);
            }
            else
            {
                //01 : every point
                //model_sur(iz,ix)=model_ori(surface(ix),ix);

                //02 : mean velocity
                //model_sur(iz,ix)=mean;

                //03 : some trick
                if(model_ori(iz,ix)>1000)
                {
                    model_sur(iz,ix) = 1000;
                }
                else
                {
                    model_sur(iz,ix) = model_ori(iz,ix);
                }

            }
        }
    }



    model_sur.save("model_topo.dat",raw_binary);





    return 0;
}
