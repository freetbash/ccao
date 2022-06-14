#include <base/Cmd.h>
#include <utils/tools.h>
#include <public/vars.h>
#include <public/public.h>


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

void Cmd::check(){ // ok
    if(!config->is_project){
        log(color("[-]Your directory is not ccao project ,so can not execute yout command!",RED));
        exit(-1);
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
            this->newapp(this->args[1]);
            exit(8);
        }
    }
    if(this->op == "help"){
        // 跳过就好
    }
    if(this->op == "run"){
        if(this->args.size()==0){
            std::string args("");
            for(auto _:this->args){
                args+= _ +" ";
            }
            this->run_project(args);
            exit(23);
        }
    }
    if(this->op == "version"){
        this->version();
        exit(2);
    }
    if(this->op == "clean"){
        this->clean();
        exit(11);
    }
    if(this->op == "install"){
        if(this->args.size()==0){
            this->install("/usr/local/bin/");
        }else{
            for(std::string out_path :this->args){
                this->install(out_path);
            }
        }
        exit(12);
    }
    if(this->op == "build"){
        this->build();
        exit(3);
    }
    if(this->op == "make"){
        this->make();
        exit(123);
    }
    if(this->op == "list"){
        this->list();
        exit(1);
    }
    if(this->op == "add"){
        if(this->args.size()==1){
            this->add(this->args[0]);
        }
        exit(1);
    }
    if(this->op == "cat"){
        if(this->args.size()==1){
            this->cat(this->args[0]);
        }else{
            log("please input right command for cat.");
        }
        exit(1);
    }
    if(this->op == "remove"){
        if(this->args.size()==1){
            this->remove(this->args[0]);
        }else{
            this->remove(this->args[0],this->args[1]);
        }
        exit(1);
    }
    if(this->op == "get"){
        if(this->args.size()==1){
            this->get(this->args[0]);
        }else{
            this->get(this->args[0],this->args[1]);
        }
        exit(1);
    }
    this->show_help();
    log(color("[*] op: "+this->op,BLUE));
    exit(1);
}

void Cmd::show_help(){ // ok
    
    std::cout<<help_text<<std::endl;
}

void Cmd::version(){ //ok
    std::cout<<"[*] ccao version "<<VERSION<<std::endl;
}

void Cmd::newproject(std::string project_name){ // ok
    std::string cwd;
    cwd = config->root + "/" + project_name;
    
    c_mkdir(cwd);
    c_mkdir(cwd+"/source");
    c_mkdir(cwd+"/temp");
    c_mkdir(cwd+"/bin");
    
    // Main App
    std::ofstream hello;
    hello.open((cwd+"/main.h"),std::ios::out);
{hello << R""(#ifndef __CCAO_HELLO_H
#define __CCAO_HELLO_H

void hello_world();

#endif)"";}hello.close();

    std::ofstream main;
    main.open((cwd+"/main.cpp"),std::ios::out);
{main<<R""(#include <main.h>
#include <iostream>

using namespace std;

void hello_world(){
    cout << "Hello world !"<<endl;
}

int main(int argc, char *argv[]){

    hello_world();

    return 0;
})"";}main.close();


    // ccao.toml
    std::ofstream ccao;
    ccao.open(cwd+"/ccao.toml",std::ios::out);
    std::stringstream fmt;
    {fmt << R""([project]
name=")""<<project_name<<R""("
#version="0"
cppversion="c++11"
debug=true
cflag="-static "#额外参数 默认为空
cpp=true # g++ or gcc
ccache=false # 启用ccache 高速编译
termux=false # 为aarch64提供支持 需要安装 aarch64-linux-gnu-g++
apps=[
    #"app0",
]
depends=[
    #"test$0"
])"";}
    ccao << fmt.str();
    ccao.close();

    std::cout<<"[+] new "<<project_name<<" Ok!"<<std::endl;
}   

void Cmd::clean(){ // ok
    this->check();
    if(config->is_project){
        check_error(system(
            ("rm -rf "+config->root+"/bin/* ;"+"rm -rf "+config->root+"/temp/* ").c_str()
        ));
    }else{
        log("[-] Here is not a project or star. ");
    }
    
}

void Cmd::install(std::string out_path){ // ok
    this->check();
    if(FileExists(config->exe_file_path)){
        check_error(system(("sudo cp "+config->exe_file_path+out_path).c_str()));
        log(color("[+] "+out_path,GREEN));
    }else{
        log(color("[-] please rebuild to get it!",RED));
    }
    
}

void Cmd::newapp(std::string app_name){ // ok
    this->check();
    std::string app_dir = config->root+"/"+app_name;
    if (FileExists(app_dir)){
        log("[-] The '"+app_name+"' has been created!");
    }else{
        c_mkdir(app_dir);
        c_mkdir(config->root+"/source/"+app_name);
        log("[*] Please instert '"+app_name+"' into the 'ccao.toml' .");
    }
}

void Cmd::build(){ // ok
    this->check();
    // 将c cpp 路径 拼接到一起
    std::string link_file("");
    std::string source_o;
    std::string cmd;
    // for headers
    for(Depend depend:project->depends){
        config->include_path+="-I"+depend.path+" ";
        link_file += depend.a;
    }

    for(App app:project->apps){
        app.build();
    }{
        log(color("[*]Building ("+config->name+")",HIGH_LIGHT));
        std::string cmd;
        for(auto cc: ls(config->root+"/source/"+config->name)){
            cmd=(
                config->compiler
                +"-c "
                +config->root+"/source/"+config->name+"/"+cc+" "
                +config->include_path
                +"-o "
                +config->root+"/temp/"+cc+".o "
                +config->cflag
                +config->extra_cflag
            );
            log("[*] "+cmd);
            check_error(system(cmd.c_str()));
        }
    }

    cmd=(
        config->compiler
        +config->root+"/temp/* main.cpp "
        +config->include_path
        +"-Xlinker '-(' "
        // -Xlinker "-("  /home/bash/projects/chameleon/out/debug/libs/own/libviews.a -Xlinker "-)" 
        +link_file
        +"-Xlinker '-)' "
        +"-o "
        +config->exe_file_path
        +config->cflag
        +config->extra_cflag
    );
    log("[*] "+cmd);
    check_error(system(cmd.c_str()));
    log(
            "[+]Build Ok!  It is here { \n\t"+color(config->exe_file_path,GREEN)+" \n} "
    );
}

void Cmd::make(){ // ok
    this->check();
    std::string link_file("");
    std::string cmd;
    for(App app:project->apps){
        app.build();
    }
        {
            log(color("[*]Building ("+config->name+")",HIGH_LIGHT));
            for(auto cc: ls(config->root+"/source/"+config->name)){
                cmd=(
                    config->compiler
                    +"-c "
                    +config->root+"/source/"+config->name+"/"+cc+" "
                    +config->include_path
                    +"-o "
                    +config->root+"/temp/"+cc+".o "
                    +config->cflag
                    +config->extra_cflag
                );
                log("[*] "+cmd);
                check_error(system(cmd.c_str()));
        }
    }
    for(std::string o:ls(config->root+"/temp")){
        link_file+=config->root+"/temp/"+o+" ";
    }
    cmd=(
        "ar crsv "
        +config->root+"/bin/lib"+config->name+".a "
        +link_file
    );
    log("[*] "+cmd);
    check_error(system(cmd.c_str()));
}
void Cmd::run_project(std::string args){ // ok
    this->build();
    check_error(system(
        (config->exe_file_path+ " "+args).c_str()
        ));

}

void Cmd::add(std::string star_path){ // ok
    this->check();
    std::string cmd(
        "mkdir -p "+config->home+"/stars/"+config->name+"/"+config->version+" "
    );
    log("[*] "+cmd);
    check_error(system(cmd.c_str()));
    cmd=(
        "cp -r "+config->root+"/* "+config->home+"/stars/"+config->name+"/"+config->version+"/ "
    );
    log("[*] "+cmd);
    check_error(system(cmd.c_str()));
    this->cat(config->name);
}

void Cmd::cat(std::string star){ //ok
    if(DirExists(config->home+"/stars/"+star)){
        log("["+star+"] all versions. ");
        for(auto _ : ls(config->home+"/stars/"+star)){
            log("\t--> "+_);
        }
    }else{
        log("[-] The ("+star+") not found.");
    }
}

void Cmd::list(){ // ok
    log("Stars in local ccao.  ["+config->home+"/stars]");
    for(auto _ : ls(config->home+"/stars")){
        log("\t--> "+_);
    }
}

void Cmd::remove(std::string star){ // ok
    if(DirExists(config->home+"/stars/"+star)){
        std::string cmd(
            "rm "+config->home+"/stars/"+star+" -r"
        );
        check_error(system(cmd.c_str()));
        log("[+] The ("+star+") remove Ok!");
    }else{
        log("[-] The ("+star+") not found.");
    }
}

void Cmd::remove(std::string star,std::string version){ // ok
    this->remove(star+"/"+version);
}

void Cmd::get(std::string star){
    std::string url = config->server+config->os+"/"+config->arch+"/"+star;
    // /star_name/last < version
    // std::string star_version = requst.get();
}

void Cmd::get(std::string star,std::string version){

}
