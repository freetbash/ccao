#ifndef __CCAO__H
// other h
#include <vector>
#include <string>


#define __CCAO__H
#define APP 1
#define DEPEND 0

class DataSet{
public:
    Cconfig *config;
    Cproject *project;
    DataSet(Cproject *project,Cconfig *config);
};

class Cconfig{
public:
    // attributes
    bool cpp;
    bool debug;
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
    Cproject(Cconfig config);
};



std::vector<std::string> ls(std::string path);

class Cmd{
public:
    std::string op;
    std::vector<std::string> args;
    DataSet *dsp;
    Cmd(int argc,char *argv[],DataSet *dsp);
    void compare();
    void newproject(DataSet *dsp);// ccao new project_name
    void newapp(DataSet *dsp);// ccao new app app_name
    void build(DataSet *dsp);// ccao build && ccao build release
    void collect_depends(DataSet *dsp);// ccao collect
};

#endif