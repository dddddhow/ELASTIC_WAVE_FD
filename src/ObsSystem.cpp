#include "../lib/Parameter_func.h"

using namespace arma;

double obs_func(struct PARAMETER* param)
{

    int nx=param->Nx;
    int nz=param->Nz;
    int npml=param->PML;

    arma::Col<float> sur_location(nx-npml*2);
    arma::Mat<float> surface(nz,nx,fill::zeros);
    sur_location.load("../model/surface_all.dat",raw_binary);
    //sur_location=sur_location/5;


    //炮点&检波点坐标系设置
    param->Ns    = 100;                      //炮数
    param->dsx   = 2;                      //x方向炮间距(point)
    param->dsz   = 0;                      //z方向炮间距(point)

    param->Nr    = 200;                   //检波点数目
    param->drx   = 1;                      //x方向检波器间距(point)
    param->drz   = 0;                      //z方向检波器间距(point)

    param->Sx=alloc1int(param->Ns);
    param->Sz=alloc1int(param->Ns);
    param->Rx=alloc2int(param->Nr,param->Ns);
    param->Rz=alloc2int(param->Nr,param->Ns);

    for(int ix=0; ix<param->Ns; ix++)
    {
        int sx=100+ix*param->dsx;
        param->Sx[ix]=sx+npml;
        param->Sz[ix]=sur_location(param->Sx[ix]-npml)+npml;
    }

    for(int ix=0; ix<param->Ns; ix++)
    {
        for(int ir=0; ir<param->Nr; ir++)
        {
            param->Rx[ix][ir]=param->Sx[ix]-param->Nr/2+ir;
            param->Rz[ix][ir]=sur_location(param->Rx[ix][ir]-npml)+npml;
            //printf("[%d],[%d]\n",param->Rx[0][ix],param->Rz[0][ix]);
        }
    }

    //VSP

    //for(int ix=0; ix<param->Nr; ix++)
    //{
    //param->Rx[0][ix]=param->Sx[0];
    //param->Rz[0][ix]=sur_location(param->Rx[0][ix]-npml)+npml+ix;
    //}









    //for (int i = 0; i<param->Ns; i++)
    //{
    //param->Sx[i] = param->PML +5000+ i*param->dsx; //炮点坐标Sx
    //param->Sz[i] = param->PML + i*param->dsz; //炮点坐标Sz
    //for (int j = 0; j<param->Nr; j++)
    //{
    //param->Rx[i][j] = param->Sx[i] + (j-floor(param->Nr/2))*param->drx; //每一炮对应的检波点坐标Rx
    //param->Rz[i][j] = param->Sz[i] + j*param->drz;//每一炮对应的检波点坐标Rz
    //}
    //}













    return 0;
}
