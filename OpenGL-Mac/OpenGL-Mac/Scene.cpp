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
#include "SkyBox.hpp"
#include "Model.hpp"
#include "Ground.hpp"
#include "Light.hpp"
#include "Camera.hpp"

SkyBox skyBox;
Model model;
Ground ground;
DirectionLight directionLight(GL_LIGHT0);
PointLight pointLight(GL_LIGHT1);
PointLight pointLight2(GL_LIGHT2);
SportLight sportLight(GL_LIGHT3);
Camera camera;

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
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseCoe);

    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularCoe);
}

void DrawQuad() {
    glLoadIdentity();
    glPushMatrix();
    glTranslated(0.0, 0.0, -3.0);
    glBegin(GL_TRIANGLE_STRIP);
    // 向量叉乘法则
    // 默认情况下，逆时针是OpenGL的正面
    glColor4ub(255, 255, 0, 255);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f,  1.0f, 0.0f);
    glVertex3f( 1.0f,  1.0f, 0.0f);
    glEnd();
    glPopMatrix();
}

void OnKeyDown(char code) {
    switch (code) {
        case 'A':
            camera.mIsMoveLeft = true;
            break;
        case 'D':
            camera.mIsMoveRight = true;
            break;
        case 'W':
            camera.mIsMoveForward = true;
            break;
        case 'S':
            camera.mIDMoveBack = true;
            break;
        default:
            break;
    }
}

void OnKeyUp(char code) {
    switch (code) {
        case 'A':
            camera.mIsMoveLeft = false;
            break;
        case 'D':
            camera.mIsMoveRight = false;
            break;
        case 'W':
            camera.mIsMoveForward = false;
            break;
        case 'S':
            camera.mIDMoveBack = false;
            break;
        default:
            break;
    }
}

void OnMouseMove(float deltaX, float deltaY) {
    
}


void Initialize() {
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    skyBox.Initialize("UI/Skybox/");
    directionLight.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
    directionLight.SetDiffuseColor(0.8f, 0.8f, 0.8f, 1.0f);
    directionLight.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
    directionLight.SetPosition(0.0f, 1.0f, 0.0f);
    pointLight.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
    pointLight.SetDiffuseColor(0.8f, 0.8f, 0.8f, 1.0f);
    pointLight.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
    pointLight.SetPosition(0.0f, 0.0f, 0.0f);
    pointLight.setConstantAttenuationCoe(1.0f);
    pointLight.setLinearAttenuationCoe(0.2f);
    pointLight2.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
    pointLight2.SetDiffuseColor(0.1f, 0.2f, 0.8f, 1.0f);
    pointLight2.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
    pointLight2.SetPosition(0.0f, 0.0f, -10.0f);
    pointLight2.setConstantAttenuationCoe(1.0f);
    pointLight2.setLinearAttenuationCoe(0.2f);
    sportLight.SetAmbientColor(0.1f, 0.1f, 0.1f, 1.0f);
    sportLight.SetDiffuseColor(0.1f, 0.8f, 0.0f, 1.0f);
    sportLight.SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
    sportLight.SetPosition(0.0f, 20.0f, -10.0f);
    sportLight.SetDirection(0.0f, -1.0f, 0.0f);
    sportLight.SetExponent(5.0f);
    sportLight.SetCutoff(10.0f);
    model.Initialize("UI/Model/Sphere.obj");
    GLuint texture = TextureFromFile("UI/earth.png");
    model.SetTextureID(texture);
    model.SetAmbientMaterial(0.1f, 0.1f, 0.1f, 1.0f);
    model.SetDiffuseMaterial(0.4f, 0.4f, 0.4f, 1.0f);
    model.SetSpecularMaterial(1.0f, 1.0f, 1.0f, 1.0f);
    ground.SetAmbientMaterial(0.1f, 0.1f, 0.1f, 1.0f);
    ground.SetDiffuseMaterial(0.4f, 0.4f, 0.4f, 1.0f);
    ground.SetSpecularMaterial(1.0f, 1.0f, 1.0f, 1.0f);
}


void Draw() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float frameTime = GetFrameTime();
    camera.Update(frameTime);
    directionLight.Enable();
    skyBox.Draw(camera.mEyePosition.x, camera.mEyePosition.y, camera.mEyePosition.z);
    model.Draw();
    pointLight.Enable();
    pointLight2.Enable();
    sportLight.Enable();
    ground.Draw();
}
