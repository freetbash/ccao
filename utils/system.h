#ifndef CCAO_UTILS_SYSTEM
#define CCAO_UTILS_SYSTEM
#include <string>
#include <vector>

bool isDir(std::string path);
bool FDExist(std::string path);
std::vector<std::string> list_files(std::string path);
void all_files(std::vector<std::string> *files,std::string path);




#endif