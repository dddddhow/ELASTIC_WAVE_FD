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
        if (LineCount > TJU_NLINE_PAR)
        {
            break;
        }
        switch (LineCount)
        {
            case 1:
                sscanf(line, "%s", Par->fn_path_of_model_in_char);
                break;
            case 2:
                sscanf(line, "%s", Par->fn_path_of_ObservationSystem_char);
                break;
            case 3:
                sscanf(line, "%s", Par->fn_path_of_data_output_char);
                break;
            case 4:
                sscanf(line, "%d  %d %d", &Par->nx, &Par->nz, &Par->nt);
                break;
            case 5:
                sscanf(line, "%f %f %f", &Par->dx, &Par->dz, &Par->dt);
                break;
            case 6:
                sscanf(line, "%d %d %d %d %d", &Par->ns, &Par->sx_first, &Par->sz_first, &Par->dsx, &Par->dsz);
                break;
            case 7:
                sscanf(line, "%d %d %d %d %d", &Par->nr, &Par->rx_first, &Par->rz_first, &Par->drx, &Par->drz);
                break;
            case 8:
                sscanf(line, "%d", &Par->npml);
                break;
            case 9:
                sscanf(line, "%d", &Par->n_omp_cores);
                break;
            case 10:
                sscanf(line, "%f", &Par->wavelet_frequence);
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
    printf("\n");

    printf("              nx=%6d  dx=%6.2fm\n",Par->nx,Par->dx);
    printf(" --------------------------------------------- \n");
    printf("|                                             |\n");
    printf("|                                             |\n");
    printf("|                  Model Show                 | nz=%6d\n",Par->nz);
    printf("|                                             | dz=%6.2fm\n",Par->dz);
    printf("|                                             |\n");
    printf("|                                             |\n");
    printf(" -------------------------------------------- \n");
    printf("\n\n");


    printf("* 5 Parameter Of ObservationSystem :\n");
    printf("*                        : (nx)                ->  %6d\n", Par->ns);
    printf("*                        : (sx_first,sz_first) -> (%6d,%6d) point\n", Par->sx_first,Par->sz_first);
    printf("*                        : (dsx,dsz)           -> (%6d,%6d) point\n", Par->dsx,Par->dsz);
    printf("*                        : (nr)                ->  %6d\n", Par->nr);
    printf("*                        : (rx_first,rz_first) -> (%6d,%6d) point\n", Par->rx_first,Par->rz_first);
    printf("*                        : (drx,drz)           -> (%6d,%6d) point\n", Par->drx,Par->drz);
    printf("\n\n");


    printf("======================================================================\n");
    return 0;
}

