#include <Cconfig.h>
#include <vars.h>
#include <tools.h>


void CONFIG(){
    // 判断是否为工程项目
    Cconfig *temp_config = new Cconfig;
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
        std::string ccao = root + "/ccao.toml";
        const toml::value data=toml::parse(ccao);
        // 配置[project]
        const auto project_data = toml::find(data,"project");
        temp_config->name = toml::find
            <std::string>
        (project_data,"name");

        temp_config->apps = toml::find
            <std::vector<std::string>>
        (project_data,"apps");

        temp_config->depends = toml::find
            <std::vector<std::string>>
        (project_data,"depends");
        // gcc or g++
        cpp = toml::find
            <bool>
        (project_data,"cpp");

            debug = toml::find
            <bool>
        (project_data,"debug");

        temp_config->cppversion = toml::find
            <std::string>
        (project_data,"cppversion");

        extra_cflag= toml::find
            <std::string>
        (project_data,"cflag");

        config=temp_config;
    } 
    if(isStar){
        std::string starS = root + "/star.toml";
        const toml::value star_data=toml::parse(starS);
        // 配置[project]
        const auto star_data = toml::find(star_data,"star");
        star->name = toml::find
            <std::string>
        (star_data,"name");
        star->version = toml::find
            <int>
        (star_data,"version");
        star->moudles = toml::find
            <std::vector<std::string>>
        (star_data,"moudles");

        star->depends = toml::find
            <std::vector<std::string>>
        (star_data,"depends");
        // gcc or g++
    }
}
