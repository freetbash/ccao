#include <base/App.h>
#include <public/vars.h>
#include <utils/tools.h>
#include <public/public.h>

App::App(std::string name){
    this->name = name;
    this->source = ls(config->root+"/source/"+name);
}
void App::build(){
        log(color("[*]Building ("+this->name+")",HIGH_LIGHT));
        std::string cmd;
        for(auto cc: ls(config->root+"/source/"+this->name)){
            cmd=(
                config->compiler
                +"-c "
                +config->root+"/source/"+this->name+"/"+cc+" "
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

Depend::Depend(std::string name_version){
    std::vector<std::string> temp = split(name_version,"\\$");
    if(temp.size()==2){
        if(DirExists(this->path)){
            this->name = temp[0];
            this->version = temp[1];
            // /home/bash/.ccao/stars/test_star/version_1
            // /home/bash/.ccao/stars/test_star/version_1/test_star
            this->path = config->home + "/stars/"+this->name + "/"+this->version;
            this->a = this->path +"/lib"+this->name+".a ";
        }else{
            std::cout << "please install "<< name_version <<std::endl;
            exit(123);
        }
    }else{
        std::cout << name_version << " error !"<<std::endl;
        exit(123);
    }
}