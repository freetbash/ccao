#include <App.h>
#include <vars.h>
#include <tools.h>
#include <public.h>

App::App(){}
std::string App::get_type(){
    if(this->type == APP){
        return "APP";
    }else{
        return "DEPEND";
    }
}
App* App::clone(){
    App *temp = new App;
    temp->type = this->type;
    temp->blank = this->blank;
    temp->name = this->name;
    temp->path = this->path;
    temp->out_path = this->out_path;
    temp->headers = this->headers;
    temp->source = this->source;
    return temp;
}
App* App::find(std::string app_name){
    for(App current_app: project->apps){
        if(current_app.name == app_name){
            return current_app.clone();
        }
    }
    return NULL;
}
App *MAIN(){
    App *main = new App;
    main->type=APP;
    main->out_path = root+"/out/debug/bin";
    if (!debug){
        main->out_path = root+"/out/release/bin";
    }

    main->type=APP;
    main->name = config->name;
        main->headers = ls(root+"/"+main->name+"/headers");
        main->source = ls(root+"/"+main->name+"/source");

    // 判断目录为不为空
    if(main->source.size() == 0)
    {
        main->blank=true;

    }else{
        main->blank=false;
    }
    return main;
};
App::App(std::string name,int type){
    std::string build_out_path = root+"/out/debug/libs";
    if (!debug){
        build_out_path = root+"/out/release/libs";
    }
    this->type=type;
    this->name = name;
    
    // 根据类型初始化
    if(this->type == APP){
        this->path = root+"/apps/"+name;
        this->headers = ls(this->path+"/headers");
        this->source  = ls(this->path+"/source");
        this->out_path = build_out_path+"/own";
    }

    if(this->type == DEPEND){
        this->path = root+"/depends/"+name;
        this->headers = ls(this->path+"/headers");
        this->source  = ls(this->path+"/source");
        this->out_path = build_out_path+"/other";
    }

    // 判断目录为不为空
    if(this->source.size() == 0){
        this->blank=true;

    }else{
        this->blank=false;
    }

}

void App::build(std::string cflag,std::string include_path,std::string library_path){
    if(this->blank){
log("[*] "+this->name+"is blank, it isn't be build !");
        return;
        }
    // 删除上一次构建
    system(
        (
            "rm -rf "
            +this->out_path+"/lib"+this->name+".a "
            +root+"/out/temp/"+this->name
        ).c_str()
    );
    // 准备 编译命令
    // 将c cpp 路径 拼接到一起
    std::string compiler;
    if(cpp){
        compiler="g++ ";
    }else{
        compiler="gcc ";
    }
    std::string source;
    std::string cmd;
    std::string type="/apps/";
    if(this->type == DEPEND){
        type="/depends/";
    }
    std::string all_o="";

log("[*] Start build ("+this->get_type()+") "+ this->name);

    for (std::string c_cpp :this->source){
        c_mkdir(root+"/out/temp/"+this->name);

        source=root+type+this->name+"/source/"+c_cpp+" ";
        std::string out_path = root+"/out/temp/"+this->name+"/"+c_cpp+".o ";
        all_o+=out_path;
        std::string cmd(
            compiler
            +source
            +cflag
            +include_path
            +library_path
            +"-o "
            +out_path
        ); // 最终生成的命令

log("[*] "+cmd);

        check_error(system(cmd.c_str()));
    }
    cmd = 
        "ar -rc "
        +this->out_path+"/lib"+this->name+".a "
        +all_o
    ;
log("[*] "+cmd);
    check_error(system(cmd.c_str()));
    

}
