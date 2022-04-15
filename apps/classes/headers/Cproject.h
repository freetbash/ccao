#ifndef CCAO_CLASSES_CPROJECT
#define CCAO_CLASSES_CPROJECT
#include <vector>
#include <App.h>

class Cproject {
public:
    std::vector<App> apps;
    std::vector<Depend> depends;
};
void PROJECT();

#endif