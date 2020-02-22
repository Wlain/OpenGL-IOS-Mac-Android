//
//  Camera.hpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/21.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "Vector3f.hpp"

class Camera {
public:
    Camera();
    ~Camera();
    // 设置当前摄像机的姿态
    void Update(float deltaTime);
    void SetPitch(float angle);
    void SetYaw(float angle);
    void SetRoll(float angle);
    // 旋转视点:绕任意轴旋转
    void RotateView(float angle, float x, float y, float z);
    void ChangeTo3D();
    void ChangeTo2D();
    bool GetIsMoveLeft() const;
    void SetIsMoveLeft(bool isMoveLeft);
    bool GetIsMoveRight() const;
    void SetIsMoveRight(bool isMoveRight);
    bool GetMoveForward() const;
    void SetIsMoveForward(bool isMoveForward);
    bool GetIsMoveBack() const;
    void SetIsMoveBack(bool isMoveBack);
    int GetViewPortWidth() const;
    void SetViewPortWidth(int viewPortWidth);
    int GetViewPortHeight() const;
    void SetViewPortHeight(int viewPortHeight);
    const Vector3f& GetEyePosition() const;
    void SetEyePosition(const Vector3f& v);
    const Vector3f& GetTargetPosition() const;
    void SetTargetPosition(const Vector3f& v);
    const Vector3f& GetUpDirection() const;
    void SetUpDirection(const Vector3f& v);
private:
    bool mIsMoveLeft;
    bool mIsMoveRight;
    bool mIsMoveForward;
    bool mIsMoveBack;
    int mViewPortWidth;
    int mViewPortHeight;
    Vector3f mEyePosition; 
    Vector3f mTargetPosition;
    Vector3f mUpDirection;
};

#endif /* Camera_hpp */
