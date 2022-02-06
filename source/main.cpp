#include "../include/Ccao.h"
#include <iostream>
int main(int argc, char *argv[]){
    std::cout<<argc<<std::endl;
    Cmd cmd = Cmd(argc,argv);
    DataSet *dsp=NULL;
    // argc 传递有问题
    cmd.compare();
}