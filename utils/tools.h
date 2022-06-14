#ifndef CCAO_UTILS_TOOLS
#define CCAO_UTILS_TOOLS
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/stat.h> 
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <dirent.h>
#include <utils/colors.h>

// toml
#include <utils/toml.h>

// tools
std::string read_file(std::string file_path);
void c_mkdir(std::string path);
void check_error(int status);
void log(std::string msg);

std::vector<std::string> ls(std::string path);
std::vector<std::string> readlines_fromfile(std::string file_path);// here !
bool FileExists(std::string path);
bool DirExists(std::string path);
std::vector<std::string> split(std::string str, std::string pattern);
void DOWNLOAD(std::string url,std::string file_path);
void progress_bar(long int x,long int total);
std::string getipbydomain(std::string domain);
#endif