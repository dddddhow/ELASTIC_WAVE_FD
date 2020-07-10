#include"../lib/Parameter_func.h"


double parameter_func(struct PARAMETER* param)
{
    //**模型参数
    param -> PML    = 50+8-8;                  //PML边界厚度
    param -> NX     = 400;                 //x方向样点数
    param -> NZ     = 600;                  //z方向样点数
    param -> Nt     = 6000;                  //模拟时间样点数
    param -> dx     = 5.0;                   //x方向取样
    param -> dz     = 5.0;                   //z方向取样
    param -> dt     = 0.0005;                //时间取样
    //**并行设计
    param->omp_ncores = 20; //单进程 线程数目

    //**数据保存设置
    param -> acoustic_flag         = 1;  //1表示弹性波、0表示声波压力P
    param->record_save_flag        = 1;  //1表示保存地震剖面，其他数字表示不保存
    param->time_vx_slice_save_flag = 0;  //1表示保存时间切片，其他数字表示不保存
    param->time_vz_slice_save_flag = 0;  //1表示保存时间切片，其他数字表示不保存
    param->time_p_slice_save_flag  = 0;  //1表示保存时间切片，其他数字表示不保存
    param->sdt                     = 500; //时间切片保存间隔
    param->model_save_flag         = 1;  //1表示输出速度模型，其他数字表示不保存
    param->pml_save_flag           = 0;  //1表示保存PML模型,其他数字不保存
    param->wavelet_save_flag       = 0;  //1表示保存子波，其他数字不保存

    //计算空间大小
    param -> Nx    = param -> NX+2*param -> PML;//x方向采样点数(x-z方向各留了PML行用于边界处理)
    param -> Nz    = param -> NZ+2*param -> PML;

    //子波参数设置
    param -> Lw    = param->Nt;//子波长度
    param -> freq  = 30;       //主频


    //**有限差分系数
    param -> C1      = 1.2340911;
    param -> C2      = -1.0664985e-01;
    param -> C3      = 2.3036367e-02;
    param -> C4      = -5.3423856e-03;
    param -> C5      = 1.0772712e-03;
    param -> C6      = -1.6641888e-04;
    param -> C7      = 1.7021711e-005;
    param -> C8      = -8.5234642e-007;//差分系数


    //**日志flag
    param->log_flag = 0; //1表示写日志，其他数字不写


    return 0.0;
}
