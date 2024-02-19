# [渲染工具开发](./)   [img](./img)  

## 1 简介 

渲染工具开发主要是基于qt实现的渲染引擎，可以包含所有渲染引擎的基本功能：相机，添加模型，模型移动，添加光照，渲染次序，坐标系转化和广告牌机制等。

可以显示：人物，模型，相机参数，以及在各个坐标系中的值。 

参考链接：https://zhuanlan.zhihu.com/p/517924720  

## 2 Assimp

Assimp:  [The Assimp 5.3.0 Minor-Release](https://github.com/assimp/assimp/releases/tag/v5.3.0)   

### 2.1 编译报错 

方法一：

```c++
// include\assimp\types.h
注释掉:
//#ifdef ASSIMP_USE_HUNTER
//#   include <utf8.h>
//#else
//#   include "../contrib/utf8cpp/source/utf8.h"
//#endif
```

方法二：

添加contrib到include目录下
