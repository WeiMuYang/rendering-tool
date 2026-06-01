# OpenGL 基础渲染

一个基于 Qt 和 OpenGL 的 3D 图形教学演示程序，涵盖了现代图形学的基础知识：顶点数据、着色器、纹理映射、变换矩阵、模型-视图-投影（MVP）、摄像机控制等。该项目适合学习 OpenGL 渲染管线和 Qt 图形开发。

## 功能特性

- **多种图元绘制**：点、线、面模式切换；三角形、矩形、立方体。
- **颜色与纹理**：
  - 统一颜色（Uniform）、逐顶点颜色（Attribute）
  - 纹理映射（支持多纹理混合）
  - 纹理包裹方式：`REPEAT`、`MIRRORED_REPEAT`、`CLAMP_TO_BORDER`、`CLAMP_TO_EDGE`
  - 纹理过滤方式：`NEAREST`、`LINEAR` 及各类 Mipmap 滤波
- **几何变换**：位移、旋转（可指定轴和角度）、缩放，实时更新模型矩阵。
- **三维投影**：透视投影（FOV、宽高比、近平面、远平面可调）。
- **多物体实例**：一次绘制多个不同位置、旋转的立方体。
- **第一人称摄像机**：
  - 键盘 `W/A/S/D` 前后左右移动
  - 鼠标控制视角偏航（Yaw）和俯仰（Pitch）
  - 滚轮改变视野（Zoom）
  - 实时显示摄像机位置、欧拉角、朝向向量、右向量、上向量、世界向上向量
- **辅助功能**：显示 RGB 坐标轴（X 红、Y 绿、Z 蓝）。

## 项目结构

| 文件               | 说明                                                      |
| :----------------- | :-------------------------------------------------------- |
| `main.cpp`         | 程序入口，启动 `MainWindow`                               |
| `mainwindow.h/cpp` | 主窗口 UI 逻辑，连接菜单与 `Preview` 控件，控制各模块参数 |
| `preview.h/cpp`    | 核心 OpenGL 绘制控件，管理着色器、VAO/VBO、纹理、渲染循环 |
| `camera.h/cpp`     | 第一人称摄像机类，处理键盘/鼠标/滚轮输入，生成视图矩阵    |
| `vertices.h/cpp`   | 管理顶点数据和索引数据的辅助类                            |
| `data_type.h`      | 枚举定义（`Module`、`DrawMode`、`TexWrap`、`TexFilter`）  |
| `mainwindow.ui`    | UI 布局文件（不在此处展示，但存在于工程中）               |

## 依赖项

- **Qt 5** 或 **Qt 6**（使用 `core`, `gui`, `opengl`, `widgets`, `openglwidgets` 模块）
- **OpenGL**（至少支持 OpenGL 2.1；Mipmap 等功能需要 3.0+，但本代码兼容性好）
- 编译器支持 C++17

## 编译与运行

### 使用 Qt Creator

1. 打开项目根目录下的 `.pro` 文件。
2. 配置构建套件（Kit），确保包含 OpenGL 开发库（通常默认已包含）。
3. 点击“构建”并运行。

### 使用命令行（qmake）

bash

```
qmake
make
./your_program_name
```



### 资源文件

项目需要两个资源文件：

- `img.qrc`：包含 `wall.jpg`、`awesomeface.png`、`small.png` 等纹理图片。
- `shader.qrc`：包含顶点和片段着色器文件（`.vert`/`.frag`）。

请确保这些资源存在且路径正确。

## 操作指南

### 选择渲染模块

通过主窗口的菜单栏选择要演示的功能：

| 菜单项              | 对应模块                | 说明                                        |
| :------------------ | :---------------------- | :------------------------------------------ |
| 三角形              | `isTriangle`            | 一个简单的彩色三角形                        |
| 矩形                | `isRectPos`             | 带统一颜色的矩形                            |
| 矩形（逐顶点颜色）  | `isRectPosCol`          | 每个顶点颜色不同                            |
| 纹理着色器          | `isRectPosColTex`       | 矩形贴两张纹理（墙壁+笑脸），可调节混合比例 |
| 纹理包裹            | `isRectPosColTexWrap`   | 演示纹理的四种包裹方式                      |
| 纹理过滤            | `isRectPosColTexFilter` | 演示纹理的缩小/放大过滤方式                 |
| 位移/旋转/缩放      | `isRectTranRotaScale`   | 对矩形做变换矩阵操作                        |
| 3D 立方体           | `isBox3dMVP`            | 单个带纹理的立方体，可调 MVP 矩阵           |
| 多个立方体          | `isManyBox3d`           | 屏幕上绘制多个不同位置的立方体              |
| 摄像机（WASD+鼠标） | `isCameraWSADMouse`     | **推荐体验**：自由视角漫游                  |

### 常规控制

- **绘制模式**：菜单栏 `点` / `线` / `填充` 改变图元显示方式。
- **参数调节**：主窗口右侧（或下方）有对应的数值输入框，可实时调整颜色、纹理比例、位移、旋转、缩放、投影参数、摄像机信息等。
- **摄像机模块**（当选择 `摄像机（WASD+鼠标）` 时）：
  - `W` / `S`：前后移动
  - `A` / `D`：左右移动
  - 鼠标移动：环顾四周（偏航+俯仰）
  - 鼠标滚轮：改变视野（Zoom）
- **其他模块**：摄像机为静态位置，但仍可通过 UI 调整 `View` 矩阵的位移（`view_tran_x/y/z`）来模拟平移视图。

### 纹理与过滤参数

- **纹理包裹**：下拉框选择，立即更新纹理坐标超出 [0,1] 时的行为。
- **纹理过滤**：可选择缩小和放大时的插值方式，Mipmap 相关选项需要纹理生成 Mipmap（代码中已为 `small.png` 生成）。

## 代码结构说明

### `Preview` 类（核心绘制）

- 继承 `QOpenGLWidget` 和 `QOpenGLFunctions`。
- 生命周期：`initializeGL` → `resizeGL` → `paintGL`。
- 管理多个 VAO/VBO：一个用于坐标轴，一个用于当前模型。
- 包含多个着色器程序（`shaderProTri`, `shaderProRectUniform`, `shaderProBox3dMVP` 等），通过 `currentModelType_` 选择激活。
- 纹理初始化在 `initTexture()` 中，每个模块绘制前会调用 `setTexture()` 绑定纹理并设置参数。
- 键盘/鼠标事件通过重写 `keyPressEvent`、`mouseMoveEvent`、`wheelEvent` 传递给 `Camera` 对象。

### `Camera` 类

- 存储位置、世界向上向量、欧拉角（Yaw, Pitch）、移动速度、灵敏度、视野。
- `GetViewMatrix()` 调用 `QMatrix4x4::lookAt` 生成视图矩阵。
- `ProcessKeyboard`：更新位置。
- `ProcessMouseMovement`：更新 Yaw 和 Pitch，重新计算 Front、Right、Up 向量。
- `ProcessMouseScroll`：更新 Zoom。
- 通过信号槽将摄像机状态回传到主窗口 UI。

### `Vertices` 辅助类

- 简单封装顶点数组和索引数组，存储长度和指针，便于多种数据切换。

## 注意事项

- 所有 OpenGL 调用如果不在 `paintGL()` 中执行，需要先调用 `makeCurrent()`，完成后调用 `doneCurrent()`。
- 纹理图片默认使用 `.mirrored()` 反转 Y 轴，以匹配 OpenGL 的纹理坐标原点（左下）。
- 深度测试 `glEnable(GL_DEPTH_TEST)` 已开启，确保立方体表面遮挡正确。
- 透明度混合 `glEnable(GL_BLEND)` 已开启，混合因子为 `GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA`，适用于 PNG 图片透明区域。

## 扩展建议

- 增加法线贴图或光照模型。
- 支持加载外部 3D 模型（如 OBJ 格式）。
- 增加摄像机“飞鸟模式”或“轨道控制”。
- 添加更多纹理过滤方式的对比显示

## 许可证

本项目仅供学习交流使用，代码可随意修改和分发。 

------

**Enjoy OpenGL with Qt!**
