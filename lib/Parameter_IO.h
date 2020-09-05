#ifndef PARAMETER_IO_H
#define PARAMETER_IO_H

#include <armadillo>
#include <iostream>

using namespace std;
using namespace arma;

//============================================================================//
//                                  参数卡结构体                              //
//============================================================================//
#define TJU_NLINE_PAR           18
#define TJU_LENGTH_FILENAME     300
typedef struct Parameter
{
    //===== Start Of Par File =====//

    char    fn_path_of_model_in_char [TJU_LENGTH_FILENAME];           // line 01
    char    fn_path_of_ObservationSystem_char [TJU_LENGTH_FILENAME];  // line 02
    char    fn_path_of_data_output_char [TJU_LENGTH_FILENAME];        // line 03

    string    fn_path_of_model_in;                                    // line 01
    string    fn_path_of_ObservationSystem;                           // line 02
    string    fn_path_of_data_output;                                 // line 03

    int nx;  int nz; int nt;                                          // line 04
    float dx; float dz;  float dt;                                    // line 05
    int ns; int nr;                                                   // line 06
    int npml;                                                         // line 07
    int n_omp_cores;                                                  // line 08
    float wavelet_frequence;                                          // line 09
    int FreeSurface_flag;                                             // line 10
    int flag_record_save; int flag_model_save; int flag_wavelet_save; int flag_acoustic_elastic;
                                                                      // line 11

    int flag_snap_vx_save; int flag_snap_vz_save; int flag_snap_p_save; int flag_snap_sdt;
                                                                      // line 12

    //=====End Of Par File =====//
} Parameter;


int readpar_func(const string &fn_par, Parameter &par);


int printpar_func(Parameter &par);


#endif
