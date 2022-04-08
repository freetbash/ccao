#include <main.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
    std::string home(getenv("HOME"));
    bool isInit = !file_exist(home)+"/.ccao";
        printf("%d\n",isInit);
    if(isInit){
        init();
    }
    CONFIG();
    if(isProject){
        printf("project\n");
        PROJECT();
    }

    Cmd cmd = Cmd(argc,argv);
    // argc 传递有问题
    cmd.compare();
}
void init(){
    printf("init\n");
    std::string home(getenv("HOME"));

    c_mkdir(home+"/.ccao");
    c_mkdir(home+"/.ccao/index");
    c_mkdir(home+"/.ccao/stars");
    c_mkdir(home+"/.ccao/stars/headers");
    c_mkdir(home+"/.ccao/stars/libs");

}