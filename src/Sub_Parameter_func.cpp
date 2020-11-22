#include"../lib/Parameter_func.h"


double parameter_func(struct PARAMETER* param, struct Parameter* par)
{

    //=============================请勿修改以下参数===========================//
    //**数据保存设置
/*
    param -> acoustic_flag         = 1;  //1表示弹性波、0表示声波压力P
    param->record_save_flag        = 1;  //1表示保存地震剖面，其他数字表示不保存
    param->time_vx_slice_save_flag = 0;  //1表示保存时间切片，其他数字表示不保存
    param->time_vz_slice_save_flag = 1;  //1表示保存时间切片，其他数字表示不保存
    param->time_p_slice_save_flag  = 0;  //1表示保存时间切片，其他数字表示不保存
    param->sdt                     = 100; //时间切片保存间隔
    param->model_save_flag         = 1;  //1表示输出速度模型，其他数字表示不保存
    param->pml_save_flag           = 0;  //1表示保存PML模型,其他数字不保存
    param->wavelet_save_flag       = 0;  //1表示保存子波，其他数字不保存
*/


    param -> acoustic_flag         = par->flag_acoustic_elastic;  //1表示弹性波、0表示声波压力P
    param->record_save_flag        = par->flag_record_save;       //1表示保存地震剖面，其他数字表示不保存
    param->time_vx_slice_save_flag = par->flag_snap_vx_save;      //1表示保存时间切片，其他数字表示不保存
    param->time_vz_slice_save_flag = par->flag_snap_vz_save;      //1表示保存时间切片，其他数字表示不保存
    param->time_p_slice_save_flag  = par->flag_snap_p_save;       //1表示保存时间切片，其他数字表示不保存
    param->sdt                     = par->flag_snap_sdt;          //时间切片保存间隔
    param->model_save_flag         = par->flag_model_save;        //1表示输出速度模型，其他数字表示不保存
    param->pml_save_flag           = 0;                           //1表示保存PML模型,其他数字不保存
    param->wavelet_save_flag       = par->flag_wavelet_save;      //1表示保存子波，其他数字不保存

    //**模型参数
    param -> fn_model_in = par -> fn_path_of_model_in;    //速度模型路径+名称
    param -> fn_data_out = par -> fn_path_of_data_output; //输出文件路径

    param -> PML    = par -> npml;                        //PML边界厚度
    param -> NX     = par -> nx;                          //x方向样点数
    param -> NZ     = par -> nz;                          //z方向样点数
    param -> Nt     = par -> nt;                          //模拟时间样点数
    param -> dx     = par -> dx;                          //x方向取样(m)
    param -> dz     = par -> dz;                          //z方向取样(m)
    param -> dt     = par -> dt;                          //时间取样(s)

    //**观测系统
    param -> fn_ObservationSystem_location = par->fn_path_of_ObservationSystem;
    param->FreeSurface_flag        = par->FreeSurface_flag;  //0表示吸收地表，1表示自由地表（水平）
    param -> Ns     = par -> ns;                             //炮数
    param -> Nr     = par -> nr;                             //检波器数目


    //**并行设计
    param->mpi_ncores = par->n_mpi_cores;         //进程数
    param->omp_ncores = par->n_omp_cores;         //单进程 线程数目

    //计算空间大小
    param -> Nx    = param -> NX+2*param -> PML;  //x方向采样点数(x-z方向各留了PML行用于边界处理)
    param -> Nz    = param -> NZ+2*param -> PML;

    //子波参数设置
    param -> Lw    = param->Nt;                   //子波长度
    param -> freq  = par->wavelet_frequence;      //主频

    //**有限差分系数
    param -> C1      = 1.2340911;
    param -> C2      = -1.0664985e-01;
    param -> C3      = 2.3036367e-02;
    param -> C4      = -5.3423856e-03;
    param -> C5      = 1.0772712e-03;
    param -> C6      = -1.6641888e-04;
    param -> C7      = 1.7021711e-005;
    param -> C8      = -8.5234642e-007;           //差分系数


    //**日志flag
    param->log_flag = 0;                          //1表示写日志，其他数字不写

    //=============================请勿修改以上参数===========================//

    return 0.0;
}
