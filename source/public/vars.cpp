#include <string>
#include <base/Project.h>
#include <base/Config.h>
#include <utils/colors.h>

std::string HTTP_VERSION="HTTP/1.1";
std::string HTTP_DELIM="\r\n";

std::string help_text = 
        color("usage:",GREEN) +" ccao <command> [<args>]\n"
        +"Project commands:\n\t"
        +color("new project_name",BLUE)+"       // create a project\n\t"
        +color("build",YELLOW)+"                // build your all apps and your main function. Please check your debug of ccao.toml\n\t"
        +color("run arg1 arg2 args",YELLOW)+"   // build and run your app in debug or release\n\t"
        +color("clean",YELLOW)+"                // clean your previous build lib or files\n\t"
        +"Star commands:\n\t"
        +color("add star_path",BLUE)+"          // add a star to ~/.stars // you can ccao add . \n\t"
        +color("get star",BLUE)+"               // get a star from internet\n\t"
        +color("get star version",BLUE)+"       // for a concrete version\n\t"
        +color("list",BLUE)+"                   // list your all installed stars\n\t"
        +color("cat star",BLUE)+"               // show you star's all version\n\t"
        +color("remove star",BLUE)+"            // remove a star but include all versions\n\t"
        +color("remove star version",BLUE)+"    // remove a targeted version star\n\t"
        
        +"Special with args:\n\t"
        +color("help",YELLOW)+"                  // print helpful text of ccao\n\t"
        +color("version",YELLOW)+"               // print the version of ccao\n\n"
        

        +color("Author:\n\tThis tool is made by Freet-Bash.\n\tIf you want to get into the development, please go to github or gitee and fork this repo.\n\tIf you have other problems ,please get in touch with me.\n\tHere is my email : 3141495167@qq.com\n",HIGH_LIGHT);