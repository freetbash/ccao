#ifndef CCAO_PUBLIC_VARS
#define CCAO_PUBLIC_VARS
#include <string>
#include <Cproject.h>
#include <Cconfig.h>

extern bool debug;
extern std::string root;
extern std::string cflag;
extern std::string extra_cflag;
extern std::string libflag;
extern std::string link_file;// 借用头文件目录添加的操作 添加库
extern std::string include_path;
extern std::string libray_path;
extern bool dynamic_app;
extern bool dynamic_depend;
extern bool cpp;
extern bool isProject;
extern Cconfig *config;
extern Cproject *project;
extern std::string help_text;

#endif