#include <Cconfig.h>
#include <vars.h>
#include <tools.h>


void CONFIG(){
    // 判断是否为工程项目
    Cconfig *temp_config = new Cconfig;
    isProject=file_exist("ccao.toml");
    // init root
    char *path = get_current_dir_name();
    if(path!=NULL){
        root=path;
    }else{
        std::cout<<"[-]Your absolute path isn't setted successfully!\n [-]Please check your permissions. "<<std::endl;
        exit(-1);
    }

    if(!isProject){return;} // 这里可是个关键

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
