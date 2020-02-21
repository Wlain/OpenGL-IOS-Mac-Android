//
//  Camera.cpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/21.
//  Copyright © 2020 william. All rights reserved.
//

#include "Camera.hpp"
#include "Base.h"

Camera::Camera()
:mEyePosition(0.0f, 0.0f, 0.0f),
mTargetPosition(0.0f, 0.0f, -1.0f),
mUp(0.0f, 1.0f, 0.0f),
mIsMoveLeft(false),
mIsMoveRight(false),
mIsMoveForward(false),
mIsMoveBack(false){
    
}
Camera::~Camera() {
    
}

void Camera::Update(float deltaTime) {
    float moveSpeed = 10.0f;
    Vector3f forWardDirection = mTargetPosition - mEyePosition;
    // 单位化之后只有方向上的几何意义
    forWardDirection.Normalize();
    Vector3f rightDirection;
    Vector3f::cross(forWardDirection, mUp, &rightDirection);
    rightDirection.Normalize();
    if (mIsMoveLeft) {
        Vector3f delta = rightDirection * deltaTime * moveSpeed;
        mEyePosition -= delta;
        mTargetPosition -= delta;
    }
    if (mIsMoveRight) {
        Vector3f delta = rightDirection * deltaTime * moveSpeed;
        mEyePosition += delta;
        mTargetPosition += delta;
    }
    if (mIsMoveForward) {
        Vector3f delta = forWardDirection * deltaTime * moveSpeed;
        mEyePosition += delta;
        mTargetPosition += delta;
    }
    if (mIsMoveBack) {
        Vector3f delta = forWardDirection * deltaTime * moveSpeed;
        mEyePosition -= delta;
        mTargetPosition -= delta;
    }
    glLoadIdentity();
    gluLookAt(mEyePosition.x, mEyePosition.y, mEyePosition.z,
              mTargetPosition.x, mTargetPosition.y, mTargetPosition.z,
              mUp.x, mUp.y, mUp.z);
    
    
}
