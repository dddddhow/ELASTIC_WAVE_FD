#include "../lib/Model_func.h"

void model_expand_func(float **m_in, float **m_out, int npml, int nx, int nz);

double model_func(struct PARAMETER *param,float **V, float **V_p, float **V_s,
        float **DEN, float **lamda, float **miu)
{

    /********************模型加载********************/

    FILE *fpvp;
    int Nx_temp,Nz_temp;

    Nx_temp          = param->NX;
    Nz_temp          = param->NZ;

    float **V_p_temp = new float*[Nx_temp];
    for(int i = 0; i < Nx_temp; i++)
        V_p_temp[i] = new float[Nz_temp];

    std::string fn_model_in = param->fn_model_in;
    const char* fn_model_in_char = fn_model_in.data();
    fpvp=fopen(fn_model_in_char,"rb");

    for(int i=0; i<Nx_temp; i++)
    {
        fread(V_p_temp[i],sizeof(float),Nz_temp,fpvp);
    }
    fclose(fpvp);

    float **v_p_temp_0 = alloc2float(param->Nz,param->Nx);

    //PML范围速度填充
    model_expand_func(V_p_temp, v_p_temp_0, param->PML, param->Nx, param->Nz);

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
        string fn_model_out = param->fn_data_out + "Model.dat";
        const char* fn_model_out_char = fn_model_out.data();
        FILE *fp;
        if((fp = fopen (fn_model_out_char, "wb"))!=NULL)
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
    return 0.0;
}


void model_expand_func(float **m_in, float **m_out, int npml, int nx, int nz)
{
    //Down
    for(int iz=nz-npml; iz<nz; iz++)
    {
        for(int ix=npml; ix<nx-npml; ix++)
        {
            m_out[ix][iz]=m_in[ix-npml][nz-npml-npml-1];
        }
    }
    //Up
    for(int iz=0; iz<npml; iz++)
    {
        for(int ix=npml; ix<nx-npml; ix++)
        {
            m_out[ix][iz]=m_in[ix-npml][0];
        }
    }

    //Center
    for(int ix=npml; ix<nx-npml; ix++)
    {
        for(int iz=npml; iz<nz-npml; iz++)
        {
            m_out[ix][iz]=m_in[ix-npml][iz-npml];
        }
    }

    //Left
    for(int ix=0; ix<npml; ix++)
    {
        for(int iz=0; iz<nz; iz++)
        {
            m_out[ix][iz]=m_out[npml][iz];
        }
    }
    //Right
    for(int ix=nx-npml; ix<nx; ix++)
    {
        for(int iz=0; iz<nz; iz++)
        {
            m_out[ix][iz]=m_out[npml][iz];
        }
    }

}
