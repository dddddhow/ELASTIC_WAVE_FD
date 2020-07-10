#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main()
{
    int nx_ori=10001;
    int nz_ori=1200;
    int nx_new=400;
    int nz_new=600;

    arma::Mat<float> model_ori(nz_ori,nx_ori,fill::zeros);
    arma::Mat<float> model_new(nz_new,nx_new,fill::zeros);

    model_ori.load("./model_max2000.dat",raw_binary);
    model_ori.reshape(nz_ori,nx_ori);

    int nx_beg=5600;
    int nx_end=5999;
    int nz_beg=0;
    int nz_end=599;
    model_new=model_ori(span(nz_beg,nz_end),span(nx_beg,nx_end));

    model_new.save("./model_max2000_nz600_nx400.dat",raw_binary);

    return 0;
}
