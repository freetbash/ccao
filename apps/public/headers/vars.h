#ifndef CCAO_PUBLIC_VARS
#define CCAO_PUBLIC_VARS
#include <string>
#include <Cproject.h>
#include <Cconfig.h>
#include <Star.h>
extern bool debug;
extern std::string root;
extern std::string cflag;
extern std::string exe_file_path;
extern std::string extra_cflag;
extern std::string include_path;
extern std::string libray_path;
extern bool dynamic_app;
extern bool dynamic_depend;
extern bool cpp;
extern bool termux;
extern bool isProject;
extern bool isStar;
extern Cconfig *config;
extern Cproject *project;
extern Star     *star;
extern std::string help_text;
extern std::string home;
extern std::string compiler;
extern std::string server;
extern bool ccache;

#endif