#include <base/Cmd.h>
#include <utils/tools.h>
#include <utils/system.h>
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
        }else if(this->args.size()==0){
            log(color("[-] ccao remove star ",RED));
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
    if(this->op == "test"){
        if(this->args.size()==0){
            this->test();
        }else{
            this->test(this->args);
        }
        exit(12);
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
    c_mkdir(cwd+"/source/"+project_name);
    c_mkdir(cwd+"/temp");
    c_mkdir(cwd+"/test");
    c_mkdir(cwd+"/bin");
    c_mkdir(cwd+"/bin/test");
    
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
version="0"
cppversion="c++11"
debug=true
cflag="-static "#额外参数 默认为空
compiler="g++"
ccache=false # 启用ccache 高速编译
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
            ("rm -rf "+config->root+"/temp/* ").c_str()
        ));
    }else{
        log("[-] Here is not a project or star. ");
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

    {
        log(color("[*]Building ("+config->name+")",HIGH_LIGHT));
        std::string cmd;
        std::vector<std::string> *_ = new std::vector<std::string>;
        all_files(_,config->root+"/source/"+config->name);
        for(auto cc: *_){
            cmd=(
                config->compiler
                +"-c "
                +cc+" "
                +config->include_path
                +"-o "
                +config->root+"/temp/"+split(cc,"\\/").back()+".o "
                +config->cflag
                +config->extra_cflag
            );
            log("[*] "+cmd);
            check_error(system(cmd.c_str()));
        }
        free(_);
    }

    for(App app:project->apps){
        app.build();
    }

    {
        cmd=(config->compiler+"-c main.cpp "+config->include_path+"-o "+config->root+"/temp/main.o "+config->cflag+config->extra_cflag);
        log("[*] "+cmd);
        check_error(system(cmd.c_str()));
    }
    cmd=(
        config->compiler
        +config->root+"/temp/* "
        +config->include_path
        +"-Xlinker '-(' "
        // -Xlinker "-("  /home/bash/projects/chameleon/out/debug/libs/own/libviews.a -Xlinker "-)" 
        +link_file
        +"-Xlinker '-)' "
        +"-o "
        +config->exe_file_path
        +" "
        +config->cflag
        +config->extra_cflag
    );
    log("[*] "+cmd);
    check_error(system(cmd.c_str()));
    log(
            "[+]Build Ok!  It is here { \n\t"+color(config->exe_file_path,GREEN)+" \n} "
    );
    check_error(system("rm temp/main.o"));
}

void Cmd::make(){ // ok
    this->check();
    std::string link_file("");
    std::string cmd;
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

    for(App app:project->apps){
        app.build();
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
    if(FileExists(star_path+"/ccao.toml")){
        const toml::value _ = toml::parse(star_path+"/ccao.toml");
        const auto data = toml::find(_,"project");
        std::string version = toml::find<std::string>(data,"version");
        std::string name = toml::find<std::string>(data,"name");
        std::string cmd(
            "mkdir -p "+config->home+"/stars/"+name+"/"+version+" "
        );
        log("[*] "+cmd);
        check_error(system(cmd.c_str()));
        cmd=(
            "cp -rf "+star_path+" "+config->home+"/stars/"+name+"/"+version+"/ "
        );
        log("[*] "+cmd);
        check_error(system(cmd.c_str()));
        this->cat(name);
    }else{
        log("[-] "+star_path+" is not a ccao project!");
    }
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
            "rm "+config->home+"/stars/"+star+" -rf"
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

void Cmd::test(std::string path){
    this->check();
    this->make();
    log(color("[*]Testing ("+path+") ",BLUE));
    std::string cmd("");
    cmd=(
        config->compiler
        +config->root+"/test/"+path+" -I. "
        +"-Xlinker '-(' "
        // -Xlinker "-("  /home/bash/projects/chameleon/out/debug/libs/own/libviews.a -Xlinker "-)" 
        +config->root+"/bin/lib"+config->name+".a "
        +"-Xlinker '-)' "
        +"-o "
        +config->root+"/bin/test/"+path+".out -g -Wall -std="
        +config->cppversion
    );
    log("[*] "+cmd);
    check_error(system(cmd.c_str()));
    cmd=config->root+"/bin/test/"+path+".out ";
    log("[*] "+cmd);
    check_error(system(cmd.c_str()));
}

void Cmd::test(std::vector<std::string> paths){
    for(std::string path : paths){
        this->test(path);
    }
}

void Cmd::test(){
    for(std::string each : ls(config->root+"/test")){
        this->test(each);
    }
}
