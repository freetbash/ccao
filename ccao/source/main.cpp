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
    
    if(cpp==true){
        if(termux){
            compiler="aarch64-linux-gnu-g++ ";
        }else{
            compiler="g++ ";
        }
    }else{
        if(termux){
            compiler="aarch64-linux-gnu-gcc ";
        }else{
            compiler="gcc ";
        }
    }
    if(ccache){compiler = "ccache "+compiler;}
    server = read_file(home+"/server");

    Cmd cmd = Cmd(argc,argv);
    // argc 传递有问题
    cmd.compare();
}
void init(){
    printf("[*] Initing..... CCAO\n");

    c_mkdir(home);
    system(
        ("echo 'http://82.157.65.112:3147/' >"+home+"/server").c_str()
    );
    c_mkdir(home+"/stars");
}