#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main()
{
    int nx=10000;
    int nt=1200;
    arma::Mat<float> sei_ori(nt,nx,fill::zeros);
    arma::Mat<float> sei_linear_noise(nt,nx,fill::zeros);
    sei_ori.load("./model.dat",raw_binary);
    sei_ori.reshape(nt,nx);
    //sei_linear_noise.load("./model_max2000.dat",raw_binary);
    //sei_linear_noise.load("./model_max1500.dat",raw_binary);
    sei_linear_noise.load("./model_max1000.dat",raw_binary);
    sei_linear_noise.reshape(nt,nx);

    arma::Mat<float> op2_result = sei_ori - sei_linear_noise;
    //op2_result.save("./op2_ori_max2000_result.dat",raw_binary);
    //op2_result.save("./op2_ori_max1500_result.dat",raw_binary);
    op2_result.save("./op2_ori_max1000_result.dat",raw_binary);

    return 0;
}

