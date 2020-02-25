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

glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;
Ground ground;
Model model;


void Initialize() {
    ground.Initialize();
    model.Initialize("Resource/UI/Model/Sphere.obj");
    model.SetTexture("Resource/UI/earth.png");
    model.SetPosition(0.0f, 0.0f, -10.0f);
}

void SetViewPort(float width, float height) {
    glViewport(0, 0, width, height);
    projectionMatrix = glm::perspective(45.0f, width / height, 0.1f, 100.0f);
}

void Draw() {
    float frameTime = GetFrameTime();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ground.Draw(viewMatrix, projectionMatrix);
    model.Draw(viewMatrix, projectionMatrix);
}

void Finalize() {
    
}
