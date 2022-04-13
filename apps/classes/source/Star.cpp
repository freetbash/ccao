#include <Star.h>
#include <tools.h>
#include <vars.h>
void Star::make(){
    std::string cmd;
    std::cout << "Start build Star" <<this->name<<std::endl;
    c_mkdir(root+"/out/temp");
    cmd="cp "+root+"/star.toml "+root+"/out/package/";
    system(cmd.c_str());
    c_mkdir(root+"/out/package/libs");
    cmd ="cp "+root+"/headers "+root+"/out/package -r";
    system(cmd.c_str());
    // g++ 
    std::string _include("");
    std::string _libs("-( ");
    // '-(' /home/bash/projects/ccao/out/debug/libs/other/libtoml.a /home/bash/projects/ccao/out/debug/libs/other/libcolorstring.a /home/bash/projects/ccao/out/debug/libs/own/libpublic.a /home/bash/projects/ccao/out/debug/libs/own/libclasses.a /home/bash/projects/ccao/out/debug/libs/own/libtools.a -Xlinker '-)'
    for(auto _ :this->depends){
        // for include
        _libs += ("-l"+_+" ");
    } // -lasd -lasd -lasdc


    cmd="rm "+root+"/out/temp -rf";
    system(cmd.c_str());
}