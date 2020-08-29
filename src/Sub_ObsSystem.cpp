#include "../lib/Parameter_func.h"

using namespace arma;

double obs_func(struct PARAMETER* param)
{
    printf("//-----------------------------------------------------//\n");
    printf("Setting Up The Obssystem Begin\n");

    //炮点&检波点坐标系设置
    int nx       = param->NX;
    int nz       = param->NZ;
    int npml     = param->PML;

    int ns       = param->Ns;                     //炮数
    int sx_first = param->sx_first;               //起始炮位置 横坐标
    //int sz_first = param->sz_first;               //起始炮位置 纵坐标
    int dsx      = param->dsx;                    //横向炮间距
    //int dsz      = param->dsz;                    //纵向炮间距

    int nr       = param->Nr;                     //检波器数目
    int rx_first = param->rx_first;               //第一检波器位置 横坐标
    int rz_first = param->rz_first;               //第一检波器位置 纵坐标
    int drx      = param->drx;                    //横向检波器间距
    int drz      = param->drz;                    //纵向检波器间距


    arma::Col<float> sur_location(nx);
    std::string fn_ObservationSystem_location = param->fn_ObservationSystem_location;
    sur_location.load(fn_ObservationSystem_location,raw_binary);

    param->Sx=alloc1int(ns);
    param->Sz=alloc1int(ns);
    param->Rx=alloc2int(nr,ns);
    param->Rz=alloc2int(nr,ns);



    for(int ix=0; ix<ns; ix++)
    {
        param->Sx[ix]=sx_first+ix*dsx+npml;
        param->Sz[ix]=sur_location(param->Sx[ix]-npml)+npml;
        //cout<<sx_first<<endl;
        //cout<<param->Sx[ix] << "  "<<param->Sz[ix]<<endl;
    }
    /*
       for(int is=0; is<ns; is++)
       {
       for(int ir=0; ir<nr; ir++)
       {
       param->Rx[is][ir]=ir+npml;
       param->Rz[is][ir]=300;
       }
       }
       */
    if(param->ObservationSystem_flag == 0) // 地表接收
    {
        for(int ix=0; ix<ns; ix++)
        {
            for(int ir=0; ir<nr; ir++)
            {
                param->Rx[ix][ir]=rx_first+drx*ir+npml;
                param->Rz[ix][ir]=sur_location(param->Rx[ix][ir]-npml)+npml;
                //param->Rz[ix][ir]=rz_first+drz*ir+npml;
            }
        }
    }

    if(param->ObservationSystem_flag == 1) // 三边接受
    {
        if(nr != nx+nz*2-2)
        {
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<"ERROR!!! (The Parameters of Observation(nr) )"<<endl;
            cout<<nr<<" != "<<nx+nz+nz-2<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
        }
        else{
            for(int ix=0; ix<ns; ix++)
            {
                for(int ir=0; ir<=nz-1; ir++)
                {
                    param->Rx[ix][ir]=npml;
                    param->Rz[ix][ir]=npml+(nz-ir);
                }
                for(int ir=nz; ir<=nz+nx-3; ir++)
                {
                    param->Rx[ix][ir]=npml+(ir-nz+1);
                    param->Rz[ix][ir]=npml;
                }
                for(int ir=nz+nx-2; ir<=nz+nz+nx-3; ir++)
                {
                    param->Rx[ix][ir]=npml+nx;
                    param->Rz[ix][ir]=npml+(ir-nz-nx+2);
                }
            }
        }
    }


    if(param->ObservationSystem_flag == 2) // 四周接收
    {
        if(nr != nx*2+nz*2-4)
        {
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<"ERROR!!! (The Parameters of Observation(nr) )"<<endl;
            cout<<nr<<" != "<<nx*2+nz+nz-4<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
        }
        else{
            for(int ix=0; ix<ns; ix++)
            {
                for(int ir=0; ir<=nz-1; ir++)
                {
                    param->Rx[ix][ir]=npml;
                    param->Rz[ix][ir]=npml+(nz-ir);
                }
                for(int ir=nz; ir<=nz+nx-3; ir++)
                {
                    param->Rx[ix][ir]=npml+(ir-nz+1);
                    param->Rz[ix][ir]=npml;
                }
                for(int ir=nz+nx-2; ir<=nz+nz+nx-3; ir++)
                {
                    param->Rx[ix][ir]=npml+nx;
                    param->Rz[ix][ir]=npml+(ir-nz-nx+2);
                }
                for(int ir=nz+nx+nz-2; ir<=nz+nz+nx+nx-4; ir++)
                {
                    param->Rx[ix][ir]=npml+(ir-nz-nx-nz+2)+1;
                    param->Rz[ix][ir]=npml+nz;
                }
            }
        }
    }



    printf("Setting Up The Obssystem Finish\n");
    printf("//-----------------------------------------------------//\n");
    return 0;
}
