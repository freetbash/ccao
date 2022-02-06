#include "../include/Ccao.h"
#include "../include/toml.hpp"
#include <unistd.h>
#include <dirent.h>
#include <iostream>

Cmd::Cmd(int argc,char *argv[],DataSet *dsp){
    this->dsp=dsp;
    int i;
    if (i<2) {
        std::cout<<"Please enter 'ccao help' to check your args.";
        exit(-3);
    }

    this->op=argv[1];

    for (i = 2; i<argc; i++){
        this->args.push_back(argv[i]);
    }
    
}
void Cmd::compare(){
    if(this->op == "new"){
        if(this->args.size() == 2){
            this->newproject(this->dsp);
        }
    }
    // 你将继续完成匹配函数
}


Cconfig::Cconfig(){
    
    // init root
    char *path = get_current_dir_name();
    if(path!=NULL){
        this->root=path;
    }else{
        std::cout<<"[-]Your absolute path isn't setted successfully!\n [-]Please check your permissions. "<<std::endl;
        exit(-1);
    }

    std::string ccao = this->root + "/ccao.toml";
    const toml::value data=toml::parse(ccao);

    // 配置[project]
    const auto project_data = toml::find(data,"project");
    this->name = toml::find
        <std::string>
    (project_data,"name");

    this->apps = toml::find
        <std::vector<std::string>>
    (project_data,"apps");

    this->depends = toml::find
        <std::vector<std::string>>
    (project_data,"depends");
    // gcc or g++
    this->cpp = toml::find
        <bool>
    (project_data,"cpp");

    this->debug = toml::find
        <bool>
    (project_data,"debug");

    this->cppversion = toml::find
        <std::string>
    (project_data,"cppversion");




}

App::App(){};
App::App(std::string name,std::string root,int type){
    std::vector<std::string> temp;

    this->type=type;
    this->name = name;
    // 根据类型初始化
    if(this->type == APP){
        this->headers = ls(root+"apps"+name+"headers");
        this->source = ls(root+"apps"+name+"source");
    }

    if(this->type == DEPEND){
        this->headers = ls(root+"depends"+name+"headers");
        this->source = ls(root+"depends"+name+"source");
    }

    // 判断目录为不为空
    if(
        (this->headers.size() == 0) and (this->source.size() == 0)
    ){
        this->blank=true;
    }else{
        this->blank=false;
    }

}

Cproject::Cproject(Cconfig config){
    
    this->config = &config;
    this->main = App(this->config->name,this->config->root,APP);// 最终要生成的可执行文件

    for (std::string app :this->config->apps){
        this->apps.push_back(
            App(app,this->config->root,APP)
        );
    }

    for (std::string depend :this->config->depends){
        this->depends.push_back(
            App(depend,this->config->root,DEPEND)
        );
    }

}

DataSet::DataSet(Cproject *project,Cconfig *config){
    this->config=config;
    this->project=project;
}



std::vector<std::string> ls(std::string path){
    DIR *dp;
    std::vector<std::string> dirs;
    struct dirent *dirp;
    char dirname[256];

    if(
        (dp=opendir(path.c_str())) == NULL)
    {
        std::cout << "[-]List files failed . \n[-]Please check your permissions. "<<std::endl;
        exit(-2);
    }

    while (
        ((dirp=readdir(dp))!=NULL)
    )
    {
        if(
            (dirp->d_name != std::string(".") and dirp->d_name != std::string(".."))
        ){
            dirs.push_back(dirp->d_name);
        }
    }
    closedir(dp);
    return dirs;
}