#include <main.h>
#include <sys/utsname.h>

void config_init(){
    printf("[*] Initing..... CCAO\n");

    c_mkdir(home);
    check_error(system(
        ("echo 'http://82.157.65.112:3147/' >"+home+"/server").c_str()
    ));
    c_mkdir(home+"/stars");
}
void init(){
    home =std::string(getenv("HOME"))+"/.ccao";
    if(!DirExists(home)){
        config_init();
    }
    CONFIG();
    if(isProject){
        PROJECT();
    }
    
    if(cpp==true){
        if(termux){
            compiler="aarch64-linux-gnu-g++ ";
        }else{
            compiler="g++ ";
        }
    }else{
        if(termux){
            compiler="aarch64-linux-gnu-gcc ";
        }else{
            compiler="gcc ";
        }
    }
    if(ccache){compiler = "ccache "+compiler;}
    server = read_file(home+"/server");

    struct utsname buf;
	uname(&buf);
	arch=buf.machine;
    os=buf.sysname;
}