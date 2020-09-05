//----------------------------------------------------------------------------//
//程序目的：
//       从原速度模型中去除地表低俗带，保留指定速度
//程序原理：
//
//程序参数说明：
//
//Copyright：2020-
//          WPI TONGJI University
//Author  ：ShengShen
//Time    ：2020 08 20
//----------------------------------------------------------------------------//



#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main()
{
    //========================================================================//
    //                       参数定义&文件载入                                //
    //========================================================================//
    int nx=1076;    //原速度模型大小
    int nz=790;     //

    int nx_new=1076;  //新速度模型大小
    int nz_new=790;  //

    int nx_start=0; //新速度模型起始位置
    int nz_start=0;    //

    arma::Mat<float> model_ori(nz,nx,fill::zeros);//原速度模型
    arma::Col<float> surface(nx,fill::zeros);//原速度模型地表位置

    arma::Mat<float> model_new(nz_new,nx_new);//新速度模型
    arma::Col<float> surface_mini(nx_new,fill::zeros);//新速度模型地表位置

    arma::Mat<float> model_sur(nz_new,nx_new,fill::zeros); //指定速度模型

    model_ori.load("WPIVelocityModel_nz790_nx1076_dx5_dz5.dat",raw_binary);
    model_ori.reshape(nz,nx);
    //========================================================================//
    //                       生成新速度模型MiniAmoco                          //
    //========================================================================//
    for(int ix=0; ix<nx_new; ix++)
    {
        for(int iz=0; iz<nz_new; iz++)
        {
            model_new(iz,ix)=model_ori(iz+nz_start,ix+nx_start);
        }
    }
    //========================================================================//
    //                       计算地表（观测系统）ObservationSyatem            //
    //========================================================================//

    for (int ix=0; ix<nx ;ix++)
    {
        int flag = 0;
        for(int iz=1; iz<nz; iz++)
        {
            if(flag==0 &&  model_ori(iz,ix)>model_ori(iz-1,ix)+100)
            {
                //surface(ix)=iz;
                surface(ix)=0;
                flag = 1;
            }
        }
    }

    for (int ix=0; ix<nx_new; ix++)
    {
        int flag = 0;
        for(int iz=1; iz<nz_new; iz++)
        {
            if(flag==0 &&  model_new(iz,ix)>model_new(iz-1,ix)+100)
            {
                //surface_mini(ix)=iz;
                surface_mini(ix)=0;
                flag = 1;
            }
        }
    }

    //========================================================================//
    //                       生成指定速度模型MiniAmoco_max                    //
    //========================================================================//
    float v_back = min(min(model_new));
    for(int ix=0; ix<nx_new ;ix++)
    {
        for(int iz=0; iz<nz_new;iz++)
        {
            if (iz<surface(ix))
            {
                model_sur(iz,ix)=model_ori(iz,ix);
            }
            else
            {
                //01 : every point
                //model_sur(iz,ix)=model_new(surface(ix),ix);

                //02 : background velocity
                model_sur(iz,ix)=v_back;

                //03 : some trick

                //if(model_new(iz,ix)>1000)
                //{
                    //model_sur(iz,ix) = 1000;
                //}
                //else
                //{
                    //model_sur(iz,ix) = model_new(iz,ix);
               /* }*/

            }
        }
    }
    //========================================================================//
    //                       文件保存                                         //
    //========================================================================//
    string fn_out = "../";


    string fn_model_new = fn_out + "Mini_WPIVelocityModel_nz"
        +std::to_string(nz_new) + "_nx"
        +std::to_string(nx_new)+".dat";
    model_new.save(fn_model_new,raw_binary);


    string fn_surface_all = fn_out + "surface_all_nx"
        +std::to_string(nx)+".dat";
    surface.save(fn_surface_all,raw_binary);


    string fn_surface_mini = fn_out + "surface_mini_nx"
        +std::to_string(nx_new)+".dat";
    surface_mini.save(fn_surface_mini,raw_binary);


    string fn_model_spec = fn_out + "Mini_WPIVelocityModel_nz"
        +std::to_string(nz_new) + "_nx"
        +std::to_string(nx_new)+"_background.dat";
    model_sur.save(fn_model_spec,raw_binary);


    return 0;
}
