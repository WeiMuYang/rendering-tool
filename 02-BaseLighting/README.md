# 光照与材质系统

本项目是一个基于 Qt 和 OpenGL 的图形学教学演示程序，系统地实现了现代 OpenGL 渲染管线中的多种光照模型和材质系统。通过直观的图形界面和实时交互，用户可以深入理解环境光、漫反射、镜面反射、材质属性、纹理光照以及各类光源（平行光、点光源、聚光灯）的工作原理。

## 项目简介

该项目从基础的顶点/片段着色器开始，逐步构建了以下核心功能：

- **基础立方体绘制**（带纹理坐标）
- **第一人称摄像机**（WASD + 鼠标控制）
- **多种经典光照模型**：仅颜色物体、Phong 光照、Gouraud 光照
- **材质系统**：可编辑的环境光、漫反射、镜面反射分量及高光反光度
- **纹理光照**：漫反射贴图、镜面反射贴图、发光贴图
- **多光源系统**：平行光、点光源（含衰减）、聚光灯（带平滑边缘）
- **多光源组合场景**：同时展示方向光、点光源和聚光灯
- **实时动画**：光源位置绕 Y 轴旋转，立方体自转，展示动态光照效果

所有光照参数均可通过弹出的控制面板实时调节，场景支持自由视角漫游。

## 功能特性

### 1. 基础渲染

- 绘制 3D 立方体（每个面具有独立纹理坐标或法线）
- 支持深度测试，正确渲染遮挡关系
- 显示 RGB 坐标轴（红色 X、绿色 Y、蓝色 Z）

### 2. 摄像机系统（`Camera` 类）

- **位置**：自由移动（W/A/S/D）
- **视角**：鼠标控制偏航（Yaw）和俯仰（Pitch）
- **视野**：鼠标滚轮调节 FOV
- **实时反馈**：在主窗口显示摄像机位置、欧拉角、前向/右向/上向向量

### 3. 光照模型实验（按菜单选择）

| 菜单项              | 对应类            | 说明                                                         |
| :------------------ | :---------------- | :----------------------------------------------------------- |
| **ColorOfObject**   | `ColorOfObject`   | 最简单的物体颜色 + 光源颜色，通过顶点着色器传递颜色          |
| **PhongLight**      | `PhongLight`      | 逐片段光照（Phong 反射模型），包含环境光、漫反射、镜面反射   |
| **GouraudLight**    | `GouraudLight`    | 逐顶点光照（Gouraud 着色），与 Phong 对比性能与效果          |
| **Material**        | `Material`        | 可编辑的材质属性（ambient, diffuse, specular, shininess）和光源分量 |
| **CyanPlastic**     | `CyanPlastic`     | 预置的青色塑料材质效果演示                                   |
| **TextureLight**    | `TextureLight`    | 漫反射贴图 + 镜面反射贴图 + 发光贴图（自发光）               |
| **ParallelLight**   | `Parallel_Light`  | 方向光（模拟太阳），只有方向，无位置衰减                     |
| **PointLight**      | `PointLight`      | 点光源，支持常数/一次/二次衰减系数                           |
| **SpotLight**       | `SpotLight`       | 聚光灯，带内锥和外锥角度（硬边缘）                           |
| **SpotLightSmooth** | `SpotLightSmooth` | 平滑聚光灯，内外锥之间平滑过渡                               |
| **MultLight**       | `MultLight`       | 多光源场景：1个平行光 + 2个点光源 + 2个聚光灯，每个光源有不同颜色 |

### 4. 实时调节参数

每个光照场景都会弹出一个独立的控制对话框，允许调整：

- 光源位置/方向/颜色
- 物体漫反射/镜面反射/环境光分量
- 高光反光度（shininess）
- 衰减系数（constant, linear, quadratic）
- 聚光灯的内外切光角（cutOff, outerCutOff）

调节后场景立即更新。

### 5. 动画与交互

- **空格键**：开始/停止光源旋转和物体自转动画
- **鼠标右键拖拽**：旋转摄像机视角（仅在 `Preview` 控件中获得焦点时有效）
- **W/A/S/D**：移动摄像机

## 编译与运行

### 依赖环境

- **Qt** 5.12 或更高版本（需要 `core`, `gui`, `opengl`, `widgets`, `openglwidgets` 模块）
- **OpenGL** 3.3 及以上（深度测试、纹理、多光源需要）
- **C++17** 兼容编译器（MSVC 2019+ / GCC 7+ / Clang 10+）

### 构建步骤（Qt Creator）

1. 用 Qt Creator 打开项目根目录下的 `.pro` 文件。
2. 确保构建套件（Kit）已配置正确，且 Qt 版本包含 OpenGL 支持。
3. 点击“构建” -> “运行”。

### 命令行构建（qmake）

bash

```
qmake
make
./your_program_name
```



### 资源文件说明

项目依赖两个资源文件（需正确添加到 `.pro` 中的 `RESOURCES`）：

- `img.qrc`：包含所有纹理图片（`wall.jpg`, `awesomeface.png`, `container2.png`, `container2_specular.png` 等）以及各场景所需的贴图。
- `shader.qrc`：包含所有顶点着色器和片段着色器（`.vert` / `.frag` 文件）。

若运行时出现纹理或着色器加载失败，请检查资源路径是否正确。

## 操作指南

### 启动程序

- 程序启动后默认显示“ColorOfObject”场景，并弹出一个控制面板。
- 主窗口顶部有菜单栏，可选择不同的光照实验。

### 菜单导航

- **场景切换**：点击菜单栏中的项目（如 `PhongLight`, `PointLight` 等）即可切换。
- **视图控制**：
  - 鼠标在 `Preview` 窗口内**右键拖拽**旋转视角（需确保窗口获得焦点）。
  - 键盘 `W`/`S`/`A`/`D` 移动摄像机。
  - 鼠标滚轮缩放视野。
- **动画**：按 **空格键** 开始/停止自动旋转立方体（光源位置也会随之移动，动态展示光照变化）。

### 调节参数

切换场景后，会自动弹出该场景对应的控制对话框。调整任意滑块或输入框，3D 视图会实时响应。例如：

- 在 `PointLight` 场景中，可以调节光源的 `constant`, `linear`, `quadratic` 观察衰减效果。
- 在 `Material` 场景中，可以分别调节物体的环境、漫反射、镜面反射颜色和光源的对应分量。

### 退出

关闭主窗口即可。

## 项目结构

| 文件/类                   | 职责                                                         |
| :------------------------ | :----------------------------------------------------------- |
| `main.cpp`                | 程序入口，创建 `MainWindow`                                  |
| `mainwindow.h/cpp`        | 主 UI 框架，菜单绑定，场景切换逻辑                           |
| `preview.h/cpp`           | 核心 OpenGL 绘制控件，管理所有场景的初始化、渲染循环、摄像机交互 |
| `camera.h/cpp`            | 第一人称摄像机，生成视图矩阵，处理键盘/鼠标输入              |
| `axis.h/cpp`              | 绘制 RGB 坐标轴（独立着色器，分别用红绿蓝绘制）              |
| `vertices.h/cpp`          | 简单封装顶点数组和索引数组，便于管理                         |
| `color_of_object.h/cpp`   | 第一场景：物体颜色 + 光源颜色（无镜面反射）                  |
| `phong_light.h/cpp`       | Phong 光照模型（逐片段）                                     |
| `gouraud_light.h/cpp`     | Gouraud 光照模型（逐顶点）                                   |
| `material.h/cpp`          | 材质系统（物体材质 + 光源分量分离）                          |
| `cyan_plastic.h/cpp`      | 预定义青色塑料材质演示                                       |
| `texture_light.h/cpp`     | 纹理光照（漫反射贴图、镜面反射贴图、发光贴图）               |
| `parallel_light.h/cpp`    | 平行光（方向光）                                             |
| `point_light.h/cpp`       | 点光源（位置衰减）                                           |
| `spot_light.h/cpp`        | 聚光灯（带内锥角）                                           |
| `spot_light_smooth.h/cpp` | 平滑边缘聚光灯（内锥+外锥）                                  |
| `mult_light.h/cpp`        | 多光源组合（平行光 + 2点光源 + 2聚光灯）                     |

### 数据流向

1. `MainWindow` 通过菜单选择 `Scene` 枚举，调用 `Preview::setCurrentScene()`。
2. `Preview` 根据当前场景激活对应的光照对象（如 `phongLight`），并将其 `projection`, `view`, `model` 等矩阵传入着色器。
3. 光照对象内部存储其特有的参数（光源颜色、位置、衰减系数等），并在 `updateShapeShader()` 中绑定纹理和设置 uniform。
4. 每帧 `paintGL()` 调用 `drawModule()`，根据场景选择执行 `DrawXXX()` 函数，该函数更新 MVP 矩阵并调用相应光照对象的 `updateShapeShader()`，然后执行 `glDrawArrays`。
5. 同时，`Preview` 中的摄像机 `pCamera_` 会实时计算视图矩阵，并传递给当前光照对象。

## 扩展与定制

若想添加新的光照模型或场景，可以：

1. 在 `data_type.h` 中的 `Scene` 枚举增加新值。
2. 创建新的类（如 `MyNewLight`），继承 `QDialog`，实现 `initShader()`, `initTexture()`, `updateShapeShader()`, `updateLightShader()` 等方法。
3. 在 `Preview` 中添加该类的成员变量，并在 `initializeGL()` 中调用其 `initShader()` 和 `initTexture()`。
4. 在 `Preview::drawModule()` 中添加新的 case，实现绘制逻辑。
5. 在 `MainWindow::initAction()` 中添加新的 QAction 并绑定到场景。

## 常见问题

1. **纹理显示为黑色**
   检查图片路径是否正确，资源文件是否编译进程序，纹理 ID 是否与着色器中 uniform 一致。
2. **光照效果过于强烈或太暗**
   请调整环境光强度（ambient strength）或光源颜色分量。
3. **摄像机无法移动**
   确保 `Preview` 窗口获得了键盘焦点（点击一下画面）。另外，W/A/S/D 仅当选择任意场景时均有效。
4. **多光源场景性能下降**
   对于大量光源，片段着色器中循环计算光照会消耗 GPU 资源。本演示中的光源数量已控制在合理范围。

## 许可证

本项目为教学演示代码，可自由使用、修改和分发。

## 致谢

项目参考了 LearnOpenGL CN 教程中的光照章节，并基于 Qt 框架进行了完整实现与扩展。

------

**Enjoy exploring the world of OpenGL lighting!**
如果有任何问题或建议，欢迎反馈。