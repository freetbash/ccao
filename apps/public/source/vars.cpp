#include <string>
#include <Cproject.h>
#include <Cconfig.h>
#include <Star.h>
bool debug;
std::string root;
std::string cflag;
std::string extra_cflag;
std::string libflag;
std::string link_file;// 借用头文件目录添加的操作 添加库
std::string include_path;
std::string libray_path;
bool isProject;
bool isStar;
Cconfig *config;
Cproject *project;
Star *star;
std::string help_text;