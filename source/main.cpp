#include "../include/Ccao.h"
#include <iostream>


int main(int argc, char *argv[]){
    CONFIG();
    if(isProject){
        PROJECT();
    }

    Cmd cmd = Cmd(argc,argv);
    // argc 传递有问题
    cmd.compare();
}