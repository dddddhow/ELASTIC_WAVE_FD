#include "../lib/ShengShen_head.h"
#include "../lib/Parameter_func.h"
#include "../lib/Forward_func.h"
#include "../lib/RickerWavelet_func.h"
#include "../lib/IO_func.h"
#include "../lib/Parameter_IO.h"

int main(int argc, char* argv[])
{
    //---------------------------------------------//
    //            计时器--开始                     //
    //---------------------------------------------//
    double start = omp_get_wtime();

    //---------------------------------------------//
    //            正演模拟                         //
    //---------------------------------------------//
    //*各种参数*//
    const string fn_par(argv[1]);
    PARAMETER param;
    Parameter par;
    readpar_func(fn_par,par);
    printpar_func(par);
    parameter_func(&param, &par);
    obs_func(&param);

    //**正演**//
    forward_func(&param);

    //---------------------------------------------//
    //            反演成像                         //
    //---------------------------------------------//



    //---------------------------------------------//
    //            计时器--结束                     //
    //---------------------------------------------//
    double end = omp_get_wtime();
    double totaltime=end-start;
    printf("It took %f seconds\n",totaltime);

    return 0;

}
