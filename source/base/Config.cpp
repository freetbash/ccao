#include <base/Config.h>
#include <public/vars.h>
#include <utils/tools.h>
#include <sys/utsname.h>

void CONFIG(){
    // init root
    char *root = get_current_dir_name();
    if (root != NULL){
        config->root = root;
    }else{
        std::cout << "[-]Your absolute path isn't setted successfully!\n [-]Please check your permissions. " << std::endl;
        exit(-1);
    }


    // config
    std::string ccao = config->root + "/ccao.toml";
    config->is_project = FileExists(ccao);
    if(config->is_project){
        const toml::value data = toml::parse(ccao);
        const auto project_data = toml::find(data, "project");
        config->name = toml::find<std::string>(project_data, "name");
        config->version = toml::find<std::string>(project_data, "version");
        config->debug = toml::find<bool>(project_data, "debug");
        config->cppversion = toml::find<std::string>(project_data, "cppversion");
        config->extra_cflag = toml::find<std::string>(project_data, "cflag");
        config->compiler = toml::find<std::string>(project_data,"compiler");
        config->compiler+=" ";
        config->ccache = toml::find<bool>(project_data, "ccache");
        config->cflag = "";
        if(config->debug){
            config->cflag ="-g -Wall ";
            config->exe_file_path = config->root+"/bin/"+config->name+"_debug";
        }else{
            config->cflag = "-O3 ";
            config->exe_file_path = config->root+"/bin/"+config->name;
        }
        config->cflag+="-std="+config->cppversion+" ";// c++11
        
        config->server = read_file(config->home+"/server");
        struct utsname buf;
        uname(&buf);
        config->arch=buf.machine;
        config->os=buf.sysname;
        if(config->ccache){config->compiler = "ccache "+config->compiler;}
        config->include_path+="-I./ ";


        // project
        project = new Project;
        for (std::string app :toml::find<std::vector<std::string>>(project_data, "apps")){
            project->apps.push_back(
                App(app)
            );
        }
        for(std::string depend :toml::find<std::vector<std::string>>(project_data, "depends")){
            project->depends.push_back(
                Depend(depend)
            );
        }

                // 保持同一 前面不留空格 后面留   很重要
    }   
}