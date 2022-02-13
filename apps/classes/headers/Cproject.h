#ifndef __CCAO_PROJECT__H
#define __CCAO_PROJECT__H
#include <vector>
#include <App.h>

class Cproject {
public:
    // attributes
    App *main;// 判断main的目录 为不为空 为空 就提示将不会创建 可执行文件
    std::vector<App> apps;
    std::vector<App> depends;
    // methods
};
void PROJECT();

#endif