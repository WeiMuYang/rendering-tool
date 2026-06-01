# OpenGL 高级渲染技术

本项目是一个基于 Qt 和 OpenGL 的图形学教学程序，系统地实现了现代 OpenGL 中的多项高级渲染技术，包括深度测试、模板测试、混合、面剔除、帧缓冲、后处理特效、天空盒、模型加载、鼠标拾取、动态数据更新等。每个技术点均提供独立的交互式演示界面，用户可实时调节参数并观察效果，非常适合学习 OpenGL 的高级管线功能和渲染技巧。

## 功能特性

程序通过菜单选择不同的渲染场景（每个场景对应一个独立的对话框），目前包含以下模块：

| 模块               | 对应类                | 说明                                                         |
| :----------------- | :-------------------- | :----------------------------------------------------------- |
| **深度测试**       | `DepthTesting`        | 演示不同的深度测试函数（LESS, ALWAYS, NEVER, EQUAL 等）对渲染结果的影响；包含立方体与平面场景。 |
| **精确深度测试**   | `DepthTestingPrecise` | 对比线性深度缓冲区与非线性（透视）深度缓冲区的可视化效果。   |
| **鼠标拾取**       | `MousePicking`        | 演示通过鼠标点击获取屏幕上像素的世界坐标、深度值、裁剪坐标等，实现物体拾取的基础。 |
| **模型加载**       | `LoadModels`          | 使用 Assimp 库加载外部 3D 模型（需自行提供模型文件），并应用光照与纹理。 |
| **模板轮廓**       | `StencilOutLine`      | 利用模板缓冲实现物体轮廓描边（边缘高亮）效果。               |
| **丢弃片段**       | `Discard`             | 通过 `discard` 关键字在片段着色器中丢弃某些片段，实现透明纹理（如草叶）的镂空效果。 |
| **混合**           | `Blending`            | 控制源和目标混合因子（Src/Dst Blend Factor），实现半透明物体的混合渲染（如窗户）。 |
| **面剔除**         | `FaceCulling`         | 切换剔除正面/背面，改变顶点绕序（顺时针/逆时针），观察面剔除对渲染的影响。 |
| **帧缓冲**         | `FrameBuffer`         | 将场景渲染到离屏纹理，再将该纹理显示到屏幕上，为基础的后处理做准备。 |
| **后处理**         | `PostProcessing`      | 对渲染结果应用多种滤镜：反相、灰度化、加权灰度、锐化、模糊。 |
| **天空盒**         | `SkyBox`              | 加载立方体贴图作为天空盒，并支持立方体贴图反射/折射效果，以及纹理反射混合。 |
| **修改数据缓冲区** | `ModifyDataBuffer`    | 演示通过 `glMapBuffer` 和 `glBufferSubData` 动态更新顶点数据。 |
| **GLSL 变量**      | `GLSLVariable`        | 演示 GLSL 中 uniform、attribute 等变量的使用方式。           |
| **接口块**         | `InterfaceBlock`      | 演示 GLSL 中的输入/输出接口块（in/out blocks）的组织方式。   |

此外，每个场景均内置 **第一人称摄像机**（WASD 移动 + 鼠标拖拽旋转 + 滚轮缩放），支持深度测试、纹理映射和光照（平行光）功能。

## 编译与运行

### 依赖环境

- **Qt** 5.12 或更高版本（需要 `core`, `gui`, `opengl`, `widgets`, `openglwidgets` 模块）
- **OpenGL** 3.3 及以上
- **Assimp**（用于模型加载模块，若不需要模型加载可省略）
- **C++17** 编译器（MSVC 2019+ / GCC 9+ / Clang 10+）

### 配置 Assimp（可选）

如果希望使用模型加载功能，需安装 Assimp 库：

bash

```
# Ubuntu
sudo apt-get install libassimp-dev

# Windows (vcpkg)
vcpkg install assimp
```



在 Qt 项目的 `.pro` 文件中添加：

qmake

```
LIBS += -lassimp
INCLUDEPATH += /path/to/assimp/include
```



### 构建步骤（Qt Creator）

1. 打开项目根目录下的 `.pro` 文件。
2. 确保构建套件（Kit）已配置正确的 Qt 版本和编译器。
3. 点击“构建” -> “运行”。

若不需要模型加载，可以注释掉相关代码（`LoadModels` 类及对应的菜单项）。

### 资源文件

项目依赖多个资源前缀（如 `:/01-depth-testing/`, `:/02-depth-testing-precise/`, …），每个模块包含自己的着色器和纹理图片。请确保资源文件（`.qrc`）已正确添加到项目中，并且所有引用的图片和着色器文件路径有效。

## 操作指南

### 主界面

- 程序启动后显示一个主窗口，中央为 OpenGL 渲染视图（`Preview` 控件），通过菜单选择不同的演示模块。
- 每个模块选中后会弹出一个独立的控制对话框，用于调节该模块特有的参数。

### 摄像机控制（所有场景通用）

| 操作             | 功能                    |
| :--------------- | :---------------------- |
| `W` / `S`        | 前后移动摄像机          |
| `A` / `D`        | 左右移动摄像机          |
| **鼠标右键拖拽** | 旋转视角（偏航 + 俯仰） |
| **鼠标滚轮**     | 缩放视野（FOV）         |

> **注意**：需要确保 OpenGL 窗口获得键盘焦点（点击一下画面）。

### 各模块参数调节示例

- **深度测试**：下拉框选择深度比较函数（NEVER, LESS, EQUAL, LEQUAL, GREATER, NOTEQUAL, GEQUAL, ALWAYS, NONE），观察立方体与平面的遮挡关系变化。
- **混合**：分别选择源混合因子和目标混合因子（ZERO, ONE, SRC_ALPHA, ONE_MINUS_SRC_ALPHA 等），调整半透明窗户的混合效果。
- **面剔除**：选择剔除的面（正面/背面/左/右/前后）以及顶点绕序（顺时针/逆时针），查看模型哪些部分消失。
- **后处理**：下拉菜单选择滤镜（反相、灰度化、加权灰度、锐化、模糊），实时改变屏幕输出效果。
- **天空盒**：切换无效果、整个模型反射、整个模型折射、纹理反射，观察立方体表面的环境映射变化。
- **修改数据缓冲区**：选择不同的数据更新方式（正常、`glMapBuffer` 给一半数据、给全部数据、`glBufferSubData` 给一半、给全部），观察顶点位置的变化。

### 其他

- 部分模块（如模型加载）需要自行将模型文件放置于指定路径（代码中硬编码为 `:/04-load-models/img/` 等资源路径，建议改为外部文件加载）。
- 鼠标拾取模块：在渲染视图中点击物体，控制对话框会显示点击处的屏幕坐标、深度值、裁剪空间坐标、世界空间坐标等信息。

## 项目结构

由于代码片段较多，以下列出主要类和文件的功能：

| 文件                          | 职责                                                         |
| :---------------------------- | :----------------------------------------------------------- |
| `preview.h/cpp`（推断）       | 主 OpenGL 控件，负责初始化、摄像机管理、场景切换、绘制循环   |
| `camera.h/cpp`                | 第一人称摄像机（位置、欧拉角、视图矩阵、移动/旋转/缩放处理） |
| `data_type.h`（推断）         | 包含枚举：`Scene`（场景类型）、`DepthTestType`、`BlendingType`、`FaceCullingType` 等 |
| `axis.h/cpp`                  | 绘制 RGB 坐标轴（独立着色器，分别绘制红/绿/蓝线条）          |
| `depth_testing.h/cpp`         | 深度测试模块（立方体 + 平面，可调深度函数）                  |
| `depth_testing_precise.h/cpp` | 精确深度测试（线性 vs 非线性深度可视化）                     |
| `mouse_picking.h/cpp`         | 鼠标拾取（计算点击位置的世界坐标）                           |
| `load_models.h/cpp`           | 模型加载（Assimp + 光照）                                    |
| `stencil_outline.h/cpp`       | 模板轮廓描边                                                 |
| `discard.h/cpp`               | 丢弃片段（草叶透明纹理）                                     |
| `blending.h/cpp`              | 混合（透明窗户）                                             |
| `face_culling.h/cpp`          | 面剔除                                                       |
| `frame_buffer.h/cpp`          | 帧缓冲（离屏渲染）                                           |
| `post_processing.h/cpp`       | 后处理特效                                                   |
| `sky_box.h/cpp`               | 天空盒 + 反射/折射                                           |
| `modify_data_buffer.h/cpp`    | 动态修改顶点数据                                             |
| `glsl_variable.h/cpp`         | GLSL 变量使用示例                                            |
| `interface_block.h/cpp`       | GLSL 接口块示例                                              |
| `mesh.h/cpp`, `model.h/cpp`   | 模型加载辅助类（Assimp 解析，Mesh 封装）                     |
| `vertices.h/cpp`              | 简单顶点数据容器                                             |

## 扩展与定制

### 添加新的演示模块

1. 在 `data_type.h` 的 `Scene` 枚举中添加新值。
2. 创建新类（继承 `QDialog`），实现 `initShader()`, `initTexture()`, `updateShapeShader()` 等方法（参照现有模块）。
3. 在 `Preview` 类中添加该成员变量，并在 `initializeGL()` 中调用其 `initShader()` 和 `initTexture()`。
4. 在 `Preview::drawModule()` 中添加新的 case，调用对应的绘制函数。
5. 在主窗口菜单中添加 `QAction`，并绑定到场景。

### 修改摄像机速度或灵敏度

在 `camera.cpp` 中调整 `SPEED`, `SENSITIVITY` 常量，或通过 UI 提供调节接口。

### 替换纹理和模型

- 纹理：替换资源文件中的图片，或修改各模块 `initTexture()` 中的加载路径。
- 模型：在 `LoadModels` 中使用 `Model` 类加载自己的 `.obj`/`.fbx` 文件（注意纹理路径）。

## 常见问题

### 1. 编译时找不到 Assimp 头文件

确保已正确安装 Assimp，并在 `.pro` 文件中添加了 `LIBS` 和 `INCLUDEPATH`。如果不需要模型加载功能，可以暂时注释掉 `LoadModels` 相关代码。

### 2. 天空盒显示为黑色

- 检查立方体贴图图片路径是否正确，图片格式是否为 RGB 24 位。
- 确保摄像机视图矩阵去除了平移分量（仅保留旋转），否则天空盒会跟随摄像机移动。

### 3. 混合效果不正确

- 确认开启了 `glEnable(GL_BLEND)`。
- 混合因子选择不当可能导致透明物体过暗或过亮，尝试常用的 `SRC_ALPHA, ONE_MINUS_SRC_ALPHA`。
- 注意混合顺序：透明物体应在不透明物体之后绘制（深度测试开启时）。

### 4. 鼠标拾取坐标不正确

- 确保投影矩阵、视图矩阵与当前渲染使用的完全一致。
- 检查是否正确读取了帧缓冲中的深度值（`glReadPixels` 的格式需为 `GL_DEPTH_COMPONENT`）。
- 注意 OpenGL 的屏幕坐标系原点在左下角，而 Qt 的鼠标事件原点在左上角，需要做 Y 轴翻转。

### 5. 模板轮廓没有效果

- 确认模板缓冲已正确配置（例如 `glEnable(GL_STENCIL_TEST)`，并设置合适的模板函数和操作）。
- 绘制轮廓时需要先绘制原始物体（填充模板缓冲），再绘制放大的轮廓物体（仅当模板值不为 0 时绘制）。

## 许可证

本项目为教学演示代码，可自由使用、修改和分发。部分纹理图片来源于网络，仅供学习使用，请勿用于商业用途。

## 致谢

- [LearnOpenGL CN](https://learnopengl-cn.github.io/) – 提供了详尽的理论和代码示例
- Qt 官方文档 – OpenGL 模块参考
- Assimp 开发团队 – 强大的模型导入库

------

**Enjoy exploring advanced OpenGL techniques with Qt!**
任何问题欢迎反馈或提交 Issue。