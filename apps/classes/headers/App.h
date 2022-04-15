#ifndef CCAO_CLASSES_APP
#define CCAO_CLASSES_APP
#include <string>
#include <vector>
class App{
public:
    // attributes
    std::string name;
    std::string path;
    App(std::string name);

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