#include <App.h>
#include <vars.h>
#include <tools.h>
#include <public.h>

App::App(std::string name){
    this->name = name;
    this->path = root+"/apps/"+name;
}

Depend::Depend(std::string name_version){
    auto temp = split(name_version,"$");
    if(temp.size()==2){
        this->name = temp[0];
        this->version = temp[1];
        this->path = home + "/stars/"+this->name + "/"+this->version;
        if(DirExists(this->path)){
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