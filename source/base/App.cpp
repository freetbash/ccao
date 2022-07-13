#include <base/App.h>
#include <public/vars.h>
#include <utils/tools.h>
#include <utils/system.h>
#include <public/public.h>

App::App(std::string name){
    this->name = name;
    this->source = ls(config->root+"/source/"+name);
}
void App::build(){
        log(color("[*]Building ("+this->name+")",HIGH_LIGHT));
        std::string cmd;
        std::vector<std::string> *_ = new std::vector<std::string>;
        all_files(_,config->root+"/source/"+this->name);
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

Depend::Depend(std::string name_version){
    std::vector<std::string> temp = split(name_version,"\\$");
    this->path = config->home + "/stars/"+this->name + "/"+this->version;
    if(temp.size()==2){
        if(FDExist(this->path)){
            this->name = temp[0];
            this->version = temp[1];
            // /home/bash/.ccao/stars/test_star/version_1
            // /home/bash/.ccao/stars/test_star/version_1/test_star
            this->path = config->home + "/stars/"+this->name + "/"+this->version;
            this->a = this->path +"/"+this->name+"/bin/lib"+this->name+".a ";
        }else{
            std::cout << "please install "<< name_version <<std::endl;
            exit(123);
        }
    }else{
        std::cout << name_version << " error !"<<std::endl;
        exit(123);
    }
}