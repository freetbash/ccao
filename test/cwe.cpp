#include <dirent.h>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>
using namespace std;

int main(){
    struct stat buffer;
    cout << (stat ("1.2h",&buffer) ==0)<<endl;
    return 0;
}