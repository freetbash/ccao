#include <Cmd.h>
#include <tools.h>
#include <vars.h>
#include <public.h>


Cmd::Cmd(int argc,char *argv[]){
    if (argc<2) {
        std::cout<<"Please enter 'ccao help' to check your args."<<std::endl;
        exit(-3);
    }
    
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
    if(this->op == "clean"){
        this->check_status();
        this->clean();
        exit(11);
    }
    if(this->op == "install"){
        this->check_status();
        this->install();
        exit(12);
    }
    if(this->op == "build"){
        this->check_status();
        this->build(project->main);
        exit(3);
    }
    if(this->op == "collect" and this->args.size() ==0){
        this->check_status();
        this->collect_depends();
        exit(4);
    }
    // if(this->op == "export"){
    //     this->check_status();

    //     if(this->args.size() ==0){
    //         ; // export whole project as a 7z
    //         exit(10);
    //     }else{
    //         std::string mode = this->args[0];// 存放操作码
    //         this->args.erase(this->args.begin()); // 删除操作码
    //         if (this->args.size() < 0){
    //             log("[-] Please type out some names of your");
    //             }
            
    //         for(std::string app_name :this->args){
    //             App *target=NULL;
    //             target = App::find(app_name);
    //             if(target!=NULL){
    //                 if(mode=="code"){
    //                     this->export_apps_to_stars(target,CODE);
    //                 }else if(mode == "libs"){
    //                     this->export_apps_to_stars(target,LIBS);
    //                 }else{
    //                     log("[-] Please select a mode from ['code','libs'] ");
    //                     exit(-8);
    //                 }
    //             }else{
    //                 log("[*] Skip the "+app_name+", because it is not a app.");
    //             }
    //         }
    //         exit(5);

    //     }
    // }
    this->show_help();
    log(color("[*] op: "+this->op,BLUE));
    exit(1);
}

void Cmd::check_status(){
    // 检查是否为 工程目录
    if(!isProject){
        std::cout<<"[-] You can't execute this operation, because this folder is not a Ccao project."<<std::endl;
        exit(-4);
    }
}

void Cmd::show_help(){
    std::string help_text = 
        color("usage:",GREEN) +" ccao <command> [<args>]\n"
        +"All commands:\n\t"
        +color("build",YELLOW)+"       // build your all apps and your main function. Please check your debug of ccao.toml\n\t"
        +color("collect",YELLOW)+"     // collect lib from internet or local libray(it could try this at first)\n\t"
        +color("help",YELLOW)+"        // print helpful text of ccao\n\t"
        +color("version",YELLOW)+"     // print the version of ccao\n\t"
        +color("clean",YELLOW)+"       // clean your previous build lib or files\n\t"
        +color("install",YELLOW)+"     // cp your target elf to /usr/local/bin\n\n"

        +"Special with args:\n\t"
        +color("new project_name",BLUE)+"    // create a project\n\t"
        +color("new app app_name",BLUE)+"    // create a app\n\t"
        +color("export",BLUE)+" // export your whole porject to a tar.xz\n\n"

        +color("Author:\n\tThis tool is made by Freet-Bash.\n\tIf you want to get into the development, please go to github or gitee and fork this repo.\n\tIf you have other problems ,please get in touch with me.\n\tHere is my email : 3141495167@qq.com",HIGH_LIGHT);
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
            {main<<R""(#include <hello.h>
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
        // stars
        c_mkdir((cwd+"/out/stars"));
            // code
            c_mkdir((cwd+"/out/stars/code"));
            // libs
            c_mkdir((cwd+"/out/stars/libs"));
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
apps=[
    #每一个app应该是相互独立的 如果需要 请你导出为star并添加到depends里面
    #"app1",
]
depends=[
    #"1$version"
])"";}
    ccao << fmt.str();
    ccao.close();

    std::cout<<"[+] new "<<project_name<<" Ok!"<<std::endl;
}   

void Cmd::clean(){
    
    system(
        ("rm -rf "+root+"/out ").c_str()
    );
    // out
    {
        c_mkdir((root+"/out"));
            // temp
            c_mkdir((root+"/out/temp"));
            // stars
            c_mkdir((root+"/out/stars"));
                // code
                c_mkdir((root+"/out/stars/code"));
                // libs
                c_mkdir((root+"/out/stars/libs"));
            // debug
            c_mkdir((root+"/out/debug"));
                c_mkdir((root+"/out/debug/bin"));
                c_mkdir((root+"/out/debug/libs"));
                    c_mkdir((root+"/out/debug/libs/own"));
                    c_mkdir((root+"/out/debug/libs/other"));
            // release
            c_mkdir((root+"/out/release"));
                c_mkdir((root+"/out/release/bin"));
                c_mkdir((root+"/out/release/libs"));
                    c_mkdir((root+"/out/release/libs/own"));
                    c_mkdir((root+"/out/release/libs/other"));
    }
}

void Cmd::install(){
    std::string target_path = root+"/out/release/bin/"+project->main->name;
    if(!file_exist(target_path)){
        if(!debug){
        log(color("[*] elf not found , start build !",BLUE));
        this->build(project->main);
        }else{
            log(color("[-] you must be in release mode .",RED));
        }
    }
    system(("sudo cp "+target_path+" /usr/local/bin/").c_str());
    log(color("[+] "+target_path,GREEN));
}

void Cmd::newapp(std::string app_name){
 // 你打算 开发 new app
    std::string app_dir = root+"/apps/"+app_name;
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

void Cmd::build(App *main){
    this->clean();


    // build depends 先生成依赖 没毛病
    for(App depend :project->depends){
        depend.build(libflag,include_path,libray_path);
    }
    log(
        color("[+]All depends "+std::to_string(project->depends.size()),PUPLE)
    );

    // build your apps
    for(App app :project->apps){
        app.build(libflag,include_path,libray_path);
    }
    log(
        color("[+]All apps "+std::to_string(project->apps.size()),PUPLE)
    );

    // build main_app 
    
    //源码
    std::string source;

    for(std::string c_cpp :main->source){
        source += root+"/"+main->name+"/source/"+c_cpp+" ";
    }
    // 将c cpp 路径 拼接到一起
    std::string compiler;
    if(cpp){
        compiler="g++ ";
    }else{
        compiler="gcc ";
    }

    std::string cmd(
        compiler
        +source
        +cflag
        +include_path
        +libray_path
        +link_file
        +"-o "
        +main->out_path+"/"
        +main->name
    );
    log("[*] "+cmd);
    
    check_error(system(cmd.c_str()));
    log(
            "[+]Build Ok!  It is here { \n\t"+color(main->out_path+"/"+main->name,GREEN)+" \n} "
    );
}

void Cmd::collect_depends(){}

