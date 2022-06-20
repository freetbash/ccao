#include <utils/system.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

bool isDir(std::string path){
    struct stat st;
    lstat(path.c_str(),&st);
    return (0 != S_ISDIR(st.st_mode));
}


bool FDExist(std::string path){
    if(access(path.c_str(),F_OK)!=-1){
        return true;
    }else{
        return false;
    }
}

std::vector<std::string> list_files(std::string path){
    std::vector<std::string> temp;
    DIR *dir = opendir(path.c_str());
    struct dirent *dp;
    while((dp=readdir(dir))!=NULL){
        if(dp->d_name != std::string(".") and dp->d_name != std::string("..")){
            temp.push_back(dp->d_name);
        }
    }
    closedir(dir);
    return temp;
}

void all_files(std::vector<std::string> *files,std::string path){
        for(std::string _ : list_files(path)){
            if(isDir(path+"/"+_)){
                all_files(files,path+"/"+_);
            }else{
                files->push_back(path+"/"+_);
            }
        }
}