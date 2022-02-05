#include "../include/Ccao.h"
#include <unistd.h>
#include <dirent.h>
#include <iostream>

Cproject::Cproject(){
    char *path = get_current_dir_name();
    
    if(path!=NULL){
        this->cwd=path;
    }else{
        std::cout<<"[-]Your absolute path isn't setted successfully!\n [-]Please check your permissions. "<<std::endl;
        exit(-1);
    }
}

App::App(std::string name,std::string cwd){
    std::vector<std::string> headers;
    std::vector<std::string> source;
    std::vector<std::string> temp;
    
    this->name = name;
    headers = ls(cwd+"apps"+name+"headers");
    source = ls(cwd+"apps"+name+"source");

    // 判断目录为不为空
    if(
        (headers.size() == 2) and (source.size() == 2)
    ){
        this->blank=true;
    }else{
        // 删除 . 以及 ..
        headers.erase(headers.begin(),headers.begin()+2);
        source.erase(source.begin(),source.begin()+2);
        
        this->blank=false;
        this->headers=headers;
        this->source=source;
    }






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
        dirs.push_back(dirp->d_name);
    }
    closedir(dp);
    return dirs;
}