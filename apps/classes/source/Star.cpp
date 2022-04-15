#include <Star.h>
#include <tools.h>
#include <vars.h>
void Star::make(){
    std::string cmd;
    cmd=(
        "rm -rf "+root+"/out/temp "
    );
    system(cmd.c_str());
    c_mkdir(root+"/out/temp");
    
    std::cout << "[*]Start build Star " <<this->name<<std::endl;
    c_mkdir(root+"/out/package/target");
    cmd="cp "+root+"/headers/* "+root+"/out/package/target -r";
    system(cmd.c_str());
// ar crsT lib1.a cwd.a .cwda
    std::vector<Depend> depends;
    for(std::string depend :this->depends){
            depends.push_back(
                Depend(depend)
            );
    }
    std::string link_file("");
    std::string compiler;if(cpp==true){compiler="g++ ";}else{compiler="gcc ";}
    include_path+="-I"+root+"/headers ";
    cflag="-std="+this->cppversion+" ";// c++11

    for(auto _:depends){
        include_path+="-I"+_.path+" ";
        link_file += _.a;
    }
        
    for(std::string source:ls(root+"/source")){
        exe_file_path += root+"/out/temp/"+source+".o ";
        cmd=(
            compiler
            +"-c "
            +root+"/source/"+source+" "
            +cflag
            +include_path
            +"-o "
            +root+"/out/temp/"+source+".o "
            +extra_cflag
        );
        std::cout << "[*]"<<cmd<<std::endl;
        system(cmd.c_str());
    }
    
    
    

    cmd=(
        "ar crsT "
        +root+"/out/package/target/lib"+this->name+".a "
        +exe_file_path
        +link_file
    );
    std::cout << "[*]"<<cmd<<std::endl;
    system(cmd.c_str());

    std::cout << "[+] Build Star" <<this->name<<" Successfully !"<<std::endl;
}