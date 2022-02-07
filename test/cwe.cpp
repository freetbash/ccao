#include <dirent.h>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>
using namespace std;

int main(){
    
    cout<<mkdir("/home/bash/ccao/test/123",S_IRUSR|S_IWUSR)<<endl;
    return 0;
}