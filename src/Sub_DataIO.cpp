#include"../lib/IO_func.h"
#include <armadillo>

using namespace arma;

double profile_IO_func(struct PARAMETER *param, float **record)
{
    FILE *fpr;


    std::string fn_csp_out = param->fn_data_out
        + "CSP_ns" + std::to_string(param->Ns)
        + "_nx"+to_string(param->NX)
        + "_nt"+std::to_string(param->Nt)
        +".su";
    const char* fn_csp_out_char = fn_csp_out.data();
    fpr=fopen(fn_csp_out_char,"a+");

    SUHEAD hdr;
    memset(&hdr, 0, 240);//SUHEAD全部置零

    if(param->dsx==0){param->dsx=1;}

    int num_shot=(param->nx_location-param->Sx[0])/param->dsx;
    float * ptr;
    for(int i=0; i<param->Nr; i++)
    {
        hdr.dt     = 1e6*param->dt;
        hdr.ns     = param->Nt;
        hdr.fldr   = param->nx_location-param->PML;
        //hdr.fldr   = param->nx_location-param->PML;
        hdr.tracf  = i+1;
        hdr.sx     = (param->nx_location-param->PML)*param->dx;
        hdr.sy     = 0;
        hdr.gx     = (param->Rx[num_shot][i]-param->PML)*param->dx;
        hdr.gy     = 0;
        hdr.sdepth = (param->Sz[num_shot]-param->PML)*param->dz;
        hdr.selev  = (param->nz_location-param->PML)*param->dz;
        hdr.gelev  = (param->Rz[num_shot][i]-param->PML)*param->dz;
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
