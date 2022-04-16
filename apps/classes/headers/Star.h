#ifndef CCAO_CLASSES_STAR
#define CCAO_CLASSES_STAR
#include <string>
#include <vector>
class Star{
public:
    std::string version;
    std::string cppversion;
    std::string name;
    std::vector<std::string> depends;
    void make();
    void test(std::string args);
};


#endif