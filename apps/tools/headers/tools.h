#ifndef _CCAO_TOOLS__H
#define _CCAO_TOOLS__H
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/stat.h> 
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <dirent.h>
// tools
void start();
void c_mkdir(std::string path);
void check_error(int status);
void log(std::string msg);
std::vector<std::string> ls(std::string path);
bool file_exist(std::string filename);

#endif