#ifndef __CCAO_CMD__H
#define __CCAO_CMD__H
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
    void build(App *main);// ccao build 
    void collect_depends();// ccao collect????? 还未开发
    void clean();
    void show_help();// show help
    void version();
    void export_apps_to_stars(App *target, int type);// stars 仅仅是源码 应该再写一种 可以导出 库的 code lib
    void export_project();// 必须是动态链接库
    void check_status();

};


#endif