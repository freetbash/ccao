#include <main.h>
#include <stdio.h>
#include <stdlib.h>// tdm
Config *config;
Project *project;
int main(int argc, char *argv[]){
    init();
    Cmd cmd = Cmd(argc,argv);
    cmd.compare();
}
