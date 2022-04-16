#include <main.h>
#include <stdio.h>
#include <stdlib.h>// tdm
int main(int argc, char *argv[]){
    home =std::string(getenv("HOME"))+"/.ccao";
    if(!DirExists(home)){
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

    c_mkdir(home);
    
    c_mkdir(home+"/stars");
}