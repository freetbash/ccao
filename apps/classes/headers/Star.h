#ifndef CCAO_CLASSES_STAR
#define CCAO_CLASSES_STAR
#include <string>
#include <vector>
class Star{
public:
    int version;
    std::string name;
    std::vector<std::string> depends;
    void make();
};


#endif