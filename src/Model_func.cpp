#include "../lib/Model_func.h"


double model_func(struct PARAMETER *param,float **V, float **V_p, float **V_s,
        float **DEN, float **lamda, float **miu)
{

    /********************模型赋值********************/
/*
    param->acoustic_flag=1;
    for(int i=0;i<param->Nx;i++)
    {
        for(int j=0;j<param->Nz;j++)
        {
            V_p[i][j]   = 2000.0;
            DEN[i][j]   = 2400.0;
            miu[i][j]   = 0.0;
            lamda[i][j] = V_p[i][j]*V_p[i][j]*DEN[i][j]-2.0*miu[i][j];
            V_s[i][j]   = sqrt(miu[i][j]*1.0/DEN[i][j]);
            V[i][j]     = sqrt(V_p[i][j]*V_p[i][j]+V_s[i][j]*V_s[i][j]);
            if(miu[i][j]!=0){param->acoustic_flag = 0;}
        }

        for(int j=param->PML+100;j<param->Nz;j++)
        {
            V_p[i][j]   = 2100.0;
            DEN[i][j]   = 2400.0;
            miu[i][j]   = 0.0;
            lamda[i][j] = V_p[i][j]*V_p[i][j]*DEN[i][j]-2.0*miu[i][j];
            V_s[i][j]   = sqrt(miu[i][j]*1.0/DEN[i][j]);
            V[i][j]     = sqrt(V_p[i][j]*V_p[i][j]+V_s[i][j]*V_s[i][j]);
            if(miu[i][j]!=0){param->acoustic_flag = 0;}
        }
        for(int j=param->PML+200;j<param->Nz;j++)
        {
            V_p[i][j]   = 2200.0;
            DEN[i][j]   = 2400.0;
            miu[i][j]   = 0.0;
            lamda[i][j] = V_p[i][j]*V_p[i][j]*DEN[i][j]-2.0*miu[i][j];
            V_s[i][j]   = sqrt(miu[i][j]*1.0/DEN[i][j]);
            V[i][j]     = sqrt(V_p[i][j]*V_p[i][j]+V_s[i][j]*V_s[i][j]);
            if(miu[i][j]!=0){param->acoustic_flag = 0;}
        }
        for(int j=param->PML+350;j<param->Nz;j++)
        {
            V_p[i][j]   = 2500.0;
            DEN[i][j]   = 2400.0;
            miu[i][j]   = 0.0;
            lamda[i][j] = V_p[i][j]*V_p[i][j]*DEN[i][j]-2.0*miu[i][j];
            V_s[i][j]   = sqrt(miu[i][j]*1.0/DEN[i][j]);
            V[i][j]     = sqrt(V_p[i][j]*V_p[i][j]+V_s[i][j]*V_s[i][j]);
            if(miu[i][j]!=0){param->acoustic_flag = 0;}
        }
        for(int j=param->PML+500;j<param->Nz;j++)
        {
            V_p[i][j]   = 3000.0;
            DEN[i][j]   = 2400.0;
            miu[i][j]   = 0.0;
            lamda[i][j] = V_p[i][j]*V_p[i][j]*DEN[i][j]-2.0*miu[i][j];
            V_s[i][j]   = sqrt(miu[i][j]*1.0/DEN[i][j]);
            V[i][j]     = sqrt(V_p[i][j]*V_p[i][j]+V_s[i][j]*V_s[i][j]);
            if(miu[i][j]!=0){param->acoustic_flag = 0;}
        }

    }
*/
    /********************模型加载********************/

    FILE *fpvp;
	int Nx_temp,Nz_temp;

	Nx_temp          = 400;
	Nz_temp          = 600;

	float **V_p_temp = new float*[Nx_temp];
	for(int i = 0; i < Nx_temp; i++)
	V_p_temp[i] = new float[Nz_temp];

    //fpvp=fopen("../model/model_nz600_nx400.dat","rb");
    fpvp=fopen("../model/model_max1500_nz600_nx400.dat","rb");
    for(int i=0; i<Nx_temp; i++)
    {
        fread(V_p_temp[i],sizeof(float),Nz_temp,fpvp);
    }
    fclose(fpvp);


    float **v_p_temp_0 = alloc2float(param->Nz,param->Nx);

    for(int ix=0; ix<param->Nx; ix++)
    {
        for(int iz=0; iz<param->Nz; iz++)
        {
            v_p_temp_0[ix][iz]=2000;
        }
    }
    //for(int ix=param->NX+param->PML; ix<param->Nx; ix++)

    for(int ix=0; ix<param->PML; ix++)
    {
        for(int iz=param->PML; iz<param->Nz-param->PML; iz++)
        {
            v_p_temp_0[ix][iz]=V_p_temp[0][iz-param->PML];
        }
    }
    for(int ix=param->NX+param->PML; ix<param->Nx; ix++)
    {
        for(int iz=param->PML; iz<param->Nz-param->PML; iz++)
        {
            v_p_temp_0[ix][iz]=V_p_temp[param->NX-1][iz-param->PML];
        }
    }
    for(int iz=param->NZ+param->PML; iz<param->Nz; iz++)
    {
        for(int ix=param->PML; ix<param->Nx-param->PML; ix++)
        {
            v_p_temp_0[ix][iz]=V_p_temp[ix-param->PML][param->NZ-1];
        }
    }
    for(int iz=0; iz<param->PML; iz++)
    {
        for(int ix=param->PML; ix<param->Nx-param->PML; ix++)
        {
            v_p_temp_0[ix][iz]=V_p_temp[ix-param->PML][0];
        }
    }
    for(int ix=param->PML; ix<param->PML+param->NX; ix++)
    {
        for(int iz=param->PML; iz<param->NZ+param->PML; iz++)
        {
            v_p_temp_0[ix][iz]=V_p_temp[ix-param->PML][iz-param->PML];
        }
    }


    for (int i=0; i<param->Nx; i++)
    {
        for(int j=0; j<param->Nz; j++)
        {
			V_p[i][j] = v_p_temp_0[i][j];
            DEN[i][j]   = 2400.0;
            miu[i][j]   = 0.0;
            lamda[i][j] = V_p[i][j]*V_p[i][j]*DEN[i][j]-2.0*miu[i][j];
            V_s[i][j]   = sqrt(miu[i][j]*1.0/DEN[i][j]);
            V[i][j]     = sqrt(V_p[i][j]*V_p[i][j]+V_s[i][j]*V_s[i][j]);
        }
    }


    /********************稳定性判断********************/
    stability_func(param, V_p, V_s);

    /********************模型保存********************/
    if(param->model_save_flag == 1)
    {
        FILE *fp;
        if((fp = fopen ("../file/Model.dat", "wb"))!=NULL)
        {
            for (int i=param->PML; i<param->Nx-param->PML; i++)
            {
                for (int j=param->PML; j<param->Nz-param->PML; j++)
                {
                    fwrite (&V_p[i][j] , sizeof(float), 1, fp);
                }
            }
            fclose (fp);
        }
    }
    {
        FILE *fp;
        if((fp = fopen ("../file/Model_all.dat", "wb"))!=NULL)
        {
            for (int i=0; i<param->Nx; i++)
            {
                for (int j=0; j<param->Nz; j++)
                {
                    fwrite (&V_p[i][j] , sizeof(float), 1, fp);
                }
            }
            fclose (fp);
        }
    }
    return 0.0;
    return 0.0;
}
