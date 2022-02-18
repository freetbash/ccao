#ifndef CCAO_CLASSES_APP
#define CCAO_CLASSES_APP
#include <string>
#include <vector>
class App{
public:
    // attributes
    int type;
    bool blank;
    std::string name;
    std::string path;
    std::string out_path;
    std::vector<std::string> headers;
    std::vector<std::string> source;

    // methods
    App();
    App *clone();
    static App *find(std::string app_name);
    App(std::string name,int type);
    std::string get_type();
    void build(
        std::string cflag,
        std::string include_path,
        std::string library_path
    );// 构建自己
};
App *MAIN();


#endif