# ccao

#### 介绍
一个C/CPP 工程构建器 去他妈的CMake
## 使用
ccao help

# 建议 

```c++
函数头宏定义推荐：
  全部大写 ： 项目名_APP名_文件名
  // 可以参照 本项目
  
头文件导入 ：
  <test.h>直接导入

头文件相互包含:
  class ClassName;
  class TEst1P{
    ClassName *name;
  }
  定义外部类 全部使用 指针
  然后在实现函数的地方包含 ClassName
关于全局变量：
  实现public app
    头文件 extern 外部定义
    source 源码文件进行定义
```
# 由Ccao 构建的项目
    Cccao https://gitee.com/cfreet/ccao         （C/C++项目构建工具)
    Chameleon https://gitee.com/cfreet/chameleon (Http 服务器，路由 视图）
