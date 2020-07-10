#include"../lib/IO_func.h"
#include <armadillo>

using namespace arma;

double profile_IO_func(struct PARAMETER *param, float **record)
{
    FILE *fpr;
    int i;

    int nx=param->Nr;
    int nt=param->Nt;
    arma::Mat<float> seis(nt,nx,fill::zeros);
    for(int ix=0; ix<nx; ix++)
    {
        for(int it=0; it<nt; it++)
        {
            seis(it,ix) = record[ix][it];
        }
    }
    //seis.save("../file/record.dat",raw_binary);


    fpr=fopen("../file/record.su","a+");
    //fpr=fopen("/home/ss/data/Amoco_Sim/record.su","a+");
    SUHEAD hdr;
    memset(&hdr, 0, 240);//SUHEAD全部置零

    int num_shot=(param->nx_location-param->Sx[0])/param->dsx;
    float * ptr;

    for(i=0; i<param->Nr; i++)
    {
        hdr.dt     = 1e6*param->dt;
        hdr.ns     = param->Nt;
        hdr.fldr   = param->nx_location-param->PML;
        //hdr.fldr   = param->nx_location-param->PML;
        hdr.tracf  = i+1;
        hdr.sx     = (param->nx_location-param->PML)*param->dx;
        hdr.sy     = (param->nz_location-param->PML)*param->dz;
        hdr.gx     = (param->Rx[num_shot][i]-param->PML)*param->dx;
        hdr.gy     = (param->Rz[num_shot][i]-param->PML)*param->dz;
        hdr.sdepth = (param->Sz[num_shot]-param->PML)*param->dz;
        hdr.selev  = hdr.sy;
        hdr.gelev  = hdr.gy;
        hdr.offset = -(hdr.sx - hdr.gx);
        hdr.cdp    = (hdr.sx + hdr.gx) /2.0f / (param->dx*0.5f);
        //hdr.cdp    = 1;
        ptr = &(record[i][0]);
        fwrite( &hdr,           240,  1, fpr);
        fwrite( ptr , sizeof(float), param->Nt, fpr);
    }
    fclose(fpr);




    return 0.0;
}

double time_slice_IO_func(struct PARAMETER *param,float **time_slice_data, char name[])
{
    FILE *fp;
    if((fp = fopen (name,"a+"))!=NULL)
    {
        for(int i=param->PML; i<param->NX + param->PML; i++)
            for(int j=param->PML; j<param->NZ + param->PML; j++)
            {
                fwrite (&time_slice_data[i][j], sizeof(float), 1, fp);
            }
    }
    fclose(fp);
    return 0.0;
}


double PS_IO_func(struct PARAMETER *param, float **Vx,  float **Vz, int num_shot,int num_r)

{

    float p,s;
    int temp_num_rx=param->Rx[num_shot][num_r];
    int temp_num_rz=param->Rz[num_shot][num_r];

    p=
        (Vx[temp_num_rx+1][temp_num_rz]-Vx[temp_num_rx][temp_num_rz])
        *1.0/param->dx
        +(Vz[temp_num_rx][temp_num_rz+1]-Vz[temp_num_rx][temp_num_rz])
        *1.0/param->dz;

    s=
        (Vx[temp_num_rx][temp_num_rz+1]-Vx[temp_num_rx][temp_num_rz])
        *1.0/param->dz
        +(Vz[temp_num_rx+1][temp_num_rz]-Vz[temp_num_rx][temp_num_rz])
        *1.0/param->dx;

    return p;
}
