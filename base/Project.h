#ifndef CCAO_BASE_CPROJECT
#define CCAO_BASE_CPROJECT
#include <vector>
#include <base/App.h>

class Project {
public:
    std::vector<App> apps;
    std::vector<Depend> depends;
};
#endif