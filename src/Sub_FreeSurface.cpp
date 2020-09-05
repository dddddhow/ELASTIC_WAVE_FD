#include "../lib/Free_Surface_Func.h"

using namespace arma;
using namespace std;



//---------------------------内部子函数定义-----------------------------------//
double h_func(float **Txx_now, float **Txz_now,float **Tzz_now,
					struct PARAMETER *param);
double vl_func(float **Txx_now, float **Txz_now,float **Tzz_now,
					struct PARAMETER *param);
double il_func(float **Txx_now, float **Txz_now,float **Tzz_now,
					struct PARAMETER *param);
double ol_func(float **Txx_now, float **Txz_now,float **Tzz_now,
					struct PARAMETER *param);
double vr_func(float **Txx_now, float **Txz_now,float **Tzz_now,
					struct PARAMETER *param);
double ir_func(float **Txx_now, float **Txz_now,float **Tzz_now,
					struct PARAMETER *param);
double or_func(float **Txx_now, float **Txz_now,float **Tzz_now,
					struct PARAMETER *param);
//----------------------------------------------------------------------------//



double free_surface_func(float **V,
                         float **Txx_now, float **Txz_now,float **Tzz_now,
					     struct PARAMETER *param)
{

    int nx=param->NX;
    int nz=param->NZ;
    int npml=param->PML;

    arma::Col<float> surface(nx,fill::zeros);
    std::string fn_surface = param->fn_ObservationSystem_location;
    surface.load(fn_surface,raw_binary);

    for(int ix=0; ix<nx-1; ix++)
    {
        int nz_temp    = surface(ix);
        int diff_sur = surface(ix+1)-surface(ix);
        //float diff_vel = V[ix+npml+1][nz_temp]-V[ix+npml][nz_temp];

        //水平边界点H
        if(diff_sur==0)
        {
            //h_func(Txx_now, Txz_now,Tzz_now, param);
            int iz_temp=surface(ix);
            Txz_now[ix][iz_temp]=0;
            //Txz_now[ix][iz_temp-1]=-Txz_now[ix][iz_temp+1];
            //Txz_now[ix][iz_temp-2]=-Txz_now[ix][iz_temp+2];
            //Txz_now[ix][iz_temp-3]=-Txz_now[ix][iz_temp+3];

            //Txz_now[ix][iz_temp]=0;
            //Tzz_now[ix][iz_temp-1]=Tzz_now[ix][iz_temp+1];
            //Tzz_now[ix][iz_temp-2]=Tzz_now[ix][iz_temp+2];
            //Tzz_now[ix][iz_temp-3]=Tzz_now[ix][iz_temp+3];

        }

        //左垂直边界点VL
        if(diff_sur>1)
        {
            int nz_sur=diff_sur;
            for(int iz=0; iz<nz_sur; iz++)
            {
                float diff_vel = V[ix+npml+1][iz]-V[ix+npml][iz];
            }
        }


        //左内部边界点IL

        //左外部边界点OL

        //右垂向边界点VR

        //右内部边界点IR

        //右外部边界点OR

    }


    return 0;
}



double h_func(float **Txx_now, float **Txz_now,float **Tzz_now,
        struct PARAMETER *param)
{
    return 0;
}

