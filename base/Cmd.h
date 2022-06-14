#ifndef CCAO_BASE_CMD
#define CCAO_BASE_CMD
#include <string>
#include <vector>
#include <base/App.h>

class Cmd{
public:
    std::string op;
    std::vector<std::string> args;
    Cmd(int argc,char *argv[]);
    void check();
    void compare();
    void newproject(std::string project_name);// ccao new project_name
    void newapp(std::string app_name);// ccao new app app_name
    void build();// ccao build 
    void make();
    void clean();
    void install(std::string out_path);
    void show_help();// show help
    void version();
    void run_project(std::string args);
    void add(std::string star_path);
    void cat(std::string star);
    void get(std::string star);
    void get(std::string star,std::string version);
    void remove(std::string star);
    void remove(std::string star,std::string version);
    void list();
    
    

};


#endif