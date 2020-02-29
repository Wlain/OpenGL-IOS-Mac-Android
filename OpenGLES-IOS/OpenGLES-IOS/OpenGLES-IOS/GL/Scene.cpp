//
//  Scene.cpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/22.
//  Copyright © 2020 william. All rights reserved.
//

#include "Scene.hpp"
#include "Base.h"
#include "Utils.hpp"
#include "Ground.hpp"
#include "Shader.hpp"
#include "Model.hpp"
#include "Skybox.hpp"
#include "ParticleSystem.hpp"
#include "TrianglesES3.hpp"
#include "MrtES3.hpp"

glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;
glm::vec3 eyePosition(0.0f, 10.0f, 40.0f);
glm::vec3 targetPosition(0.0f, 0.0f, 0.0f);
glm::vec3 upDirection(0.0f, 1.0f, 0.0f);
Ground ground;
Model model;
Model cattle;
Model head;
Skybox skybox;
ParticleSystem particle;
TrianglesES3 triangle;
MrtES3 mrt;

void Initialize() {
    PrintGLString("Version", GL_VERSION);
    PrintGLString("Vendor", GL_VENDOR);
    PrintGLString("Renderer", GL_RENDERER);
    PrintGLString("Extensions", GL_EXTENSIONS);
    GLint maxVertexAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
    printf("GL_MAX_VERTEX_ATTRIBS:%d", maxVertexAttribs);
//    ground.Initialize();
//    viewMatrix = glm::lookAt(eyePosition, targetPosition, upDirection);
//    model.Initialize("Resource/UI/Model/Sphere.obj");
//    model.SetTexture("Resource/UI/earth.png");
//    cattle.Initialize("Resource/UI/Model/ox.obj");
//    cattle.SetTexture("Resource/UI/ox.jpg");
//    head.Initialize("Resource/UI/Model/head.obj");
//    head.SetTexture("Resource/UI/2.png");
//    model.SetPosition(targetPosition.x, targetPosition.y, targetPosition.z);
//    glm::mat4 oxModelMatrix = glm::translate(-5.0f, 0.0f, 4.0f) * glm::scale(0.05f, 0.05f, 0.05f);
//    glm::mat4 headModelMatrix = glm::translate(5.0f, 0.0f, 4.0f) * glm::scale(0.01f, -0.01f, -0.01f);
//    cattle.SetModelMatrix(oxModelMatrix);
//    head.SetModelMatrix(headModelMatrix);
//    skybox.Initialize("Resource/UI/Skybox2/");
//    particle.Initialize(targetPosition.x, targetPosition.y, targetPosition.z);
//    triangle.Initialize();
    mrt.Initialize();
}

void SetViewPort(GLfloat width, GLfloat height) {
    glViewport(0, 0, width, height);
    projectionMatrix = glm::perspective(45.0f, width / height, 0.1f, 1500.0f);
    mrt.Resize(width, height);
}

void Draw() {
    GLfloat frameTime = GetFrameTime();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    skybox.Draw(eyePosition.x, eyePosition.y, eyePosition.z, viewMatrix, projectionMatrix);
//    ground.Draw(viewMatrix, projectionMatrix);
//    model.Draw(eyePosition.x, eyePosition.y, eyePosition.z, viewMatrix, projectionMatrix);
//    cattle.Draw(eyePosition.x, eyePosition.y, eyePosition.z, viewMatrix, projectionMatrix);
//    head.Draw(eyePosition.x, eyePosition.y, eyePosition.z, viewMatrix, projectionMatrix);
//    particle.Update(frameTime);
//    particle.Draw(viewMatrix, projectionMatrix);
//    triangle.Draw();
    mrt.Draw();
}

void Finalize() {
    
}
