#include "../include/Ccao.h"
#include <iostream>
int main(int argc, char *argv[]){
    Cconfig config;
    Cproject project(config);
    DataSet *dsp;
    dsp->config=&config;
    dsp->project=&project;
    
    Cmd cmd = Cmd(argc,argv);
    // argc 传递有问题
    cmd.compare();
}