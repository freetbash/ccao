#include <utils/system.h>
#include <utils/tools.h>

int main(int argc, char const *argv[])
{
    /* code */

    if(isDir("/home/bash/cw")){
        log("cw");
    }
    if(FDExist("/home/bash/Projects/ccao/bin")){
        log("ok");
    }
    std::vector<std::string> *temp= new std::vector<std::string>;
    all_files(temp,"/home/bash/Projects/ccao/source");
    for(auto _ : *temp){
        log(_);
    }
    log(split("/home/asdasd/adasd.cpp","\\/").back());
    
    return 0;
}
