#ifndef CCAO_BASE_CCONFIG
#define CCAO_BASE_CCONFIG
#include <string>
#include <vector>

class Config{
public:
    // attributes
    std::string name;
    std::string root;
    bool is_project;
    bool debug;
    bool cpp;
    bool termux;
    bool ccache;
    std::string cflag;
    std::string exe_file_path;
    std::string extra_cflag;
    std::string include_path;
    std::string compiler;
    std::string arch;
    std::string os;
    // star
    std::string home;
    std::string version;
    std::string server;
    std::string cppversion;
    // methods    

};
void CONFIG();


#endif