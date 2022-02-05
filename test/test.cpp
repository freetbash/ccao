#include "../include/Ccao.h"
#include <unistd.h>
#include <iostream>

using namespace std;
int main(){
    
    for(
        string i : ls(get_current_dir_name())
    ){
        cout<<i<<endl;
    }
}