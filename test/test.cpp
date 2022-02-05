#include "../include/Ccao.h"
#include <unistd.h>
#include <iostream>

using namespace std;
int main(){
    vector<string> asc = ls(get_current_dir_name());

    for(string i : asc){
        cout<<i<<endl;
    }
}