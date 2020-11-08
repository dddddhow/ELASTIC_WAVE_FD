//----------------------------------------------------------------------------//
//程序目的： 1、参数卡读写函数
//
//程序原理：
//
//
//程序参数说明：
//
//程序依赖关系说明：
//          1、需要armadillo库
//          2、-std=c++11 或者 更高
//
//Copyright：2020-
//          WPI TONGJI University
//Author  ：ShengShen
//Time    ：2020 08 01
//----------------------------------------------------------------------------//

#include "../lib/Parameter_IO.h"


int readpar_func(const string &fn_par, Parameter &par)
{
    auto Par = &par;
    int LineCount = 0;
    FILE *fp = fopen(fn_par.c_str(), "r");
    if (fp == NULL)
    {
        printf("failed to open %s !!!\n", fn_par.c_str());
        return 0;
    }

    // read a complete line into line[]
    char line[TJU_LENGTH_FILENAME];
    while (1)
    {
        if (NULL == fgets(line, TJU_LENGTH_FILENAME, fp))
        {
            break;
        }
        if (line[0] == '*')
        {
            continue;
        }
        LineCount++;

        //printf("%d-th line=%s\n",LineCount,line); //DEBUG FOR CARDIO
        switch (LineCount)
        {
            case 1:
                sscanf(line, "%s",Par->fn_path_of_model_in_char);
                break;
            case 2:
                sscanf(line, "%s",Par->fn_path_of_ObservationSystem_char);
                break;
            case 3:
                sscanf(line, "%s",Par->fn_path_of_data_output_char);
                break;
            case 4:
                sscanf(line, "%d %d %d",&Par->nx,&Par->nz,&Par->nt);
                break;
            case 5:
                sscanf(line, "%f %f %f",&Par->dx,&Par->dz,&Par->dt);
                break;
            case 6:
                sscanf(line, "%d %d",&Par->ns,&Par->nr);
                break;
            case 7:
                sscanf(line, "%d",&Par->npml);
                break;
            case 8:
                sscanf(line, "%d %d",&Par->n_mpi_cores,&Par->n_omp_cores);
                break;
            case 9:
                sscanf(line, "%f",&Par->wavelet_frequence);
                break;
            case 10:
                sscanf(line, "%d",&Par->flag_snap_sdt);
                break;
            case 11:
                sscanf(line, "%d",&Par->FreeSurface_flag);
                break;
            case 12:
                sscanf(line, "%d",&Par->flag_acoustic_elastic);
                break;
            case 13:
                sscanf(line, "%d %d %d", &Par->flag_record_save, &Par->flag_model_save, &Par->flag_wavelet_save);
                break;
            case 14:
                sscanf(line, "%d %d %d", &Par->flag_snap_vx_save, &Par->flag_snap_vz_save, &Par->flag_snap_p_save);
                break;
            default:
                break;
        }
    }
    Par->fn_path_of_model_in          = Par->fn_path_of_model_in_char;
    Par->fn_path_of_data_output       = Par->fn_path_of_data_output_char;
    Par->fn_path_of_ObservationSystem = Par->fn_path_of_ObservationSystem_char;

    fclose(fp);
    return 0;
}




/*
 * Print Par
 */
int printpar_func(Parameter &par)
{
    auto Par = &par;
    printf("======================================================================\n");
    printf("PrintPar : \n\n");


    printf("* 1  Path of model       : %s \n", Par->fn_path_of_model_in_char);
    printf("* 2  Path of ObsSystem   : %s \n", Par->fn_path_of_ObservationSystem_char);
    printf("* 3  Path of Data Out    : %s \n", Par->fn_path_of_data_output_char);
    printf("\n\n");


    printf("* 4 Parameter Of Model   :\n");
    printf("*                        : (nx,nz,nt) -> (%6d,%6d,%6d)\n", Par->nx, Par->nz,Par->nt);
    printf("*                        : (dx,dz,dt) -> (%6.2fm,%6.2fm,%6.5fs)\n", Par->dx,Par->dz, Par->dt);
    printf("\n\n");

    {
        int nz=int (Par->nz *1.0 / Par->nx *20 *1.0 /2);
        printf("              nx=%6d  dx=%6.2fm\n",Par->nx,Par->dx);
        printf(" -------------------------------------------------- \n");
        for(int iz=0; iz<nz-1; iz++)
        {
            printf("|                                                  |\n");
        }
        printf("|                     Model Show                   | nz=%6d\n",Par->nz);
        printf("|                                                  | dz=%6.2fm\n",Par->dz);
        for(int iz=0; iz<nz-1; iz++)
        {
            printf("|                                                  |\n");
        }
        printf(" -------------------------------------------------- \n");
        printf("\n\n");
    }

    printf("* 5 Parameter Of ObservationSystem :\n");
    printf("*        : (ns,nr)                ->  (%6d,%6d)\n", Par->ns,Par->nr);

    printf("*        : FreeSurface_flag       ->  (%6d)\n",Par->FreeSurface_flag);
    if(Par->FreeSurface_flag == 0)
    {
        printf("           The (Upper)Surface is Absorbing boundary.\n");
    }
    if(Par->FreeSurface_flag == 1)
    {
        printf("           The (Upper)Surface is FreeSurfce.\n");
    }
    printf("\n\n");

    printf("* 6 Parameter Of Data Save :\n");
    printf("*        : flag_record_save   -> (%6d) -> ",Par->flag_record_save);
    if(Par->flag_record_save == 1)
    {
        printf(" [Yes] \n");
    }
    else
    {
        printf(" [No]  \n");
    }

    printf("*        : flag_model_save    -> (%6d) -> ",Par->flag_model_save);
    if(Par->flag_model_save == 1)
    {
        printf(" [Yes] \n");
    }
    else
    {
        printf(" [No]  \n");
    }

    printf("*        : flag_wavelet_save  -> (%6d) -> ",Par->flag_wavelet_save);
    if(Par->flag_wavelet_save == 1)
    {
        printf(" [Yes] \n");
    }
    else
    {
        printf(" [No]  \n");
    }


    printf("*        : flag_snap_vx_save  -> (%6d) -> ",Par->flag_snap_vx_save);
    if(Par->flag_snap_vx_save == 1)
    {
        printf(" [Yes] \n");
    }
    else
    {
        printf(" [No]  \n");
    }

    printf("*        : flag_snap_vz_save  -> (%6d) -> ",Par->flag_snap_vz_save);
    if(Par->flag_snap_vz_save == 1)
    {
        printf(" [Yes] \n");
    }
    else
    {
        printf(" [No]  \n");
    }


    printf("*        : flag_snap_p_save   -> (%6d) -> ",Par->flag_snap_p_save);
    if(Par->flag_snap_p_save == 1)
    {
        printf(" [Yes] \n");
    }
    else
    {
        printf(" [No]  \n");
    }
    printf("*        : flag_snap_sdt      -> (%6d)",Par->flag_snap_sdt);
    printf("\n\n");


    printf("* 7 flag Of forward function :\n");
    printf("*        : flag_of_function   -> (%6d) -> ",Par->flag_acoustic_elastic);
    if(Par->flag_acoustic_elastic == 0)
    {
        printf(" [Acoustic] \n");
    }
    if(Par->flag_acoustic_elastic == 1)
    {
        printf(" [ELASTIC] \n");
    }
    printf("\n");

    printf("* 8 Parameter Of Parallel Computing :\n");
    printf("*        : N_MPI              -> (%6d)\n",Par->n_mpi_cores);
    printf("*        : N_OMP              -> (%6d)\n",Par->n_omp_cores);
    printf("\n");

    printf("======================================================================\n");
    return 0;
}

