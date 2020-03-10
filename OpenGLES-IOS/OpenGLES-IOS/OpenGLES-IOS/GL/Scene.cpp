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
#include "ParticleEmitter.hpp"
#include "FullScreenQuad.hpp"

glm::mat4 viewMatrix;
glm::mat4 quadViewMatrix;
glm::mat4 quadOrthoMatrix;
glm::mat4 projectionMatrix;
glm::vec3 eyePosition(0.0f, 0.0f, 1.0f);
glm::vec3 targetPosition(0.0f, 0.0f, 0.0f);
glm::vec3 upDirection(0.0f, 1.0f, 0.0f);
Model head;
FullScreenQuad fullScreenQuad;

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
    fullScreenQuad.Initialize();
    viewMatrix = glm::lookAt(eyePosition, targetPosition, upDirection);
    head.Initialize("Resource/UI/Model/Sphere.obj");
    head.SetTexture("Resource/UI/earth.png");
    glm::mat4 modelMatrix = glm::translate(0.0f, 0.0f, -5.0f);
    head.SetModelMatrix(modelMatrix);
}

void Resize(ESContext *esContext, GLint width, GLint height) {
    glViewport(0, 0, width, height);
    projectionMatrix = glm::perspective(45.0f, (GLfloat)width / height, 1.0f, 1000.0f);
    quadOrthoMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 1000.0f);
}

void Draw(ESContext *esContext) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    fullScreenQuad.Draw(quadViewMatrix, quadOrthoMatrix);
    head.Draw(eyePosition.x, eyePosition.y, eyePosition.z, viewMatrix, projectionMatrix);
}

void Key(ESContext *esContext) {
    
}

void Update(ESContext *esContext, float deltaTime) {

}

void Finalize(ESContext *esContext) {

}


