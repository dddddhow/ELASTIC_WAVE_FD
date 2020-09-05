#pragma once

#include <iostream>

using namespace std;

struct PARAMETER{

    //**模型参数
    std::string fn_model_in;
    int NX;//x方向样点数
    int NZ;//z方向样点数
    int PML;//PML边界厚度
    int Nt;//模拟时间样点数
    float dx;//x方向取样
    float dz;//z方向取样
    float dt;//时间取样
    float V_pmax;//最大纵波速度

    //**各向异性参数**Thomson表征形式
    float epsilon;
    float delt;
    float yita;

    //**有限差分系数
    float C1;
    float C2;
    float C3;
    float C4;
    float C5;
    float C6;
    float C7;
    float C8;//差分系数

    //计算空间大小
    int Nx;//x方向采样点数(x-z方向各留了PML行用于边界处理)
    int Nz;

    //子波参数设置
    int Lw;   //子波长度
    float freq; //主频

    //**观测系统
    std::string fn_ObservationSystem_location;
    int nx_location;
    int nz_location;
    int nshot_count;
    //炮点
    int Ns;//炮数
    int dsx;
    int dsz;
    int sx_first;
    int sz_first;
    int *Sx;
    int *Sz;
    //检波点
    int Nr;
    int drx;
    int drz;
    int rx_first;
    int rz_first;
    int **Rx;
    int **Rz;


    //**输出参数
    std:: string fn_data_out;
    int record_save_flag;
    int time_vx_slice_save_flag;
    int time_vz_slice_save_flag;
    int time_p_slice_save_flag;
    int sdt;
    int model_save_flag;
    int pml_save_flag;
    int wavelet_save_flag;
    int acoustic_flag;
    //int ObservationSystem_flag;
    int FreeSurface_flag;

    //**并行设计
    int omp_ncores;

	//**计时设置
	float tvx;
    float tvz;
    float ttxx;
    float ttzz;
    float ttxz;
    //**日志flag
    int log_flag;
};
