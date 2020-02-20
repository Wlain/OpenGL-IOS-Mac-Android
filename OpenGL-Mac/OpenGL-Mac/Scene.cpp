//
//  Scene.cpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/19.
//  Copyright © 2020 william. All rights reserved.
//
//                 y  ^
//                    |
//                    |
//                    |
//                    |
//    ------------------------------------------->
//                    | (0,0,0)                  x
//                    |
//                    |
//                    |
// z轴指向屏幕外面

#include "Scene.hpp"
#include "Util.hpp"

GLuint textureID;

void Initialize() {
    glMatrixMode(GL_PROJECTION);
    gluPerspective(50.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLsizei width, height;
    textureID = TextureFromFile("test.jpeg", width, height);
//    glViewport(0, 0, width, height);
}

void DrawTriangle() {
    glPushMatrix();
        glBegin(GL_TRIANGLES);
        // 向量叉乘法则
        // 默认情况下，逆时针是OpenGL的正面
        glColor4ub(255, 0, 0, 255);
        glVertex3f(-0.2f, -0.2f, -1.0f);
        glColor4ub(0, 255, 0, 255);
        glVertex3f(0.2f, -0.2f, -1.0f);
        glColor4ub(0, 0, 255, 255);
        glVertex3f(0.0f, 0.2f, -1.0f);
        glEnd();
    glPopMatrix();
}

void DrawLight() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // 无穷远的点光源(x/w, y/w, z/w)
    float lightPos[4] = {0.0f, 0.0f, 1.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    float whiteColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    // 环境光系数
    float ambientCoe[4] = {0.07f, 0.07f, 0.07f, 1.0f};
    // 漫反射光系数
    // {0.0f, 0.0f, 0.4f, 1.0f};
    float diffuseCoe[4] = {0.4f, 0.4f, 0.4f, 1.0f};
    // 镜面反色光系数
    float specularCoe[4] = {0.9f, 0.9f, 0.9f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, whiteColor);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientCoe);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ambientCoe);

    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ambientCoe);
}

void DrawQuad() {
    glLoadIdentity();
    glTranslated(0.0, 0.0, -3.0);
    glPushMatrix();
    glBegin(GL_TRIANGLE_STRIP);
    // 向量叉乘法则
    // 默认情况下，逆时针是OpenGL的正面
    glColor4ub(255, 255, 255, 255);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0f, -1.0f, -0.0f);
    glTexCoord2f(1.0, 1.0);
    glVertex3f( 1.0f, -1.0f, -0.0f);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0f,  1.0f, -0.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f( 1.0f,  1.0f, -0.0f);
    glEnd();
    glPopMatrix();
}

void Draw() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    DrawQuad();
}
