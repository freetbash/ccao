#include <tools.h>
// tools
std::vector<std::string> ls(std::string path){
    DIR *dp;
    std::vector<std::string> dirs;
    struct dirent *dirp;
    char dirname[256];

    if(
        (dp=opendir(path.c_str())) == NULL)
    {
        log(path);
        std::cout << "[-]List files failed . \n[-]Please check your permissions. "<<std::endl;
        exit(-2);
    }

    while (
        ((dirp=readdir(dp))!=NULL)
    )
    {
        if(
            (dirp->d_name != std::string(".") and dirp->d_name != std::string(".."))
        ){
            dirs.push_back(dirp->d_name);
        }
    }
    closedir(dp);
    return dirs;
}

void start(){
    if(
        !(access(get_current_dir_name(),W_OK) == 0 )
    ){
        std::cout<<"[-] Please ensure you are root or sudors ,because you don't have access to operate this folder"<<std::endl;
        exit(-3);
    }
}

void c_mkdir(std::string path){
    mkdir(path.c_str(),0775);
}

void check_error(int status){
    if(status<0){
        std::cout<<"[-] "<<strerror(errno)<<std::endl;
        exit(-99);
    }
}

void log(std::string msg){
    std::cout<<msg<<std::endl;
}




bool FileExists(std::string path)
{
    struct stat fileStat; 
    if ( stat(path.c_str(), &fileStat) )
    {
        return false;
    }
    if ( !S_ISREG(fileStat.st_mode) )
    {
        return false;
    }
    return true;
}

bool DirExists(std::string path)
{
    struct stat fileStat;
    if ( stat(path.c_str(), &fileStat) )
    {
        return false;
    }
    if ( !S_ISDIR(fileStat.st_mode) )
    {
        return false;
    }
    return true;
}