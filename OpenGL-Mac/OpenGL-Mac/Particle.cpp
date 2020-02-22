//
//  Particle.cpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/22.
//  Copyright © 2020 william. All rights reserved.
//

#include "Particle.hpp"

Particle::Particle()
:mTexture(0),
mHalfSize(0.0f),
mLifeTime(0.0f),
mCurrentTime(0.0f),
mEndTime(0.0f),
mPosition(0.0f, 0.0f, 0.0f){
    memset(&mColor[0], 0, sizeof(GLubyte));
    memset(&mColor[1], 0, sizeof(GLubyte));
    memset(&mColor[2], 0, sizeof(GLubyte));
    memset(&mColor[3], 0, sizeof(GLubyte));
}

Particle::~Particle () {
    
}

GLuint Particle::GetTexture() const {
    return this->mTexture;
}

void Particle::SetTexture(GLuint texture) {
    this->mTexture = texture;
}

float Particle::GetHalfSize() const {
    return this->mHalfSize;
}

void Particle::SetHalfSize(float size) {
    this->mHalfSize = size;
}

float Particle::GetLifeTime() const {
    return this->mLifeTime;
}

void Particle::SetLifeTime(float time) {
    this->mLifeTime = time;
}

float Particle::GetStartTime() const {
    return this->mStartTime;
}

void Particle::SetStartTime(float time) {
    this->mStartTime = time;
}

float Particle::GetCurrentTime() const {
    return this->mCurrentTime;
}

void Particle::SetCurrentTime(float time) {
    this->mCurrentTime = time;
}

float Particle::GetEndTime() const {
    return this->mEndTime;
}

void Particle::SetEndTime(float time) {
    this->mEndTime = time;
}

GLubyte* const Particle::GetColor() {
    return this->mColor;
}

void Particle::SetColor(GLubyte color[]) {
    this->mColor[0] = color[0];
    this->mColor[1] = color[1];
    this->mColor[2] = color[2];
    this->mColor[3] = color[3];
}

const Vector3f& Particle::GetPosition() const {
    return this->mPosition;
}

void Particle::SetPosition(const Vector3f &v) {
    this->mPosition = v;
}

void Particle::Init(GLubyte r, GLubyte g, GLubyte b, GLubyte a, float life) {
    mLifeTime = life;
    mColor[0] = r;
    mColor[1] = g;
    mColor[2] = b;
    mColor[3] = a;
}

void Particle::Draw() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glColor4ubv(mColor);
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(mPosition.x - mHalfSize, mPosition.y - mHalfSize, mPosition.z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(mPosition.x + mHalfSize, mPosition.y - mHalfSize, mPosition.z);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(mPosition.x - mHalfSize, mPosition.y + mHalfSize, mPosition.z);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(mPosition.x - mHalfSize, mPosition.y + mHalfSize, mPosition.z);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(mPosition.x + mHalfSize, mPosition.y + mHalfSize, mPosition.z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(mPosition.x + mHalfSize, mPosition.y - mHalfSize, mPosition.z);
    glEnd();
    glDisable(GL_BLEND);
}

void Particle::Update(float deltaTime) {
    if (mCurrentTime > mLifeTime) {
        return;
    }
    mCurrentTime += deltaTime;
    float maxRadius = 300.0f;
    float rotateSpeed = 60.0f;
    float currentAngle = rotateSpeed * mCurrentTime;
    float currentRadius = maxRadius * mCurrentTime / mLifeTime;
    mPosition.x = currentRadius * cosf(currentAngle * MATH_PI / 180);
    mPosition.y = currentRadius * sinf(currentAngle * MATH_PI / 180);
}
