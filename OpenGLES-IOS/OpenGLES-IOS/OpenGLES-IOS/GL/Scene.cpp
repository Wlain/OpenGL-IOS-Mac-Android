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

GLuint texture;
GLint textureLocation;
glm::mat4 modelViewMatrix;
glm::mat4 projectionMatrix;
glm::mat4 worldViewProjectionMatrix;
Ground ground;
Shader *shader;
VertexBuffer *vertexBuffer;

void Initialize() {
    vertexBuffer = new VertexBuffer();
    shader = new Shader();
    vertexBuffer->SetSize(4);
    vertexBuffer->SetPosition(0, -0.5f, -0.5f, -4.0f);
    vertexBuffer->SetTexCoord(0, 0.0f, 0.0f);
    vertexBuffer->SetPosition(1, 0.5f, -0.5f, -4.0f);
    vertexBuffer->SetTexCoord(1, 1.0f, 0.0f);
    vertexBuffer->SetPosition(2, -0.5f,  0.5f, -4.0f);
    vertexBuffer->SetTexCoord(2, 0.0f, 1.0f);
    vertexBuffer->SetPosition(3, 0.5f,  0.5f, -4.0f);
    vertexBuffer->SetTexCoord(3, 1.0f, 1.0f);
    modelViewMatrix = glm::translate(0.0f, 0.0f, -0.6f);
    shader->Initialize("Resource/Shader/textured.vert", "Resource/Shader/textured.frag");
    shader->SetTexture("u_texture", "Resource/UI/logo.png");
    shader->SetTexture("u_diffuseTexture", "Resource/UI/Skybox/back.jpg");
    shader->SetTexture("u_mask", "Resource/UI/mask.png");
    ground.Initialize();
}

void SetViewPort(float width, float height) {
    glViewport(0, 0, width, height);
    projectionMatrix = glm::perspective(45.0f, width / height, 0.1f, 100.0f);
    worldViewProjectionMatrix = modelViewMatrix * projectionMatrix;
}

void Draw() {
    float frameTime = GetFrameTime();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ground.Draw(worldViewProjectionMatrix);
    vertexBuffer->Bind();
    shader->Bind(worldViewProjectionMatrix);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    vertexBuffer->Unbind();
    glUseProgram(0);
}

void Finalize() {
    SAFE_DELETE(vertexBuffer);
    SAFE_DELETE(shader);
}
