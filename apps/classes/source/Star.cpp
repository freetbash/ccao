#include <Star.h>
#include <tools.h>
#include <vars.h>
void Star::make(){
    std::string cmd;
    std::cout << "Start build Star" <<this->name<<std::endl;
    cmd="rm "+root+"/temp/*";
    system(cmd.c_str());
    cmd="cp "+root+"/star.toml "+root+"/out/package/";
    system(cmd.c_str());
    c_mkdir(root+"/out/package/libs");
    cmd ="cp "+root+"/headers "+root+"/out/package -r";
    system(cmd.c_str());
}