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
    // 你打算 完成这个函数
    
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