//
//  Ground.cpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/20.
//  Copyright © 2020 william. All rights reserved.
//

#include "Ground.hpp"

Ground::Ground() {
    memset(mAmbientMaterial, 0, sizeof(mAmbientMaterial));
    memset(mDiffuseMaterial, 0, sizeof(mDiffuseMaterial));
    memset(mSpecularMaterial, 0, sizeof(mSpecularMaterial));
}

Ground::~Ground() {
    
}

void Ground::SetAmbientMaterial(float r, float g, float b, float a) {
    this->mAmbientMaterial[0] = r;
    this->mAmbientMaterial[1] = g;
    this->mAmbientMaterial[2] = b;
    this->mAmbientMaterial[3] = a;
}

void Ground::SetDiffuseMaterial(float r, float g, float b, float a) {
    this->mDiffuseMaterial[0] = r;
    this->mDiffuseMaterial[1] = g;
    this->mDiffuseMaterial[2] = b;
    this->mDiffuseMaterial[3] = a;
}

void Ground::SetSpecularMaterial(float r, float g, float b, float a) {
    this->mSpecularMaterial[0] = r;
    this->mSpecularMaterial[1] = g;
    this->mSpecularMaterial[2] = b;
    this->mSpecularMaterial[3] = a;
}

void Ground::Draw() {
    glEnable(GL_LIGHTING);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mAmbientMaterial);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuseMaterial);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecularMaterial);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    for (int z = 0; z < 20; ++z) {
        float zStart = 120.0f - z * 10.0f;
        for (int x = 0; x < 20; ++x) {
            float xStart = x * 10.0f - 120.0f;
            if ((z % 2) ^ (x & 2)) {
                glColor4ub(41, 41, 41, 255);
            } else {
                glColor4ub(200, 200, 200, 255);
            }
            glVertex3f(xStart, -1.0f, zStart);
            glVertex3f(xStart + 10.0f, -1.0f, zStart);
            glVertex3f(xStart + 10.0f, -1.0f, zStart - 10.0f);
            glVertex3f(xStart, -1.0f, zStart - 10.0f);
        }
    }
    glEnd();
}
