#include <main.h>
#include <public/vars.h>

void config_init(){
    printf("[*] Initing..... CCAO\n");

    c_mkdir(config->home);
    check_error(system(
        ("echo 'http://127.0.0.1:3147/' >"+config->home+"/server").c_str()
    ));
    c_mkdir(config->home+"/stars");
    c_mkdir(config->home+"/temp");
}
void init(){
    config = new Config;
    project = new Project;
    config->home =std::string(getenv("HOME"))+"/.ccao";
    if(!DirExists(config->home)){
        config_init();
    }
    CONFIG();
}