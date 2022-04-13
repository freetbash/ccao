#include <main.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
    std::string home(getenv("HOME"));
    if(!DirExists(home+"/.ccao")){
        init();
    }
    CONFIG();
    if(isProject){
        PROJECT();
    }

    Cmd cmd = Cmd(argc,argv);
    // argc 传递有问题
    cmd.compare();
}
void init(){
    printf("[*] Initing..... CCAO\n");
    std::string home(getenv("HOME"));

    c_mkdir(home+"/.ccao");
    system(("touch "+home+"/.ccao/index").c_str());
    c_mkdir(home+"/.ccao/stars");
    c_mkdir(home+"/.ccao/stars/headers");
    c_mkdir(home+"/.ccao/stars/libs");

}