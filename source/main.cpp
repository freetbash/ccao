#include "../include/Ccao.h"
#include <iostream>
int main(int argc, char *argv[]){
    Cconfig config;
    DataSet *dsp=NULL;
    if(config.isProject){
        Cproject project(&config);
        dsp=new DataSet(&project,&config);
    }

    Cmd cmd = Cmd(argc,argv,dsp);
    // argc 传递有问题
    cmd.compare();
}