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

glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;
glm::vec3 eyePosition(0.0f, 0.0f, 1200.0f);
glm::vec3 targetPosition(0.0f, 0.0f, 0.0f);
glm::vec3 upDirection(0.0f, 1.0f, 0.0f);
Ground ground;
Model model;
Skybox skybox;

void Initialize() {
    ground.Initialize();
    viewMatrix = glm::lookAt(eyePosition, targetPosition, upDirection);
    model.Initialize("Resource/UI/Model/head.obj");
    model.SetTexture("Resource/UI/2.png");
    model.SetPosition(targetPosition.x, targetPosition.y, targetPosition.z);
    skybox.Initialize("Resource/UI/Skybox/");
}

void SetViewPort(float width, float height) {
    glViewport(0, 0, width, height);
    projectionMatrix = glm::perspective(45.0f, width / height, 0.1f, 1500.0f);
}

void Draw() {
    float frameTime = GetFrameTime();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    skybox.Draw(eyePosition.x, eyePosition.y, eyePosition.z, viewMatrix, projectionMatrix);
//    ground.Draw(viewMatrix, projectionMatrix);
    model.Draw(eyePosition.x, eyePosition.y, eyePosition.z, viewMatrix, projectionMatrix);
}

void Finalize() {
    
}
