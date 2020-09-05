#include "../lib/Parameter_func.h"

using namespace arma;

double obs_func(struct PARAMETER* param)
{
    printf("//-----------------------------------------------------//\n");
    printf("Setting Up The Obssystem Begin\n");

    //炮点&检波点坐标系设置
    int nx       = param->NX;
    int nz       = param->NZ;
    int npml     = param->PML;

    int ns       = param->Ns;                     //炮数
    int nr       = param->Nr;                     //检波器数目

    //观测系统加载
    arma::Col<float> sur_location(nx);  //地表面在模型中的高程（点）
    std::string fn_ObservationSystem_location_surface = param->fn_ObservationSystem_location
        +"surface_mini_nx"+std::to_string(nx)+".dat";
    sur_location.load(fn_ObservationSystem_location_surface,raw_binary);

    arma::Col<float> shot_x(ns,fill::zeros);  //炮点横坐标 （点）
    arma::Col<float> shot_z(ns,fill::zeros);  //炮点纵坐标 （点）
    arma::Mat<float> geophone_x(nr,ns,fill::zeros); //检波器横坐标 （点）
    arma::Mat<float> geophone_z(nr,ns,fill::zeros); //检波器纵坐标 （点）

    string fn_ObservationSystem_location_shot_x = param->fn_ObservationSystem_location
        +"shot_x_ns"+std::to_string(ns)+".dat";
    string fn_ObservationSystem_location_shot_z = param->fn_ObservationSystem_location
        +"shot_z_ns"+std::to_string(ns)+".dat";
    string fn_ObservationSystem_location_geophone_x = param->fn_ObservationSystem_location
        +"geophone_x_ns"+std::to_string(ns)+"_nr"+std::to_string(nr)+".dat";
    string fn_ObservationSystem_location_geophone_z = param->fn_ObservationSystem_location
        +"geophone_z_ns"+std::to_string(ns)+"_nr"+std::to_string(nr)+".dat";

    shot_x.load(fn_ObservationSystem_location_shot_x,raw_ascii);
    shot_z.load(fn_ObservationSystem_location_shot_z,raw_ascii);
    geophone_x.load(fn_ObservationSystem_location_geophone_x,raw_ascii);
    geophone_z.load(fn_ObservationSystem_location_geophone_z,raw_ascii);

    shot_x.as_col();
    shot_z.as_col();
    geophone_x.reshape(nr,ns);
    geophone_z.reshape(nr,ns);


    //Arma矩阵格式转给alloc格式矩阵
    param->Sx=alloc1int(ns);
    param->Sz=alloc1int(ns);
    param->Rx=alloc2int(nr,ns);
    param->Rz=alloc2int(nr,ns);

    for(int is=0; is<ns; is++)
    {
        param->Sx[is] = shot_x(is)+npml;
        param->Sz[is] = shot_z(is)+npml;

        for(int ir=0; ir<nr ;ir++)
        {
            param->Rx[is][ir] = geophone_x(ir,is)+npml;
            param->Rz[is][ir] = geophone_z(ir,is)+npml;
        }
    }

    printf("Setting Up The Obssystem Finish\n");
    printf("//-----------------------------------------------------//\n");
    return 0;
}
