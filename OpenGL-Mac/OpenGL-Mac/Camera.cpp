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
mIDMoveBack(false){
    
}
Camera::~Camera() {
    
}

void Camera::Update(float deltaTime) {
    float moveSpeed = 10.0f;
    if (mIsMoveLeft) {
        float delta = deltaTime * moveSpeed;
        mEyePosition.x -= delta;
        mTargetPosition.x -= delta;
    }
    if (mIsMoveRight) {
        float delta = deltaTime * moveSpeed;
        mEyePosition.x += delta;
        mTargetPosition.x += delta;
    }
    if (mIsMoveForward) {
        float delta = deltaTime * moveSpeed;
        mEyePosition.z -= delta;
        mTargetPosition.z -= delta;
    }
    if (mIDMoveBack) {
        float delta = deltaTime * moveSpeed;
        mEyePosition.z += delta;
        mTargetPosition.z += delta;
    }
    glLoadIdentity();
    gluLookAt(mEyePosition.x, mEyePosition.y, mEyePosition.z,
              mTargetPosition.x, mTargetPosition.y, mTargetPosition.z,
              mUp.x, mUp.y, mUp.z);
    
    
}
