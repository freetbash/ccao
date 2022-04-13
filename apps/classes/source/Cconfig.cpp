#include <Cconfig.h>
#include <vars.h>
#include <tools.h>


void CONFIG(){
    // 判断是否为工程项目
    
    // init root
    char *path = get_current_dir_name();
    
    if(path!=NULL){
        root=path;
    }else{
        std::cout<<"[-]Your absolute path isn't setted successfully!\n [-]Please check your permissions. "<<std::endl;
        exit(-1);
    }
    isProject=FileExists(root+"/ccao.toml");
    isStar=FileExists(root+"/star.toml");

    if(isProject){
        config = new Cconfig;
        std::string ccao = root + "/ccao.toml";
        const toml::value data=toml::parse(ccao);
        // 配置[project]
        const auto project_data = toml::find(data,"project");
        config->name = toml::find
            <std::string>
        (project_data,"name");

        config->apps = toml::find
            <std::vector<std::string>>
        (project_data,"apps");

        config->depends = toml::find
            <std::vector<std::string>>
        (project_data,"depends");

            debug = toml::find
            <bool>
        (project_data,"debug");

        config->cppversion = toml::find
            <std::string>
        (project_data,"cppversion");

        extra_cflag= toml::find
            <std::string>
        (project_data,"cflag");
    } 
    
    if(isStar){
        star = new Star;
        std::string starS = root + "/star.toml";
        
        const toml::value data=toml::parse(starS);
        // 配置[project]
        const auto star_data = toml::find(data,"star");
        
        star->name = toml::find
            <std::string>
        (star_data,"name");
        star->version = toml::find
            <int>
        (star_data,"version");

        star->depends = toml::find
            <std::vector<std::string>>
        (star_data,"depends");
        // gcc or g++
    }
}
