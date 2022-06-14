#ifndef CCAO_BASE_APP
#define CCAO_BASE_APP
#include <string>
#include <vector>
class App{
public:
    // attributes
    std::string name;
    std::vector<std::string> source;
    App(std::string name);
    void build();

};
class Depend{
public:
    std::string name;
    std::string path;
    std::string version;
    std::string a;
    Depend(std::string name_version);
};
#endif