#include <Cproject.h>
#include <vars.h>
#include <tools.h>
#include <public.h>

void PROJECT(){
    Cproject *temp_project = new Cproject;

    for (std::string app :config->apps){
        temp_project->apps.push_back(
            App(app)
        );
    }
    for(std::string depend :config->depends){
        temp_project->depends.push_back(
            Depend(depend)
        );
    }
    project=temp_project;

            // 保持同一 前面不留空格 后面留   很重要
    cflag = "";
    include_path += "-I"+root+"/"+config->name+"/headers ";
    // 拼接 主程序的 头文件目录 
    if(debug){
        cflag ="-g -Wall ";
        exe_file_path = root+"/out/debug/"+config->name+" ";
    }else{
        cflag = "-O3 ";
        exe_file_path = root+"/out/release/"+config->name+" ";
    }
    cflag+="-std="+config->cppversion+" ";// c++11
    

}
