#include <Star.h>
#include <tools.h>
#include <vars.h>
#include <unistd.h>
void Star::make(){
    std::string cmd;
    c_mkdir(root+"/out/temp");
    cmd=(
        "cp "+root+"/star.toml "+root+"/out/package/star.toml "
    );
    check_error(system(cmd.c_str()));
    std::cout << "[*]Start build Star " <<this->name<<std::endl;
    cmd="cp "+root+"/headers/* "+root+"/out/package -r";
    check_error(system(cmd.c_str()));
// ar crsT lib1.a cwd.a .cwda
    std::vector<Depend> depends;
    for(std::string depend :this->depends){
            depends.push_back(
                Depend(depend)
            );
    }
    std::string link_file("");
    include_path+="-I"+root+"/headers ";
    cflag="-std="+this->cppversion+" ";// c++11

    chdir((root+"/out/temp").c_str());
    for(auto _:depends){
        include_path+="-I"+_.path+" ";

        cmd=("cp "+home+"/stars/"+_.name+"/"+_.version+"/lib"+_.name+".a "+root+"/out/temp ");
        log("[*] "+cmd);
        check_error(system(cmd.c_str()));
        
        cmd=("ar x lib"+_.name+".a ");
        log("[*] "+cmd);
        check_error(system(cmd.c_str()));
        
        cmd=("rm lib"+_.name+".a ");
        log("[*] "+cmd);
        check_error(system(cmd.c_str()));
        
    }
    
    

    for(std::string source:ls(root+"/source")){
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
        check_error(system(cmd.c_str()));
    }
    for(auto _:ls(root+"/out/temp")){
        link_file += _+" ";
    }

    cmd=(
        "ar crsv "
        +root+"/out/package/lib"+this->name+".a "
        +link_file
    );
    std::cout << "[*]"<<cmd<<std::endl;
    check_error(system(cmd.c_str()));

    std::cout << "[+] Build Star" <<this->name<<" Successfully !"<<std::endl;
}


void Star::test(std::string args){
    this->make();
    std::string s=" ";
    if(debug){
        s=" -g -Wall ";
    }
    std::string cmd(
        compiler
        +root+"/test/test.cpp "
        +"-I"+root+"/out/package "
        +"-L"+root+"/out/package "
        +"-l"+this->name+s
        +"-o "+root+"/test/a.out "
    );

    std::cout << "[*]"<<cmd<<std::endl;
    check_error(system(cmd.c_str()));
    
    cmd = (root+"/test/a.out "+args);
    std::cout << "[*]"<<cmd<<std::endl;
    std::cout << "[+]Results => \n"<<std::endl;
    check_error(system(cmd.c_str()));
    
}