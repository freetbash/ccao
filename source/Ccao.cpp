#include "../include/Ccao.h"
#include "../include/toml.hpp"
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <iostream>
#include <sstream>
#include <fstream>

extern bool debug;

Cmd::Cmd(int argc,char *argv[],DataSet *dsp){
    if (argc<2) {
        std::cout<<"Please enter 'ccao help' to check your args."<<std::endl;
        exit(-3);
    }

    this->dsp=dsp;    
    
    // ccao     new     app         app_name
    // agrv[0]  argv[1] argv[2]     argv[3]
    //          op      vector[0]   vector[1]
    this->op=argv[1];
    
    for (int i = 2; i<argc; i++){
        this->args.push_back(argv[i]);
    }
    
}

void Cmd::compare(){
    
    if(this->op == "new"){

            // new project
        if(this->args.size() == 1 ){
            if(this->args[0] == "app"){
                std::cout<<"[-] You can't use the 'app' as your project_name"<<std::endl;
                std::cout<<"[*] (Tip~)$ ccao new app app_name"<<std::endl;
                exit(7);
            }
            this->newproject(this->args[0]);
            exit(7);
        }

            // new app
        if(this->args.size() == 2 and this->args[0] == "app"){
            this->check_status();
            this->newapp(this->args[1]);
            exit(8);
        }
    }
    if(this->op == "help"){
        // 跳过就好
    }
    if(this->op == "version"){
        this->version();
        exit(2);
    }
    if(this->op == "build" and this->args.size() == 0){
        this->check_status();
        this->build();
        exit(3);
    }
    if(this->op == "collect" and this->args.size() ==0){
        this->check_status();
        this->collect_depends();
        exit(4);
    }
    if(this->op == "export_app" and this->args.size() ==1){
        this->check_status();
        this->export_app();//你还没有完成
        exit(5);
    }
    this->show_help();
    log("[*] op: "+this->op);
    exit(1);
}

void Cmd::export_app(){}

void Cmd::check_status(){
    // 检查是否为 工程目录
    if(!this->dsp->config->isProject){
        std::cout<<"[-] You can't execute this operation, because this folder is not a Ccao project."<<std::endl;
        exit(-4);
    }
}

void Cmd::show_help(){
    std::string help_text = R""(usage: ccao <command> [<args>]

All commands:
    build       // build your all apps and your main function. Please check your debug of ccao.toml
    collect     // collect lib from internet or local libray(it could try this at first)
    help        // print helpful text of ccao
    version     // print the version of ccao

Special with args:
    new project_name    // create a project
    new app app_name    // create a app
    export_app app_name // export yout app to 7z to deliver it on web


Author:
    This tool is made by Freet-Bash.
    If you want to get into the development, please go to github or gitee and fork this repo.
    If you have other problems ,please get in touch with me.
    Here is my email : 3141495167@qq.com 

    )"";
    std::cout<<help_text<<std::endl;
}

void Cmd::version(){
    std::cout<<"[*] ccao version "<<VERSION<<std::endl;
}

void Cmd::newproject(std::string project_name){
    int status;
    std::string cwd=std::string(get_current_dir_name());
    cwd = cwd + "/" + project_name;
    // Porject
    c_mkdir(cwd);
    // Main App
    std::string main_app = cwd+ "/"+project_name;
        c_mkdir(main_app);
        c_mkdir((main_app+"/headers"));
            std::ofstream hello;
            hello.open(
                (main_app+"/headers/hello.h"),std::ios::out
            );
            {hello << R""(#ifndef __CCAO_HELLO_H
#define __CCAO_HELLO_H

void hello_world();

#endif)"";}
            hello.close();
        c_mkdir((main_app+"/source"));
            std::ofstream main;
            main.open(
                (main_app+"/source/main.cpp"),std::ios::out
            );
            {main<<R""(#include "../headers/hello.h"
#include <iostream>

using namespace std;

void hello_world(){
    cout << "Hello world !"<<endl;
}

int main(int argc, char *argv[]){

    hello_world();

    return 0;
})"";}
            main.close();
    
    // Apps
    c_mkdir((cwd+"/apps"));
    
    // Depends
    c_mkdir((cwd+"/depends"));
    
    // out
    c_mkdir((cwd+"/out"));
        // temp
        c_mkdir((cwd+"/out/temp"));
        // debug
        c_mkdir((cwd+"/out/debug"));
            c_mkdir((cwd+"/out/debug/bin"));
            c_mkdir((cwd+"/out/debug/libs"));
                c_mkdir((cwd+"/out/debug/libs/own"));
                c_mkdir((cwd+"/out/debug/libs/other"));
        // release
        c_mkdir((cwd+"/out/release"));
            c_mkdir((cwd+"/out/release/bin"));
            c_mkdir((cwd+"/out/release/libs"));
                c_mkdir((cwd+"/out/release/libs/own"));
                c_mkdir((cwd+"/out/release/libs/other"));
    // ccao.toml
    std::ofstream ccao;
    ccao.open(cwd+"/ccao.toml",std::ios::out);
    std::stringstream fmt;
    {fmt << R""([project]
name=")""<<project_name<<R""("
#version=0.01
cppversion="c++11"
debug=true
cpp=true# g++ or gcc
dynamic=false #生成 .a 而不是 .so
apps=[
    #"app1",
]
depends=[
    #"1$version"
])"";}
    ccao << fmt.str();
    ccao.close();

    std::cout<<"[+] new "<<project_name<<" Ok!"<<std::endl;
}   


void Cmd::newapp(std::string app_name){
 // 你打算 开发 new app
    std::string app_dir = this->dsp->config->root+"/apps/"+app_name;
    if (file_exist(app_dir)){
        log("[-] The '"+app_name+"' has been created!");
        exit(-5);
        
    }
    c_mkdir(app_dir);
    // headers
    c_mkdir(app_dir+"/headers");
    // source
    c_mkdir(app_dir+"/source");
    log("[*] Please instert '"+app_name+"' into the 'ccao.toml' .");
}

void Cmd::build(){
    std::vector<std::string> cmds;
    std::string dynamic="";
    std::string debug_op = "-g -Wall -fPIC -std="+this->dsp->config->cppversion;
    // 你打算完成Cmd::build 里的 貌似有些复杂 头文件不用动
    if(!debug){
        debug_op ="-fPIC -std="+this->dsp->config->cppversion;;
    }

    if(this->dsp->config->dynamic){
        cmds.push_back(debug_op);
    }else{

    }

    for(App app :this->dsp->project->apps){
        app.build(cmds);
    }

    // build main_app
    check_error(system(""));


}

void Cmd::collect_depends(){}

Cconfig::Cconfig(){
    // 判断是否为工程项目
    this->isProject=file_exist("ccao.toml");
    // init root
    char *path = get_current_dir_name();
    if(path!=NULL){
        this->root=path;
    }else{
        std::cout<<"[-]Your absolute path isn't setted successfully!\n [-]Please check your permissions. "<<std::endl;
        exit(-1);
    }

    if(!this->isProject){return;} // 这里可是个关键

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

    this->dynamic = toml::find
        <bool>
    (project_data,"dynamic");




}
App::App(){}
App::App(void *project){
    Cproject *fuck_project = (Cproject *)project;
    std::vector<std::string> temp;

    this->type=APP;
    this->name = fuck_project->config->name;
        this->headers = ls(fuck_project->config->root+"/"+this->name+"/headers");
        this->source = ls(fuck_project->config->root+"/"+this->name+"/source");


    // 判断目录为不为空
    if(
        (this->headers.size() == 0) and (this->source.size() == 0)
    ){
        this->blank=true;

    }else{
        this->blank=false;
    }

};
App::App(std::string name,std::string root,int type){
    std::vector<std::string> temp;

    std::string build_out_path = "/out/debug/libs";
    if (!debug){
        build_out_path = "/out/release/libs";
    }
    this->type=type;
    this->name = name;
    
    // 根据类型初始化
    if(this->type == APP){
        this->path = root+"/apps/"+name;
        this->headers = ls(this->path+"/headers");
        this->source  = ls(this->path+"/source");
        this->out_path = build_out_path+"/own";
    }

    if(this->type == DEPEND){
        this->path = root+"/depends/"+name;
        this->headers = ls(this->path+"/headers");
        this->source  = ls(this->path+"/source");
        this->out_path = build_out_path+"/other";
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

void build(std::vector<std::string> cmds){
    for (std::string cmd : cmds){

    }


}


Cproject::Cproject(Cconfig *config){
    
    this->config = config;
    this->main = App(this);// 最终要生成的可执行文件

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
        log(path);
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

void start(){
    if(
        !(access(get_current_dir_name(),W_OK) == 0 )
    ){
        std::cout<<"[-] Please ensure you are root or sudors ,because you don't have access to operate this folder"<<std::endl;
        exit(-3);
    }
}
void c_mkdir(std::string path){
    check_error(mkdir(path.c_str(),0775));
}
void check_error(int status){
    if(status<0){
        std::cout<<"[-] "<<strerror(errno)<<std::endl;
    }
}

void log(std::string msg){
    std::cout<<msg<<std::endl;
}

bool file_exist(std::string filename){
    struct stat buffer;
    return (stat (filename.c_str(),&buffer) ==0);
}