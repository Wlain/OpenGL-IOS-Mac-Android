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
Model strawberry;
FullScreenQuad fullScreenQuad;
float translateZ = -723.145386f;

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
    head.Initialize("Resource/UI/Model/head.obj");
    head.SetTexture("Resource/UI/test.png");
    strawberry.Initialize("Resource/UI/Model/strawberry.obj");
    strawberry.SetTexture("Resource/UI/strawberry.png");
    GLint width = 750;
    GLint height = 1334;
    GLfloat facePosX = 184.762573f;
    GLfloat facePosY = 385.965118f;
    GLfloat faceWidth = 382.812714f;
    GLfloat faceHeight = 400.8205567f;
    glm::vec2 midFace(facePosX + faceWidth / 2, facePosY + faceHeight / 2);
    glm::mat4 matrix;
    matrix = matrix * glm::translate(0.47f * width - midFace.x, 0.63f * height - midFace.y, 1.0f) *
    glm::translate(midFace.x, midFace.y, 1.0f) * glm::scale(0.35f, 0.35f, 1.0f) *
    glm::translate(-midFace.x, -midFace.y, 1.0f);
    glm::mat4 headModelMatrix = glm::translate(11.841172f, -29.00336f, -503.501892f) * glm::scale(1.0f, -1.0f, -1.0f);
    glm::mat4 headModelMatrix2 = glm::translate(50.841172f, -100.00336f, -503.501892f) * glm::scale(1.0f, -1.0f, -1.0f);
    head.SetModelMatrix(headModelMatrix2);
    strawberry.SetModelMatrix(headModelMatrix);
    glm::vec4 alpha(1.0f, 0.0f, 0.0f, 0.0f);
    strawberry.SetAlpha(alpha);
}

void Resize(ESContext *esContext, GLint width, GLint height) {
    glViewport(0, 0, width, height);
    projectionMatrix = glm::perspective(53.1301f, (GLfloat)width / height, 1.0f, abs(translateZ) + 1500.0f);
    quadOrthoMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 1000.0f);
}

void Draw(ESContext *esContext) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    fullScreenQuad.Draw(quadViewMatrix, quadOrthoMatrix);
    head.Draw(eyePosition.x, eyePosition.y, eyePosition.z, viewMatrix, projectionMatrix);
    strawberry.Draw(eyePosition.x, eyePosition.y, eyePosition.z, viewMatrix, projectionMatrix);
}

void Key(ESContext *esContext) {
    
}

void Update(ESContext *esContext, float deltaTime) {

}

void Finalize(ESContext *esContext) {

}


