#ifndef CCAO_TOOLS_TOOLS
#define CCAO_TOOLS_TOOLS
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/stat.h> 
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <dirent.h>
#include <colors.h>
// toml
#include <toml.h>

// tools
void c_mkdir(std::string path);
void check_error(int status);
void log(std::string msg);

std::vector<std::string> ls(std::string path);
std::vector<std::string> readlines_fromfile(std::string file_path);// here !
bool FileExists(std::string path);
bool DirExists(std::string path);
std::vector<std::string> split(std::string str, std::string pattern);

#endif