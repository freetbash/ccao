#ifndef __CCAO__H
// other h
#include <vector>
#include <string>

// error id -5
// Ok id 8
#define __CCAO__H
#define APP 1
#define DEPEND 0
#define VERSION "0.01"



class Cconfig{
public:
    // attributes
    // root or debug 在Ccao.cpp中
    std::string name;
    std::string cppversion;
    std::vector<std::string> apps;
    std::vector<std::string> depends;
    // methods    

};
void CONFIG();


class App{
public:
    // attributes
    int type;
    bool blank;
    std::string name;
    std::string path;
    std::string out_path;
    std::vector<std::string> headers;
    std::vector<std::string> source;

    // methods
    App();
    
    App(std::string name,int type);
    void build(
        std::string cflag,
        std::string include_path,
        std::string library_path
    );// 构建自己
};
App *MAIN();


class Cproject {
public:
    // attributes
    App *main;// 判断main的目录 为不为空 为空 就提示将不会创建 可执行文件
    std::vector<App> apps;
    std::vector<App> depends;
    // methods
};
void PROJECT();


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
    void show_help();// show help
    void version();
    void export_app();
    void export_prokect();// 必须是动态链接库
    void check_status();

};
// tools
void start();
void c_mkdir(std::string path);
void check_error(int status);
void log(std::string msg);
std::vector<std::string> ls(std::string path);
bool file_exist(std::string filename);


// 一部分 设置 放在这里好调用
extern bool debug;
extern std::string root;
extern bool dynamic_app;
extern bool dynamic_depend;
extern bool cpp;
extern bool isProject;
extern Cconfig *config;
extern Cproject *project;
#endif