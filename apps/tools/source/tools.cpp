#include <tools.h>
// tools
#include <regex>

std::string read_file(std::string file_path){
    std::ifstream in(file_path);
    std::ostringstream tmp;
    tmp << in.rdbuf();
    return tmp.str();
}
std::vector<std::string> ls(std::string path){
    DIR *dp;
    std::vector<std::string> dirs;
    struct dirent *dirp;

    if(
        (dp=opendir(path.c_str())) == NULL)
    {
        log(path);
        std::cout << "[-]List files failed . \n[-]Please check your permissions. "<<std::endl;
        exit(-2);
    }

    while (
        ((dirp=readdir(dp))!=NULL)
    )
    {
        if(
            (dirp->d_name != std::string(".") and dirp->d_name != std::string(".."))
        ){
            dirs.push_back(dirp->d_name);
        }
    }
    closedir(dp);
    return dirs;
}

void c_mkdir(std::string path){
    mkdir(path.c_str(),0775);
}

void check_error(int status){
    if(status!=0){
        exit(-99);
    }
}

void log(std::string msg){
    std::cout<<msg<<std::endl;
}




bool FileExists(std::string path)
{
    struct stat fileStat; 
    if ( stat(path.c_str(), &fileStat) )
    {
        return false;
    }
    if ( !S_ISREG(fileStat.st_mode) )
    {
        return false;
    }
    return true;
}

bool DirExists(std::string path)
{
    struct stat fileStat;
    if ( stat(path.c_str(), &fileStat) )
    {
        return false;
    }
    if ( !S_ISDIR(fileStat.st_mode) )
    {
        return false;
    }
    return true;
}

std::vector<std::string> split(std::string s, std::string d) { 
	std::string text = s;
	std::regex ws_re(d); 
	// whitespace 
	std::vector<std::string> tokens(std::sregex_token_iterator(text.begin(), text.end(), ws_re, -1), std::sregex_token_iterator()); 
	return tokens;
}
std::vector<std::string> readlines_fromfile(std::string file_path){
    std::vector<std::string> temp;
    std::string query;
    std::ifstream in(file_path);
    while (getline(in,query))
    {
        temp.push_back(query);
    }
    return temp;
}