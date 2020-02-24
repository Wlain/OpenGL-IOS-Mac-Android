//
//  ground.cpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/23.
//  Copyright © 2020 william. All rights reserved.
//

#include "ground.hpp"
Ground::Ground() {
    
}

Ground::~Ground() {
    
}

void Ground::Initialize() {
    mVertexBuffer = new VertexBuffer();
    mShader = new Shader();
    mVertexBuffer->SetSize(4);
    mVertexBuffer->SetPosition(0, -1.0f, -1.0f, -5.0f);
    mVertexBuffer->SetPosition(1,  1.0f, -1.0f, -5.0f);
    mVertexBuffer->SetPosition(2, -1.0f,  1.0f, -5.0f);
    mVertexBuffer->SetPosition(3,  1.0f,  1.0f, -5.0f);
    mVertexBuffer->SetColor(0, 1.0f, 0.0f, 0.0f);
    mVertexBuffer->SetColor(1, 0.0f, 1.0f, 0.0f);
    mVertexBuffer->SetColor(2, 0.0f, 1.0f, 0.0f);
    mVertexBuffer->SetColor(3, 0.0f, 0.0f, 1.0f);
    mShader->Initialize("Resource/Shader/ground.vert", "Resource/Shader/ground.frag");
}


void Ground::Draw(glm::mat4 &viewProjectionMatrix) {
    glEnable(GL_DEPTH_TEST);
    mVertexBuffer->Bind();
    mShader->Bind(glm::value_ptr(viewProjectionMatrix));
    glDrawArrays(GL_TRIANGLE_STRIP, 0 * 4, 4);
    mVertexBuffer->Unbind();
}
