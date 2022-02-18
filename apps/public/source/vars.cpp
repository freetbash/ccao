#include <string>
#include <Cproject.h>
#include <Cconfig.h>

bool debug;
std::string root;
std::string cflag;
std::string extra_cflag;
std::string libflag;
std::string link_file;// 借用头文件目录添加的操作 添加库
std::string include_path;
std::string libray_path;
bool dynamic_app;
bool dynamic_depend;
bool cpp;
bool isProject;
Cconfig *config;
Cproject *project;
std::string help_text;