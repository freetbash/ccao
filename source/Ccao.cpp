#include "../include/Ccao.h"
#include "../include/toml.hpp"
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <iostream>
#include <sstream>
#include <fstream>

extern DataSet *dsp;
Cmd::Cmd(int argc,char *argv[]){
    this->isProject=file_exist("ccao.toml");
    if(!this->isProject){
        this->init(dsp);
    }
    
    int i;
    std::cout<<i<<std::endl;
    if (i<2) {
        std::cout<<"Please enter 'ccao help' to check your args.";
        exit(-3);
    }
    // ccao     new     app         app_name
    // agrv[0]  argv[1] argv[2]     argv[3]
    //          op      vector[0]   vector[1]
    this->op=argv[1];
    
    for (i = 2; i<argc; i++){
        this->args.push_back(argv[i]);
    }
    
}

void Cmd::compare(){
    if(this->op == "new"){
            // new project
        if(this->args.size() == 1 ){
            this->newproject(this->args[1]);
        }
            // new app
        if(this->args.size() == 2 and this->args[0] == "app"){
            this->check_status();
            this->newapp(this->args[1]);
        }
        return;
    }
    if(this->op == "help"){
        this->show_help();
        return;
    }
    if(this->op == "version"){
        this->version();
        return;
    }
    if(this->op == "build" and this->args.size() == 0){
        this->check_status();
        this->build();
        return;
    }
    if(this->op == "collect" and this->args.size() ==0){
        this->check_status();
        this->collect_depends();
        return;
    }
    if(this->op == "export_app" and this->args.size() ==1){
        this->check_status();
        this->export_app();//你还没有完成
    }
    this->show_help();
}

void Cmd::export_app(){}

void Cmd::check_status(){
    // 检查是否为 工程目录
    if(!this->isProject){
        std::cout<<"[-] You can't execute this operation, because this folder is not a Ccao project."<<std::endl;
        exit(-4);
    }
}

void Cmd::show_help(){
    std::string help_text = R""(
usage: ccao <command> [<args>]

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
}

void Cmd::version(){
    std::cout<<"[*] ccao version "<<VERSION<<std::endl;
}

void Cmd::newproject(std::string project_name){
    std::string cwd=std::string(get_current_dir_name());
    cwd = cwd + "/" + project_name;
    // Main App
    std::string main_app = cwd+project_name;
        mkdir(main_app.c_str(),S_IRUSR|S_IWUSR);
        mkdir((main_app+"/headers").c_str(),S_IRUSR|S_IWUSR);
            std::ofstream hello;
            hello.open(
                (main_app+"/headers/hello.h"),std::ios::out
            );
            {hello << R""(#ifndef __CCAO_HELLO_H
#define __CCAO_HELLO_H

void hello_world();

#endif)"";}
            hello.close();
        mkdir((main_app+"/source").c_str(),S_IRUSR|S_IWUSR);
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
    mkdir((cwd+"/apps").c_str(),S_IRUSR|S_IWUSR);
    
    // Depends
    mkdir((cwd+"/depends").c_str(),S_IRUSR|S_IWUSR);
    
    // out
    mkdir((cwd+"/out").c_str(),S_IRUSR|S_IWUSR);
        // debug
        mkdir((cwd+"/out/debug").c_str(),S_IRUSR|S_IWUSR);
            mkdir((cwd+"/out/debug/bin").c_str(),S_IRUSR|S_IWUSR);
            mkdir((cwd+"/out/debug/libs").c_str(),S_IRUSR|S_IWUSR);
                mkdir((cwd+"/out/debug/libs/own").c_str(),S_IRUSR|S_IWUSR);
                mkdir((cwd+"/out/debug/libs/other").c_str(),S_IRUSR|S_IWUSR);
        // release
        mkdir((cwd+"/out/release").c_str(),S_IRUSR|S_IWUSR);
            mkdir((cwd+"/out/release/bin").c_str(),S_IRUSR|S_IWUSR);
            mkdir((cwd+"/out/release/libs").c_str(),S_IRUSR|S_IWUSR);
                mkdir((cwd+"/out/release/libs/own").c_str(),S_IRUSR|S_IWUSR);
                mkdir((cwd+"/out/release/libs/other").c_str(),S_IRUSR|S_IWUSR);
    // ccao.toml
    std::ofstream ccao;
    ccao.open(cwd+"ccao.toml",std::ios::out);
    std::stringstream fmt;
    {fmt << R""([project]
name=")""<<project_name<<R""("
#version=0.01
cppversion="c++11"
debug=true
cpp=true
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

void Cmd::init(DataSet *dsp){
    this->dsp=dsp;
}

void Cmd::newapp(std::string app_name){}

void Cmd::build(){}

void Cmd::collect_depends(){}

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

void start(){
    if(
        !(access(get_current_dir_name(),W_OK) == 0 )
    ){
        std::cout<<"[-] Please ensure you are root or sudors ,because you don't have access to operate this folder"<<std::endl;
        exit(-3);
    }

}

bool file_exist(std::string filename){
    struct stat buffer;
    return (stat (filename.c_str(),&buffer) ==0);
}