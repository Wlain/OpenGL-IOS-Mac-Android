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
mUpDirection(0.0f, 1.0f, 0.0f),
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
    Vector3f::cross(forWardDirection, mUpDirection, &rightDirection);
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
              mUpDirection.x, mUpDirection.y, mUpDirection.z);
}

void Camera::SetPitch(float angle) {
    Vector3f viewDirection = mTargetPosition - mEyePosition;
    viewDirection.Normalize();
    // 叉乘：右手螺旋法则
    Vector3f rightDirection;
    Vector3f::cross(viewDirection, mUpDirection, &rightDirection);
    rightDirection.Normalize();
    RotateView(angle, rightDirection.x, rightDirection.y, rightDirection.z);
}

void Camera::SetYaw(float angle) {
    RotateView(angle, mUpDirection.x, mUpDirection.y, mUpDirection.z);
}

void Camera::SetRoll(float angle) {
    
}

void Camera::RotateView(float angle, float x, float y, float z) {
    // 视线方向
    Vector3f viewDirection = mTargetPosition - mEyePosition;
    Vector3f newDirection(0.0, 0.0, 0.0);
    // 矩阵 * 方向向量 （以下是3d中，绕任意轴旋转的矩阵公式）
    float c = cosf(angle);
    float s = sinf(angle);
    Vector3f tempX(c + x * x * (1.0 - c),  x * y * (1.0 - c) - x * s, x * z * (1.0 - c) + y * s);
    newDirection.x = tempX.dot(viewDirection);
    Vector3f tempY(x * y * (1.0 - c) + z * s, c + y * y *(1.0 - c), y * z * (1.0 - c) - x * s);
    newDirection.y = tempY.dot(viewDirection);
    Vector3f tempZ(x * z * (1.0 - c) - y * s, y * z * (1.0 - c) + x * s, x + z * z * (1.0 - c));
    newDirection.z = tempZ.dot(viewDirection);
    viewDirection = mEyePosition + newDirection;
 }

void Camera::ChangeTo3D() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)mViewPortWidth/(float)mViewPortHeight, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Camera::ChangeTo2D() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-mViewPortWidth / 2, mViewPortWidth / 2,
            -mViewPortHeight / 2, mViewPortHeight / 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

bool Camera::GetIsMoveLeft() const {
    return this->mIsMoveLeft;
}

void Camera::SetIsMoveLeft(bool isMoveLeft) {
    this->mIsMoveLeft = isMoveLeft;
}

bool Camera::GetIsMoveRight() const {
    return this->mIsMoveRight;
}

void Camera::SetIsMoveRight(bool isMoveRight) {
    this->mIsMoveRight = isMoveRight;
}


bool Camera::GetMoveForward() const {
    return this->mIsMoveForward;
}

void Camera::SetIsMoveForward(bool isMoveForward) {
    this->mIsMoveForward = isMoveForward;
}

bool Camera::GetIsMoveBack() const {
    return this->mIsMoveBack;
}

void Camera::SetIsMoveBack(bool isMoveBack) {
    this->mIsMoveBack = isMoveBack;
}

int Camera::GetViewPortWidth() const {
    return this->mViewPortWidth;
}

void Camera::SetViewPortWidth(int viewPortWidth) {
    this->mViewPortWidth = viewPortWidth;
}

int Camera::GetViewPortHeight() const {
    return this->mViewPortHeight;
}

void Camera::SetViewPortHeight(int viewPortHeight) {
    this->mViewPortHeight = viewPortHeight;
}

const Vector3f& Camera::GetEyePosition() const {
    return this->mEyePosition;
}

void Camera::SetEyePosition(const Vector3f& v) {
    this->mEyePosition = v;
}

const Vector3f& Camera::GetTargetPosition() const {
    return this->mTargetPosition;
}

void Camera::SetTargetPosition(const Vector3f& v) {
    this->mTargetPosition = v;
}

const Vector3f& Camera::GetUpDirection() const {
    return this->mUpDirection;
}

void Camera::SetUpDirection(const Vector3f& v) {
    this->mUpDirection = v;
}



