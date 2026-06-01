# 实时三维渲染引擎 – 基于 OpenGL 的图形框架

一个基于 Qt 与 OpenGL 的高性能 3D 渲染框架，集成现代图形管线中的核心渲染技术、高级光照模型与后处理特效，适用于可视化仿真、图形引擎及渲染技术验证。系统地实现了现代 OpenGL 渲染管线中的各项核心技术。从基础的图元绘制、纹理映射、几何变换，到复杂的光照模型（Phong、Gouraud、材质系统、多光源），再到高级渲染技巧（深度测试、模板测试、混合、面剔除、帧缓冲、后处理特效、天空盒、模型加载、鼠标拾取、动态数据更新等）。每个功能模块都配有独立的交互界面，支持实时参数调节。

## 功能总览

### 一、基础渲染模块（早期代码）

这些功能存在于项目的初始版本中，展示了 OpenGL 的基础知识：

| 菜单项                    | 功能说明                                                     |
| :------------------------ | :----------------------------------------------------------- |
| **三角形/矩形**           | 绘制基本图元，支持点、线、面三种绘制模式                     |
| **统一颜色 / 逐顶点颜色** | 演示 `uniform` 和顶点属性 `attribute` 传递颜色数据           |
| **纹理贴图**              | 单纹理、多纹理混合，纹理包裹方式（REPEAT / MIRRORED_REPEAT / CLAMP_TO_BORDER / CLAMP_TO_EDGE） |
| **纹理过滤**              | 邻近过滤、线性过滤及各类 Mipmap 过滤（NEAREST, LINEAR, NEAREST_MIPMAP_NEAREST 等） |
| **几何变换**              | 通过模型矩阵实现位移、旋转（绕任意轴）、缩放，并支持实时调节 |
| **3D 立方体（MVP）**      | 引入透视投影和模型-视图-投影矩阵，展示立体物体的渲染         |
| **多立方体实例**          | 一次绘制多个不同位置、旋转角度的立方体                       |
| **第一人称摄像机**        | 键盘 WASD 移动 + 鼠标控制视角 + 滚轮缩放，实时显示摄像机参数 |

### 二、光照与材质系统（扩展模块）

以下模块独立为对话框，可单独运行观察：

| 模块                     | 类名              | 说明                                                         |
| :----------------------- | :---------------- | :----------------------------------------------------------- |
| **简单物体颜色**         | `ColorOfObject`   | 只包含物体颜色和光源颜色，演示最基础的光照（无漫反射和镜面反射） |
| **Phong 光照**           | `PhongLight`      | 逐片段光照模型：环境光 + 漫反射 + 镜面反射                   |
| **Gouraud 光照**         | `GouraudLight`    | 逐顶点光照（顶点着色器计算颜色），与 Phong 对比效果与性能    |
| **材质系统**             | `Material`        | 物体材质（环境光、漫反射、镜面反射、反光度）与光源分量（环境/漫反射/镜面反射）分离调节 |
| **预置材质（青色塑料）** | `CyanPlastic`     | 演示一种固定材质的视觉效果                                   |
| **纹理光照**             | `TextureLight`    | 漫反射贴图 + 镜面反射贴图 + 发光贴图（自发光）               |
| **平行光（方向光）**     | `Parallel_Light`  | 只具有方向，无位置衰减的光源                                 |
| **点光源**               | `PointLight`      | 具有位置和衰减系数（常数、一次、二次）的光源                 |
| **聚光灯（硬边缘）**     | `SpotLight`       | 带内锥角（cutOff）的聚光效果                                 |
| **聚光灯（平滑边缘）**   | `SpotLightSmooth` | 带内锥角和外锥角（outerCutOff），边缘平滑过渡                |
| **多光源组合**           | `MultLight`       | 同时包含 1 个平行光 + 2 个点光源 + 2 个聚光灯，每个光源颜色不同，展示复杂光照环境 |

### 三、高级渲染技术（进阶模块）

| 模块                 | 类名                  | 说明                                                         |
| :------------------- | :-------------------- | :----------------------------------------------------------- |
| **深度测试**         | `DepthTesting`        | 切换深度比较函数（LESS, ALWAYS, NEVER, EQUAL 等），观察遮挡关系变化 |
| **精确深度测试**     | `DepthTestingPrecise` | 可视化线性深度缓冲区（`gl_FragCoord.z`）与非线性的透视深度对比 |
| **鼠标拾取**         | `MousePicking`        | 点击屏幕获取像素的世界坐标、深度值、裁剪空间坐标，用于物体拾取 |
| **模型加载**         | `LoadModels`          | 使用 Assimp 库加载外部 3D 模型（如 `.obj`），自动解析网格、材质和纹理 |
| **模板轮廓描边**     | `StencilOutLine`      | 利用模板缓冲实现物体边缘轮廓高亮（卡通轮廓效果）             |
| **丢弃片段**         | `Discard`             | 在片段着色器中使用 `discard` 丢弃透明纹理的片段，实现草叶、树叶等镂空效果 |
| **混合（透明）**     | `Blending`            | 调节源因子和目标因子（SRC_ALPHA, ONE_MINUS_SRC_ALPHA 等），实现半透明物体渲染 |
| **面剔除**           | `FaceCulling`         | 选择剔除正面/背面，改变顶点绕序（顺时针/逆时针），优化渲染性能 |
| **帧缓冲**           | `FrameBuffer`         | 将场景渲染到离屏纹理，再将该纹理绘制到屏幕，为后处理做准备   |
| **后处理特效**       | `PostProcessing`      | 对渲染结果应用多种滤镜：反相、灰度化、加权灰度、锐化、模糊   |
| **天空盒**           | `SkyBox`              | 加载立方体贴图作为环境背景，并支持环境映射（反射、折射、纹理反射混合） |
| **动态修改顶点数据** | `ModifyDataBuffer`    | 演示 `glMapBuffer` 和 `glBufferSubData` 两种方式动态更新顶点缓冲区 |
| **GLSL 变量示范**    | `GLSLVariable`        | 展示 uniform、attribute、varying 等 GLSL 变量的典型用法      |
| **接口块示范**       | `InterfaceBlock`      | 展示 GLSL 中输入/输出接口块（in/out blocks）的组织方式       |

## 项目结构

由于代码量较大，以下列出核心类及文件：

text

```
.
├── main.cpp                     # 应用程序入口
├── mainwindow.h/cpp             # 主窗口，菜单管理，场景切换
├── preview.h/cpp                # OpenGL 渲染控件（核心），管理摄像机、VAO、着色器、绘制循环
├── camera.h/cpp                 # 第一人称摄像机类
├── axis.h/cpp                   # 坐标轴绘制（独立着色器）
├── vertices.h/cpp               # 简单的顶点/索引数据容器
├── data_type.h                  # 共用枚举（Module, Scene, DrawMode, TexWrap, TexFilter, DepthTestType, BlendingType, FaceCullingType 等）
│
├── 光照材质模块（独立对话框）
│   ├── color_of_object.h/cpp
│   ├── phong_light.h/cpp
│   ├── gouraud_light.h/cpp
│   ├── material.h/cpp
│   ├── cyan_plastic.h/cpp
│   ├── texture_light.h/cpp
│   ├── parallel_light.h/cpp
│   ├── point_light.h/cpp
│   ├── spot_light.h/cpp
│   ├── spot_light_smooth.h/cpp
│   └── mult_light.h/cpp
│
├── 高级渲染模块
│   ├── depth_testing.h/cpp
│   ├── depth_testing_precise.h/cpp
│   ├── mouse_picking.h/cpp
│   ├── load_models.h/cpp
│   ├── stencil_outline.h/cpp
│   ├── discard.h/cpp
│   ├── blending.h/cpp
│   ├── face_culling.h/cpp
│   ├── frame_buffer.h/cpp
│   ├── post_processing.h/cpp
│   ├── sky_box.h/cpp
│   ├── modify_data_buffer.h/cpp
│   ├── glsl_variable.h/cpp
│   └── interface_block.h/cpp
│
├── 模型加载辅助（Assimp）
│   ├── model.h/cpp               # 加载和管理模型
│   └── mesh.h/cpp                # 单个网格的 VAO/VBO/EBO 管理及绘制
│
└── 资源文件
    ├── img.qrc                   # 纹理图片资源
    └── shader.qrc                # 所有顶点/片段着色器
```



> **注**：实际代码中各个模块的着色器和纹理位于独立的前缀路径下（如 `:/01-depth-testing/shader/`, `:/02-depth-testing-precise/shader/` 等），但最终都通过 Qt 资源系统编译进可执行文件。

## 编译与运行

### 依赖环境

| 组件       | 版本要求   | 备注                                                         |
| :--------- | :--------- | :----------------------------------------------------------- |
| **Qt**     | 5.12+      | 需要 `core`, `gui`, `opengl`, `widgets`, `openglwidgets` 模块 |
| **OpenGL** | 3.3+       | 深度测试、模板测试、高级特性需要                             |
| **Assimp** | 任意稳定版 | **可选**，仅模型加载模块需要（若不使用可注释相关代码）       |
| **编译器** | C++17      | MSVC 2019+ / GCC 9+ / Clang 10+                              |

### 安装 Assimp（如需模型加载）

bash

```
# Ubuntu / Debian
sudo apt-get install libassimp-dev

# macOS (Homebrew)
brew install assimp

# Windows (vcpkg)
vcpkg install assimp
```



在项目 `.pro` 文件中添加：

qmake

```
LIBS += -lassimp
INCLUDEPATH += /usr/include/assimp   # 根据实际路径调整
```



### 构建步骤

1. 使用 **Qt Creator** 打开项目根目录下的 `.pro` 文件。
2. 选择正确的构建套件（Kit），确保 Qt 版本和编译器匹配。
3. 点击“构建” -> “运行”。

若遇到缺少资源文件的错误，请检查 `.qrc` 文件是否正确添加到项目中，且所有引用的图片/着色器文件确实存在于对应的路径。

## 操作指南

### 主窗口操作

- **菜单栏**：选择不同的演示模块（分为基础、光照、高级三类）。
- **OpenGL 视图**：显示当前的 3D 场景，支持以下交互：
  - **键盘**：`W` / `S` / `A` / `D` 移动摄像机。
  - **鼠标**：**右键拖拽** 旋转视角；**滚轮** 缩放视野（FOV）。
  - *注意*：视图需要获得焦点（点击画面一次）才能响应键盘/鼠标事件。
- **参数调节**：切换模块后会自动弹出一个独立的控制对话框，可以实时调整光源位置/颜色、材质属性、深度函数、混合因子、后处理滤镜等参数。修改后场景即时更新。

### 各模块典型操作示例

| 模块                   | 典型操作                                                     |
| :--------------------- | :----------------------------------------------------------- |
| **Phong/Gouraud 光照** | 调整光源位置（动态环绕），改变物体反光度（shininess），观察高光变化。 |
| **材质系统**           | 分别调节物体材质（ambient, diffuse, specular）和光源分量（ambient, diffuse, specular），理解各自作用。 |
| **纹理光照**           | 切换漫反射贴图、镜面反射贴图、发光贴图，观察材质外观。       |
| **点光源**             | 调整衰减系数（constant, linear, quadratic），观察光线随距离衰减的效果。 |
| **聚光灯平滑**         | 调节内锥角（cutOff）和外锥角（outerCutOff），看光斑边缘渐变。 |
| **多光源**             | 每个光源独立颜色和位置，观察多个颜色叠加的照明效果。         |
| **深度测试**           | 改变比较函数为 `ALWAYS` 可看到后绘制的物体总是覆盖先绘制的，`LESS` 则是正常遮挡。 |
| **混合**               | 将源因子设为 `SRC_ALPHA`，目标因子设为 `ONE_MINUS_SRC_ALPHA`，实现标准透明度混合。 |
| **面剔除**             | 剔除背面并改变顶点绕序为顺时针，立方体某些面会消失。         |
| **后处理**             | 选择“模糊”滤镜，场景会变模糊；选择“反相”则颜色反转。         |
| **天空盒**             | 切换到“整个模型反射”模式，可以看到立方体表面反射天空盒图像。 |
| **动态修改顶点数据**   | 选择“glMapBuffer 给一半数据”，立方体形状会变形（顶点位置被部分改变）。 |

## 扩展与定制

### 添加新的渲染模块

1. 在 `data_type.h` 的 `Scene` 枚举中添加新值。
2. 创建新类（继承 `QDialog`），实现 `initShader()`, `initTexture()`, `updateShapeShader()` 等方法。
3. 在 `Preview` 类中添加该类的成员变量，并在 `initializeGL()` 中调用其初始化函数。
4. 在 `Preview::drawModule()` 的 `switch` 中添加新的 `case`，调用对应的绘制函数。
5. 在主窗口的菜单中添加 `QAction`，绑定到新场景。

### 修改摄像机参数

编辑 `camera.cpp` 中的 `SPEED`（移动速度）、`SENSITIVITY`（鼠标灵敏度）、`ZOOM`（初始视野）常量，或通过信号槽在 UI 中添加滑动条。

### 加载自己的模型

- 将模型文件（如 `backpack.obj` 及对应的 `.mtl` 和纹理）放入可访问的目录。
- 修改 `LoadModels` 类中的路径，或通过对话框让用户选择文件。
- 注意 Assimp 会自动解析材质和纹理，但纹理路径可能需要调整（代码中已有 `TextureFromFile` 函数拼接目录）。

## 已知问题与注意事项

- **纹理图片翻转**：代码中多处使用 `.mirrored()` 来匹配 OpenGL 的纹理坐标原点（左下），如果图片上下颠倒，移除该调用即可。
- **模型加载纹理缺失**：如果模型文件引用的纹理图片路径是相对路径且与模型文件不在同一目录，需要修改 `LoadModels::TextureFromFile` 中的拼接逻辑。
- **混合排序问题**：在 `Blending` 模块中，由于未对透明物体进行深度排序，可能出现透过窗户看到后面墙壁但窗户半透明渲染不正确的情况。教学演示中可接受，实际项目中需按距离排序。
- **模板轮廓**：需要在 `StencilOutLine` 模块中正确设置模板缓冲的初始值和操作（代码中未展示完整绘制流程，参考 `preview` 的实现）。
- **鼠标拾取深度值**：使用 `glReadPixels` 读取深度时，注意 OpenGL 坐标原点在左下，而 Qt 鼠标坐标原点在左上，需要做 `y = height - y` 转换。

## 许可证

本项目为教学用途，代码可自由使用、修改和分发。部分纹理图片来源于网络，仅限学习使用，请勿用于商业用途。

## 参考资料

- [LearnOpenGL CN](https://learnopengl-cn.github.io/) – 光照、高级 OpenGL 章节
- Qt 官方文档 – [Qt OpenGL 模块](https://doc.qt.io/qt-5/qtopengl-index.html)
- Assimp 文档 – [Open Asset Import Library](http://www.assimp.org/)

------

**愿这份项目能帮助您深入理解现代 OpenGL 渲染技术！**
如有问题或建议，欢迎反馈。