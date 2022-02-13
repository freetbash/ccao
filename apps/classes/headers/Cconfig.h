#ifndef __CCAO_CONFIG__H
#define __CCAO_CONFIG__H
#include <string>
#include <vector>

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


#endif