#include <tools.h>
// tools
std::vector<std::string> ls(std::string path){
    DIR *dp;
    std::vector<std::string> dirs;
    struct dirent *dirp;

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

std::vector<std::string> split(std::string str, std::string pattern){
    std::vector<std::string> res;
    if(str == "")
        return res;
    //在字符串末尾也加入分隔符，方便截取最后一段
    std::string strs = str + pattern;
    size_t pos = strs.find(pattern);

    while(pos != strs.npos)
    {
        std::string temp = strs.substr(0, pos);
        res.push_back(temp);
        //去掉已分割的字符串,在剩下的字符串中进行分割
        strs = strs.substr(pos+1, strs.size());
        pos = strs.find(pattern);
    }

    return res;
}