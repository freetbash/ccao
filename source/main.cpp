#include "../include/Ccao.h"
#include <iostream>
int main(int argc, char *argv[]){
    Cmd cmd = Cmd(argc,argv);
    DataSet *dsp=NULL;
    std::cout<<"123"<<std::endl;\
    // argc 传递有问题
    cmd.compare();
}