# 模型加载与光源

本项目是一个基于 Qt 和 OpenGL 的 3D 渲染教学程序，集成了模型加载（Assimp）、多种光照模型、纹理映射和材质系统。通过该程序，用户可以学习如何导入外部 3D 模型，并为模型应用漫反射贴图、镜面反射贴图，同时动态调节光源参数（平行光、点光源等），观察不同光照条件下的渲染效果。

## 功能特性

- **3D 模型加载**：使用 Assimp 库解析主流 3D 模型格式（如 obj、fbx、gltf 等），自动提取顶点、法线、纹理坐标和材质信息。
- **纹理光照**：支持漫反射贴图（diffuse map）和镜面反射贴图（specular map），实现基于纹理的光照计算。
- **光源系统**：内置**平行光（方向光）**，可调节光源方向、环境光、漫反射和镜面反射分量。
- **第一人称摄像机**：WASD 移动、鼠标拖拽旋转视角、滚轮缩放视野。
- **实时参数调节**：通过控制面板动态修改光源位置/方向/颜色、材质反光度（shininess）等。
- **辅助功能**：显示 RGB 坐标轴（X 红、Y 绿、Z 蓝），便于观察物体在三维空间中的方位。

## 编译与运行

### 依赖项

| 组件       | 说明                                                         |
| :--------- | :----------------------------------------------------------- |
| **Qt**     | 5.12 或更高版本（需要 `core`, `gui`, `opengl`, `widgets`, `openglwidgets` 模块） |
| **OpenGL** | 支持 OpenGL 3.3 及以上                                       |
| **Assimp** | Open Asset Import Library，用于加载 3D 模型（需自行编译或通过包管理器安装） |
| **C++**    | 支持 C++17 的编译器（MSVC 2019+ / GCC 9+ / Clang 10+）       |

### 配置 Assimp（以 Ubuntu 为例）

bash

```
sudo apt-get install libassimp-dev
```



在 Qt 项目的 `.pro` 文件中添加：

qmake

```
LIBS += -lassimp
```



### 构建步骤（Qt Creator）

1. 用 Qt Creator 打开项目根目录下的 `.pro` 文件。
2. 确保 Assimp 库已正确链接（若未自动找到，需在 `LIBS` 中指定路径）。
3. 选择构建套件，点击“构建” -> “运行”。

### 资源文件

项目依赖两个资源文件（已在 `.pro` 中配置）：

- `00-axis`：坐标轴渲染所需的着色器。
- `01-box-3d`：内置立方体模型（`box_container2.png` 等纹理）及对应的着色器。
- `02-load-model`：外部模型加载所需的着色器和默认纹理（`load_container2.png`, `load_container2_specular.png`）。

若加载外部模型失败，请检查模型文件路径及纹理文件是否存在。

## 操作指南

### 界面概览

- 主窗口：显示 3D 渲染视图（`Preview` 控件）。
- 控制面板：程序启动时自动弹出（`Box3D` 或 `ModelShaderTexture` 对应的对话框），可调节光照和材质参数。

### 默认场景

程序启动后默认显示一个带纹理的立方体（平行光照明）。用户可通过修改代码切换到模型加载场景（详见“扩展与定制”）。

### 摄像机控制

| 操作             | 功能                    |
| :--------------- | :---------------------- |
| **W/A/S/D**      | 前后左右移动摄像机      |
| **鼠标右键拖拽** | 旋转视角（偏航 + 俯仰） |
| **鼠标滚轮**     | 缩放视野（FOV）         |

*注意：需要确保 `Preview` 控件获得键盘焦点（点击一下画面）*

### 光照参数调节（以 `Box3D` 为例）

控制面板包含以下可调参数：

| 分组         | 参数                             | 说明                                                        |
| :----------- | :------------------------------- | :---------------------------------------------------------- |
| **光源属性** | `lightPos` (X/Y/Z)               | 光源位置（仅对点光源有效，平行光使用方向）                  |
|              | `lightDirection` (X/Y/Z)         | 平行光的方向向量                                            |
|              | `lightColor` (R/G/B)             | 光源颜色                                                    |
|              | `ambient`, `diffuse`, `specular` | 光源对环境光、漫反射、镜面反射的贡献强度                    |
| **材质属性** | `shininess`                      | 高光反光度（值越大高光点越小）                              |
| **纹理切换** | `diffuseTexID`, `specularTexID`  | 选择使用的漫反射/镜面反射贴图（演示中可改为无效ID禁用贴图） |

修改任意参数，场景会实时更新。

## 代码结构

| 文件                          | 职责                                                         |
| :---------------------------- | :----------------------------------------------------------- |
| `axis.h/cpp`                  | 绘制 RGB 坐标轴（使用独立着色器，分别输出红/绿/蓝）          |
| `box3d.h/cpp`                 | 内置立方体场景：包含顶点数据（位置+法线+纹理坐标）、纹理加载、平行光光照计算 |
| `model_shader_texture.h/cpp`  | 模型加载场景的着色器和纹理管理（结构与 `Box3D` 类似）        |
| `model.h/cpp`                 | 使用 Assimp 加载模型，解析节点、网格、材质，生成 `Mesh` 列表 |
| `mesh.h/cpp`                  | 单个网格的 OpenGL 资源管理（VAO, VBO, EBO）和绘制函数        |
| `preview.h/cpp`（未完整提供） | 主渲染控件，管理 OpenGL 初始化、摄像机、场景切换和绘制循环   |

### 数据流

1. `Box3D::initShader()` 编译着色器，`initTexture()` 加载纹理。
2. `Box3D::updateShapeShader()` 更新 uniform（MVP 矩阵、光源参数、材质参数），并绑定纹理。
3. `Preview` 在 `paintGL()` 中调用 `Draw()` 函数，传入摄像机矩阵，执行 `glDrawArrays` 绘制立方体。
4. 模型加载流程：`Model` 类通过 Assimp 读取文件 → 生成 `Mesh` 对象 → `Mesh::Draw()` 设置纹理单元并绘制。

## 扩展与定制

### 切换到模型加载模式

当前代码未提供完整的 `Preview` 和 `MainWindow` 实现，但你可以按以下步骤启用模型加载：

1. 在 `Preview` 中添加 `ModelShaderTexture` 成员。
2. 在 `initializeGL()` 中调用其 `initShader()` 和 `initTexture()`。
3. 在 `paintGL()` 中调用 `ModelShaderTexture::updateShapeShader()`，然后使用 `Model` 类加载一个模型文件（例如 `backpack.obj`），并调用其 `Draw()` 方法。

示例代码片段：

cpp

```
// 在 Preview 类中
Model myModel;
myModel.loadModel("path/to/model.obj");

// 在绘制循环中
modelShaderTexture.updateShapeShader();
myModel.Draw(modelShaderTexture.shader_Shape);
```



### 添加新的光源类型

参考 `Box3D` 中的平行光实现，可以增加点光源、聚光灯的光照计算。只需在片段着色器中添加相应代码，并在 C++ 端传递对应的 uniform 参数。

### 修改默认模型或纹理

- 内置立方体：修改 `Box3D_01` 数组的顶点数据。
- 纹理：替换资源文件中的图片，或修改 `initTexture()` 中的加载路径。

## 常见问题

### 1. 编译时提示找不到 `assimp/assimp.hpp`

确保 Assimp 开发包已安装，并在 `.pro` 文件中正确添加了 `INCLUDEPATH` 和 `LIBS`。

### 2. 加载模型后纹理显示为黑色

- 检查模型文件关联的纹理路径是否正确（Assimp 会返回纹理文件名，需要程序自行拼接完整路径）。
- 确保纹理图片格式受 OpenGL 支持（常见如 PNG、JPG）。

### 3. 光照效果不正确

- 确认法线数据是否正确加载（可在着色器中临时输出法线颜色进行调试）。
- 检查光源方向是否归一化（在着色器中应对 `light.direction` 进行归一化）。

### 4. 摄像机无法移动

- 确认 `Preview` 控件获得了焦点（点击一下画面）。
- 检查 `keyPressEvent` 和 `mouseMoveEvent` 是否正确调用了 `Camera` 类的方法。

## 许可证

本项目为教学演示代码，可自由使用、修改和分发。使用时请保留原始作者信息（若有）。

## 参考与致谢

- [LearnOpenGL CN](https://learnopengl-cn.github.io/) – 光照与模型加载教程
- [Assimp 官方文档](http://www.assimp.org/)
- Qt 官方 OpenGL 示例

------

**Enjoy rendering with Qt, OpenGL and Assimp!**