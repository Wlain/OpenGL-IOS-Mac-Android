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
mPosition(0.0f, 0.0f, 0.0f),
mHalfSize(0.0f) {
    
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

const Vector3f& Particle::GetPosition() const {
    return this->mPosition;
}

void Particle::SetPosition(const Vector3f &v) {
    this->mPosition = v;
}

void Particle::Draw() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glColor4ub(255, 255, 255, 255);
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
