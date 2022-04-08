#ifndef CCAO_CLASSES_CMD
#define CCAO_CLASSES_CMD
#include <string>
#include <vector>
#include <App.h>
class Cmd{
public:
    std::string op;
    std::vector<std::string> args;
    Cmd(int argc,char *argv[]);
    void compare();
    void newproject(std::string project_name);// ccao new project_name
    void newapp(std::string app_name);// ccao new app app_name
    void newstar(std::string star_name);
    void build(App *main);// ccao build 
    void export_star();
    void clean();
    void install(std::string out_path);
    void show_help();// show help
    void version();
    void check_project();
    void check_star();
    void run_project();

};


#endif