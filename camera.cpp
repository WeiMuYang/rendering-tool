#include "camera.h"

// 默认值
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

Camera::Camera(QObject *parent)
    : QObject{parent}
{
}

// constructor with vectors
Camera::Camera(QVector3D position, QVector3D up, float yaw, float pitch)
    : Front(QVector3D(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}
// constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : Front(QVector3D(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = QVector3D(posX, posY, posZ);
    WorldUp = QVector3D(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
QMatrix4x4 Camera::GetViewMatrix()
{
    // View矩阵，view.lookAt(cameraPos，cameraTarget, QVector3D(0.0f, 1.0f, 0.0f) );
    // View矩阵最终乘到物体的顶点坐标，也就是将相机中的物体进行移动，模拟一种相机在动的状态
    // lookAt实现的效果是，获取物体朝着相机移动方向的变化矩阵的逆
    QMatrix4x4 theMatrix;
    theMatrix.lookAt(Position, Position + Front, Up);
    return theMatrix;
}

// 处理从任何类似键盘的输入系统接收的输入。接受摄像机定义枚举形式的输入参数（从窗口系统中提取）
void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
    // 移动的速度和电脑的刷新速度有关
    // MovementSpeed刷新一次移动的距离
    // deltaTime是刷新间隔

    float velocity = MovementSpeed * deltaTime;
    switch (direction) {
    case FORWARD:
        Position += Front * velocity;
        break;
    case BACKWARD:
        Position -= Front * velocity;
        break;
    case LEFT:
        Position -= Right * velocity;
        break;
    case RIGHT:
        Position += Right * velocity;
        break;
    default:
        break;
    }
    emit sigCameraPositionInfo(Position);
}

// 处理从鼠标输入系统接收的输入。需要x和y方向上的偏移值。
// 鼠标只是确定方向
void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw   += xoffset; // 偏航
    Pitch += yoffset; // 俯仰

    // 确保当投球超出边界时，屏幕不会翻转
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // 使用更新的Euler角度更新前、右和上矢量
    updateCameraVectors();
    emit sigCameraYawPitchInfo(Yaw, Pitch);
}

// 处理从鼠标滚轮事件接收的输入。仅需要在垂直车轮轴上输入
void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 75.0f)
        Zoom = 75.0f;
}

// 根据相机的（更新的）Euler角度计算前矢量
void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    double PI=3.1415926;
    QVector3D front;
    front.setX(cos(Yaw*PI/180.0) * cos(Pitch*PI/180.0));
    front.setY( sin(Pitch*PI/180.0));
    front.setZ(sin(Yaw*PI/180.0) * cos(Pitch*PI/180.0));
    front.normalize();
    Front = front;
    // also re-calculate the Right and Up vector
    Right = QVector3D::crossProduct(Front, WorldUp);
    // 标准化向量，因为向上或向下看得越多，向量的长度就越接近0，这会导致移动速度变慢。
    Right.normalize();
    Up    = QVector3D::crossProduct(Right, Front);
    Up.normalize();

    emit sigCameraFrontRightUpInfo(Front, Right, Up, WorldUp);

}
