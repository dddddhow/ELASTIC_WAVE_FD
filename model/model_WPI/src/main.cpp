//----------------------------------------------------------------------------//
//程序目的：
//       生成观测系统坐标（炮 和 检波器） 都用向量表示
//       炮     :   shot_vec
//       检波器 :   geophone_vec
//程序原理：
//
//程序参数说明：
//
//Copyright：2020-
//          WPI TONGJI University
//Author  ：ShengShen
//Time    ：2020 09 04
//----------------------------------------------------------------------------//

#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main()
{
    //========================================================================//
    //                       参数定义                                         //
    //========================================================================//
    int nz=790;    //模型纵向坐标
    int nx=1076;   //模型横向坐标

    int ns=200;      //炮数
    int nr;        //检波器数目

    int ObservationSystem_flag = 2;
    // 0: 单边放炮，地表接收
    // 1: 单边放炮，四周接收
    // 2: 四边放炮，四边接收
    if(ObservationSystem_flag == 0) // 单边放炮，地表接收
    {
        nr=nx;
    }
    if(ObservationSystem_flag == 1) // 单边放炮，四周接收
    {
        nr=nx*2+nz*2-4;
    }
    if(ObservationSystem_flag == 2) // 四边放炮，四边接收
    {
        nr=nx*2+nz*2-4;
    }

    arma::Col<float> x_shot(ns);
    arma::Col<float> z_shot(ns);
    arma::Mat<float> x_geo(nr,ns);
    arma::Mat<float> z_geo(nr,ns);

    int sx_first = 0;               //起始炮位置 横坐标
    int sz_first = 0;               //起始炮位置 纵坐标
    int dsx      = 21;             //横向炮间距
    int dsz      = 15;             //纵向炮间距

    int rx_first = 0;               //第一检波器位置 横坐标
    int rz_first = 0;               //第一检波器位置 纵坐标
    int drx      = 1;               //横向检波器间距
    int drz      = 1;               //纵向检波器间距

    //========================================================================//
    //                       生成观测系统        ObservationSyatem            //
    //========================================================================//


    if(ObservationSystem_flag == 0) // 单边放炮，地表接收
    {

        //炮 坐标
        for(int is=0; is<ns; is++)
        {
            x_shot(is)=sx_first+is*dsx;
            z_shot(is)=0;
        }

        //检波器 坐标
        for(int is=0; is<ns; is++)
        {
            for(int ir=0; ir<nr; ir++)
            {
                x_geo(ir,is)=rx_first+drx*ir;
                z_geo(ir,is)=0;
            }
        }
    }

    if(ObservationSystem_flag == 1) // 单边放炮，四边接收
    {
        if(nr != nx*2+nz*2-4)
        {
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<"ERROR!!! (The Parameters of Observation(nr) )"<<endl;
            cout<<nr<<" != "<<nx+nz+nz-4<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
        }
        else
        {
            //炮 坐标
            for(int is=0; is<ns; is++)
            {
                x_shot(is)=sx_first+is*dsx;
                z_shot(is)=0;
            }

            //检波器 坐标
            for(int is=0; is<ns; is++)
            {
                for(int ir=0; ir<=nx-1; ir++)
                {
                    x_geo(ir,is)=ir;
                    z_geo(ir,is)=0;
                }
                for(int ir=nx; ir<=nz+nx-3; ir++)
                {
                    x_geo(ir,is)=nx-1;
                    z_geo(ir,is)=ir-nx+1;
                }
                for(int ir=nz+nx-2; ir<=nx+nz+nx-3; ir++)
                {
                    x_geo(ir,is)=nx-1-(ir-nz-nx+2);
                    z_geo(ir,is)=nz-1;
                }
                for(int ir=nz+nx+nx-2; ir<=nx+nz+nx+nz-5; ir++)
                {
                    x_geo(ir,is)=0;
                    z_geo(ir,is)=nz-2-(ir-(nz+nx+nx-2)+1);
                }
            }
        }
    }


    if(ObservationSystem_flag == 2) // 四边放炮，四周接收
    {
        if(nr != nx*2+nz*2-4)
        {
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<"ERROR!!! (The Parameters of Observation(nr) )"<<endl;
            cout<<nr<<" != "<<nx*2+nz+nz-4<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
            cout<<endl;
        }
        else{
            //炮 坐标
                for (int is=0; is<ns/4; is++)  //上侧边界
                {
                    int ix=is-0;
                    x_shot(is) = sx_first+ix*dsx;
                    z_shot(is) = 0;
                }
                for (int is =ns/4; is<ns/2; is++)  //右侧边界
                {
                    int iz=is-ns/4;
                    x_shot(is) = nx-1;
                    z_shot(is) = sz_first+iz*dsz;
                }
                for (int is=ns/2; is<ns*3*1.0/4; is++)  //下侧边界
                {
                    int ix=is-ns/2;
                    x_shot(is) = sx_first+ix*dsx;;
                    z_shot(is) = nz-1;
                }
                for (int is=ns*3.0/4; is<ns; is++)  //左侧边界
                {
                    int iz=is-ns*3.0/4;
                    x_shot(is) = 0;
                    z_shot(is) = sz_first+iz*dsz;
                }

            //检波器 坐标
            for(int is=0; is<ns; is++)
            {
                for(int ir=0; ir<=nx-1; ir++)
                {
                    x_geo(ir,is)=ir;
                    z_geo(ir,is)=0;
                }
                for(int ir=nx; ir<=nz+nx-3; ir++)
                {
                    x_geo(ir,is)=nx-1;
                    z_geo(ir,is)=ir-nx+1;
                }
                for(int ir=nz+nx-2; ir<=nx+nz+nx-3; ir++)
                {
                    x_geo(ir,is)=nx-1-(ir-nz-nx+2);
                    z_geo(ir,is)=nz-1;
                }
                for(int ir=nz+nx+nx-2; ir<=nx+nz+nx+nz-5; ir++)
                {
                    x_geo(ir,is)=0;
                    z_geo(ir,is)=nz-2-(ir-(nz+nx+nx-2)+1);
                }
            }
        }
    }


    //========================================================================//
    //                       文件保存                                         //
    //========================================================================//
    string fn_out = "../";

    // SHOT
    string fn_x_shot = fn_out+"shot_x_ns"+std::to_string(ns)+".dat";
    string fn_z_shot = fn_out+"shot_z_ns"+std::to_string(ns)+".dat";
    x_shot.save(fn_x_shot,raw_ascii);
    z_shot.save(fn_z_shot,raw_ascii);

    //GEOPHONE
    string fn_x_geophone = fn_out+"geophone_x_ns"+std::to_string(ns)+"_nr"+std::to_string(nr)+".dat";
    string fn_z_geophone = fn_out+"geophone_z_ns"+std::to_string(ns)+"_nr"+std::to_string(nr)+".dat";
    x_geo.save(fn_x_geophone,raw_ascii);
    z_geo.save(fn_z_geophone,raw_ascii);




    return 0;
}
