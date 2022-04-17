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
            if(this->args[0] == "star"){
                std::cout<<"[-] You can't use the 'star' as your project_name"<<std::endl;
                std::cout<<"[*] (Tip~)$ ccao new star star_name"<<std::endl;
                exit(7);
            }
            this->newproject(this->args[0]);
            exit(7);
        }

            // new app
        if(this->args.size() == 2 and this->args[0] == "app"){
            this->check_project();
            this->newapp(this->args[1]);
            exit(8);
        }
        if(this->args.size() == 2 and this->args[0] == "star"){
            this->newstar(this->args[1]);
            exit(8);
        }
    }
    if(this->op == "help"){
        // 跳过就好
    }
    if(this->op == "run"){
        if(this->args.size()==0){
            this->check_project();
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
        this->check_project();
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
        this->check_project();
        this->build();
        exit(3);
    }
    if(this->op == "make"){
        this->check_star();
        star->make();
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
    if(this->op == "test"){
        this->check_star();
        if(this->args.size()==1){
            star->test("");
        }else{
            std::string args("");
            for(auto _:this->args){
                args+= _ +" ";
            }
            star->test(args);
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

void Cmd::check_project(){
    // 检查是否为 工程目录
    if(!isProject){
        std::cout<<"[-] You can't execute this operation, because this folder is not a Ccao project."<<std::endl;
        exit(-4);
    }
}
void Cmd::check_star(){
    // 检查是否为 工程目录
    if(!isStar){
        std::cout<<"[-] You can't execute this operation, because this folder is not a Ccao star."<<std::endl;
        exit(-4);
    }
}
void Cmd::show_help(){
    std::string help_text = 
        color("usage:",GREEN) +" ccao <command> [<args>]\n"
        +"Project commands:\n\t"
        +color("new project_name",BLUE)+"       // create a project\n\t"
        +color("build",YELLOW)+"                // build your all apps and your main function. Please check your debug of ccao.toml\n\t"
        +color("run arg1 arg2 args",YELLOW)+"   // build and run your app in debug or release\n\t"
        +color("clean",YELLOW)+"                // clean your previous build lib or files\n\t"
        +color("install",YELLOW)+"              // cp your target elf to /usr/local/bin/\n\t"
        +color("install /usr/local/bin/ /other/bin/",BLUE)+" // install your release to targer path\n\n"
        +"Star commands:\n\t"
        +color("add star_path",BLUE)+"          // add a star to ~/.ccao/stars // you can ccao add . \n\t"
        +color("get star",BLUE)+"               // get a star from internet\n\t"
        +color("get star version",BLUE)+"       // for a concrete version\n\t"
        +color("make",BLUE)+"                   // generate you star to out\n\t"
        +color("list",BLUE)+"                   // list your all installed stars\n\t"
        +color("cat star",BLUE)+"               // show you star's all version\n\t"
        +color("remove star",BLUE)+"            // remove a star but include all versions\n\t"
        +color("remove star version",BLUE)+"    // remove a targeted version star\n\t"
        +color("test",BLUE)+"                   // test star\n\n"
        
        +"Special with args:\n\t"
        +color("help",YELLOW)+"                  // print helpful text of ccao\n\t"
        +color("version",YELLOW)+"               // print the version of ccao\n\n"
        

        +color("Author:\n\tThis tool is made by Freet-Bash.\n\tIf you want to get into the development, please go to github or gitee and fork this repo.\n\tIf you have other problems ,please get in touch with me.\n\tHere is my email : 3141495167@qq.com\n",HIGH_LIGHT);
    std::cout<<help_text<<std::endl;
}

void Cmd::version(){
    std::cout<<"[*] ccao version "<<VERSION<<std::endl;
}

void Cmd::newproject(std::string project_name){
    std::string cwd;
    cwd = root + "/" + project_name;
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
    // out
    c_mkdir((cwd+"/out"));
        // debug
        c_mkdir((cwd+"/out/debug"));
        // release
        c_mkdir((cwd+"/out/release"));
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

void Cmd::clean(){
    if(isProject){
        system(
            ("rm -rf "+root+"/out ").c_str()
        );
        // out
        {
            c_mkdir((root+"/out"));
                c_mkdir((root+"/out/debug"));
                // release
                c_mkdir((root+"/out/release"));
        }
    }else if (isStar){
        system(
            ("rm -rf "+root+"/out ").c_str()
        );
        {
                c_mkdir(root+"/out");
                c_mkdir(root+"/out/package");
                c_mkdir(root+"/out/temp");
        }
    }else{
        log("[-] Here is not a project or star. ");
    }
    
}

void Cmd::install(std::string out_path){
    if(!FileExists(exe_file_path)){
        if(!debug){
        log(color("[*] elf not found , start build !",BLUE));
        this->build();
        }else{
            log(color("[-] you must be in release mode .",RED));
        }
    }
    system(("sudo cp "+exe_file_path+out_path).c_str());
    log(color("[+] "+out_path,GREEN));
}

void Cmd::newapp(std::string app_name){
 // 你打算 开发 new app
    std::string app_dir = root+"/apps/"+app_name;
    if (FileExists(app_dir)){
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

void Cmd::newstar(std::string star_name){
    std::string cwd;
    cwd = root + "/" + star_name;
    c_mkdir(cwd);
    c_mkdir(cwd+"/out");
    c_mkdir(cwd+"/headers");
    c_mkdir(cwd+"/source");
    c_mkdir(cwd+"/out/package");
    c_mkdir(cwd+"/test");

    std::ofstream star;
    star.open(cwd+"/star.toml",std::ios::out);
    std::stringstream fmt;
    {fmt << R""([star]
name=")""<<star_name<<R""("
author="root"
email=""
version="0"
ccache=false # 启用ccache 高速编译
cppversion="c++11"
cpp=true # g++ or gcc
cflag="-static "#额外参数 默认为空
depends=[
    #"test$0"
])"";}
    star << fmt.str();
    star.close();

    std::ofstream test;
    test.open(cwd+"/test/test.cpp",std::ios::out);
    std::stringstream ffmt;
    {ffmt << R""(#include <iostream>
int main(int argc, char const *argv[])
{
    // test code here !
    return 0;
}
)"";}
    test << ffmt.str();
    test.close();
}

void Cmd::build(){
    this->clean();
    // 将c cpp 路径 拼接到一起
    std::string link_file("");
    std::string source("");
    for(auto _ : project->apps){
        source+=_.path+"/source/* ";
        include_path+="-I"+_.path+"/headers ";
    }{
        source+=root+"/"+config->name+"/source/* ";
        include_path+="-I"+root+"/"+config->name+"/headers ";
        for(auto _:project->depends){
            include_path+="-I"+_.path+" ";
            link_file += _.a;
        }
    }
        

    std::string cmd(
        compiler
        +source
        +cflag
        +include_path
        +"-Xlinker '-(' "
        // -Xlinker "-("  /home/bash/projects/chameleon/out/debug/libs/own/libviews.a -Xlinker "-)" 
        +link_file
        +"-Xlinker '-)' "
        +"-o "
        +exe_file_path
        +extra_cflag
    );
    log("[*] "+cmd);
    int status;
    status = system(cmd.c_str());
    if(status != 0){
            exit(status);
    }
    log(
            "[+]Build Ok!  It is here { \n\t"+color(exe_file_path,GREEN)+" \n} "
    );
}
void Cmd::run_project(std::string args){
    this->build();
    system(
        (exe_file_path+ " "+args).c_str()
        );

}

void Cmd::add(std::string star_path){
    std::string star_ = star_path + "/star.toml";
    if(!FileExists(star_)){
        log("[-] your path is not for star!");
        exit(1);
    }
    std::string star_name;
    std::string star_version;
    const toml::value data=toml::parse(star_);
    // 配置[project]
    const auto star_data = toml::find(data,"star");
    star_name = toml::find
        <std::string>
    (star_data,"name");

    star_version = toml::find
        <std::string>
    (star_data,"version");

    std::string cmd(
        "mkdir -p "+home+"/stars/"+star_name+"/"+star_version+" "
    );
    log("[*] "+cmd);
    system(cmd.c_str());
    cmd=(
        "cp -r "+star_path+"/* "+home+"/stars/"+star_name+"/"+star_version+"/ "
    );
    log("[*] "+cmd);
    system(cmd.c_str());
    this->cat(star_name);
}
void Cmd::cat(std::string star){
    if(DirExists(home+"/stars/"+star)){
        log("["+star+"] all versions. ");
        for(auto _ : ls(home+"/stars/"+star)){
            log("\t--> "+_);
        }
    }else{
        log("[-] The ("+star+") not found.");
    }
}
void Cmd::list(){
    log("Stars in local ccao.  ["+home+"/stars]");
    for(auto _ : ls(home+"/stars")){
        log("\t--> "+_);
    }
}
void Cmd::remove(std::string star){
    if(DirExists(home+"/stars/"+star)){
        std::string cmd(
            "rm "+home+"/stars/"+star+" -r"
        );
        system(cmd.c_str());
        log("[+] The ("+star+") remove Ok!");
    }else{
        log("[-] The ("+star+") not found.");
    }
}
void Cmd::remove(std::string star,std::string version){
    this->remove(star+"/"+version);
}

void Cmd::get(std::string star){

}
void Cmd::get(std::string star,std::string version){

}
