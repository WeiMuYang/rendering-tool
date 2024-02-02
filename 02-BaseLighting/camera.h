#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QMatrix4x4>
#include <QVector3D>

// 移动方向 // 我们这里是WSAD
enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// 相机移动的原理：就是根据相机移动的方向，生成View矩阵，将View矩阵乘以模型的顶点上。
//              通过实现模型顶点的移动，实现好像相机发生了变化
//              View矩阵是通过调用LookAt函数是实现，实际结果就是 相机移动和旋转的 逆矩阵
//              因为View乘到模型顶点上，相当于模型在向相机的移动反方向在移动和旋转
class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QObject *parent = nullptr);
    // constructor with vectors    yaw = -90.0f指的是 正对屏幕
    Camera(QVector3D position = QVector3D(0.0f, 0.0f, 0.0f), QVector3D up = QVector3D(0.0f, 1.0f, 0.0f),
           float yaw = -90.0f, float pitch = 0.0f);
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
           float yaw, float pitch);
    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    QMatrix4x4 GetViewMatrix();

    // 处理从任何类似键盘的输入系统接收的输入。接受摄像机定义枚举形式的输入参数（从窗口系统中提取）
    void ProcessKeyboard(CameraMovement direction, float deltaTime);

    // 处理从鼠标输入系统接收的输入。需要x和y方向上的偏移值。
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    // 处理从鼠标滚轮事件接收的输入。仅需要在垂直车轮轴上输入
    void ProcessMouseScroll(float yoffset);

    // 根据相机的（更新的）Euler角度计算前矢量
    void updateCameraVectors();

signals:
    void sigCameraPositionInfo(QVector3D value);
    void sigCameraYawPitchInfo(float yaw, float pitch);
    void sigCameraFrontRightUpInfo(QVector3D f, QVector3D r, QVector3D u,QVector3D wu);

public:
    // camera Attributes
    // QMatrix4x4 view;
    // view.lookAt(cameraPos，cameraTarget, QVector3D(0.0f, 1.0f, 0.0f) );
    //              Position, Position + Front, Up
    QVector3D Position;  // 相机位置
    QVector3D Front;     // 相机移动方向和大小 键盘的话是 (0,0,-1)
    QVector3D Up;        //           Right × Front
    QVector3D Right;     //           Front × Up
    QVector3D WorldUp;   // 始终是： 0.0f, 1.0f, 0.0f
    // euler Angles
    float Yaw;   // 偏航，鼠标的 x 方向控制 Yaw的角度
    float Pitch; // 俯仰，鼠标的 y 方向控制 Pitch的角度
    // camera options
    float MovementSpeed;
    float MouseSensitivity;

    // 相机参数
    float fov;   // Zoom可以控制
    float aspectRatio;
    float nearPlane;
    float farPlane;
};

#endif // CAMERA_H
