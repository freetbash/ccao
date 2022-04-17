#ifndef CCAO_CLASSES_CMD
#define CCAO_CLASSES_CMD
#include <string>
#include <vector>
#include <App.h>
#include <Star.h>
class Cmd{
public:
    std::string op;
    std::vector<std::string> args;
    Cmd(int argc,char *argv[]);
    void compare();
    void newproject(std::string project_name);// ccao new project_name
    void newapp(std::string app_name);// ccao new app app_name
    void newstar(std::string star_name);
    void build();// ccao build 
    void clean();
    void install(std::string out_path);
    void show_help();// show help
    void version();
    void check_project();
    void check_star();
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