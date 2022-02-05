#ifndef __CCAO__H
// other h
#include <vector>
#include <string>


#define __CCAO__H

class App{
public:
    // attributes
    bool blank;
    std::string name;
    std::vector<std::string> headers;
    std::vector<std::string> source;

    // methods
    App(std::string name,std::string cwd);
};


class Cproject {
public:
    // attributes
    bool debug;
    std::string name;
    std::string cppversion;
    std::string cwd;
    std::vector<App> apps;
    std::vector<App> depends;

    // methods
    Cproject();
};



std::vector<std::string> ls(std::string path);

#endif