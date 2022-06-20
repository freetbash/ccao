#include <utils/system.h>
#include <sys/dir.h>
#include <sys/stat.h>
bool isDir(std::string path){
    struct stat st;
    lstat(path.c_str(),&st);
    return (0 != S_ISDIR(st.st_mode));
}


bool isFile(std::string path){
    return !isDir(path);
}
