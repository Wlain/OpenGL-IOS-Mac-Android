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
#include "ParticleSystem3.hpp"

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
ParticleSystem3 particle3;

GLboolean ESSCENE_API esCreateWindow(ESContext *esContext, const char *title, GLint width, GLuint height) {
    esContext->width = width;
    esContext->height = height;
    return GL_FALSE;
}

void ESSCENE_API esResigerInitFunc(ESContext *esContext, void(ESCALLBACK *initFunc)(ESContext *)) {
    esContext->initFunc = initFunc;
}

void ESSCENE_API esResigerResizeFunc(ESContext *esContext, void(ESCALLBACK *resizeFunc)(ESContext *)) {
    esContext->resizeFunc = resizeFunc;
}

void ESSCENE_API esResigerDrawFunc(ESContext *esContext, void(ESCALLBACK *drawFunc)(ESContext *)) {
    esContext->drawFunc = drawFunc;;
}

void ESSCENE_API esResigerUpdateFunc(ESContext *esContext, void(ESCALLBACK *updateFunc)(ESContext *, float deltaTime)) {
    esContext->updateFunc = updateFunc;
}

void ESSCENE_API esResigerKeyFunc(ESContext *esContext, void(ESCALLBACK *keyFunc)(ESContext *,unsigned char, int, int)) {
    esContext->keyFunc = keyFunc;
}

void ESSCENE_API esRegisterShutdownFunc( ESContext *esContext, void(ESCALLBACK *finalizeFunc)(ESContext *)) {
    esContext->finalizeFunc = Finalize;
}

void ESSCENE_API esLogMessage(const char *formatStr, ...) {
    va_list params;
    char buf[1024];
    va_start(params, formatStr);
    vsprintf(buf, formatStr, params);
    printf("%s", buf);
    va_end(params);
}

void Initialize(ESContext *esContext) {
    PrintGLString("Version", GL_VERSION);
    PrintGLString("Vendor", GL_VENDOR);
    PrintGLString("Renderer", GL_RENDERER);
    PrintGLString("Extensions", GL_EXTENSIONS);
    GLint maxVertexAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
    printf("GL_MAX_VERTEX_ATTRIBS:%d", maxVertexAttribs);
    esResigerDrawFunc(esContext, Draw );
    esResigerUpdateFunc(esContext, Update );
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
//    triangle.Initialize(esContext);
//    mrt.Initialize(esContext);
    particle3.Initialize(esContext);
}

void Resize(ESContext *esContext, GLint width, GLint height) {
    glViewport(0, 0, width, height);
    projectionMatrix = glm::perspective(45.0f, (GLfloat)width / height, 0.1f, 1500.0f);
//    mrt.Resize(esContext, width, height);
    particle3.Resize(esContext, width, height);
}

void Draw(ESContext *esContext) {
    GLfloat frameTime = GetFrameTime();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    skybox.Draw(eyePosition.x, eyePosition.y, eyePosition.z, viewMatrix, projectionMatrix);
//    ground.Draw(viewMatrix, projectionMatrix);
//    model.Draw(eyePosition.x, eyePosition.y, eyePosition.z, viewMatrix, projectionMatrix);
//    cattle.Draw(eyePosition.x, eyePosition.y, eyePosition.z, viewMatrix, projectionMatrix);
//    head.Draw(eyePosition.x, eyePosition.y, eyePosition.z, viewMatrix, projectionMatrix);
//    particle.Update(frameTime);
//    particle.Draw(viewMatrix, projectionMatrix);
//    triangle.Draw(esContext);
//    mrt.Draw(esContext);
    particle3.Draw(esContext);
}

void Key(ESContext *esContext) {
    
}

void Update(ESContext *esContext, float deltaTime) {
    particle3.Update(esContext, deltaTime);
}

void Finalize(ESContext *esContext) {
//    triangle.Finalize(esContext);
//    mrt.Finalize(esContext);
    particle3.Finalize(esContext);
}


