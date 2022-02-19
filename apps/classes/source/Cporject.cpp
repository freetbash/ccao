#include <Cproject.h>
#include <vars.h>
#include <tools.h>
#include <public.h>

void PROJECT(){
    Cproject *temp_project = new Cproject;

    temp_project->main = MAIN();// 最终要生成的可执行文件

    for (std::string app :config->apps){
        temp_project->apps.push_back(
            App(app,APP)
        );
    }

    for (std::string depend :config->depends){
        temp_project->depends.push_back(
            App(depend,DEPEND)
        );
    }

    project=temp_project;

            // 保持同一 前面不留空格 后面留   很重要
    // debug 模式 默认 或 dynamic 为 true生成 .so
    cflag = "";
    libflag="";

    for(App depend:project->depends){
        include_path+="-I"+root+"/depends/"+depend.name+"/headers ";
        if(!depend.blank){
            link_file+=depend.out_path+"/lib"+depend.name+".a ";
        }
    }
    for(App app :project->apps){
        include_path+="-I"+root+"/apps/"+app.name+"/headers ";
        if(!app.blank){
            
            link_file+=app.out_path+"/lib"+app.name+".a ";
        }
    }
    

    include_path += "-I"+root+"/"+config->name+"/headers ";
    // 你打算完成Cmd::build 里的 貌似有些复杂 头文件不用动
    // gcc -fPIC -shared xxx.c -o libxxx.so
    if(debug){
        cflag ="-g -Wall ";
    }
    cflag+="-std="+config->cppversion+" ";// c++11
    

    libflag="-c -std="+config->cppversion+" ";

}
