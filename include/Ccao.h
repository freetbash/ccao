#ifndef __CCAO__H
// other h
#include <vector>
#include <string>

// error id -4
// Ok id 9
#define __CCAO__H
#define APP 1
#define DEPEND 0
#define VERSION "0.01"



class Cconfig{
public:
    // attributes
    bool cpp;
    bool debug;
    bool isProject;
    std::string root;
    std::string name;
    std::string cppversion;
    std::vector<std::string> apps;
    std::vector<std::string> depends;
    // methods
    Cconfig();
};


class App{
public:
    // attributes
    int type;
    bool blank;
    std::string name;
    std::vector<std::string> headers;
    std::vector<std::string> source;

    // methods
    App();
    App(std::string name,std::string root,int type);
};


class Cproject {
public:
    // attributes
    App main;
    std::vector<App> apps;
    std::vector<App> depends;
    Cconfig *config;
    // methods
    Cproject(Cconfig *config);
};

class DataSet{
public:
    Cconfig *config;
    Cproject *project;
    DataSet(Cproject *project,Cconfig *config);
};


class Cmd{
public:
    std::string op;
    std::vector<std::string> args;
    DataSet *dsp;
    Cmd(int argc,char *argv[],DataSet *dsp);
    void compare();
    void newproject(std::string project_name);// ccao new project_name
    void newapp(std::string app_name);// ccao new app app_name
    void build();// ccao build 
    void collect_depends();// ccao collect
    void show_help();// show help
    void version();
    void export_app();
    void check_status();

};
// tools
void start();
void check_error(int status);
void log(std::string msg);
std::vector<std::string> ls(std::string path);
bool file_exist(std::string filename);
#endif