//
//  FullScreenQuad.cpp
//  OpenGLES-IOS
//
//  Created by william on 2020/3/10.
//  Copyright © 2020 william. All rights reserved.
//

#include "FullScreenQuad.hpp"


FullScreenQuad::FullScreenQuad() {
    
}

FullScreenQuad::~FullScreenQuad() {
    
}

void FullScreenQuad::Initialize() {
    mVertexBuffer = new VertexBuffer();
    mShader = new Shader();
    mVertexBuffer->SetSize(4);
    mVertexBuffer->SetPosition(0, -1.0f, -1.0f, -1000.0f);
    mVertexBuffer->SetTexCoord(0, 0.0f, 0.0f);
    mVertexBuffer->SetPosition(1, 1.0f, -1.0f, -1000.0f);
    mVertexBuffer->SetTexCoord(1, 1.0f, 0.0f);
    mVertexBuffer->SetPosition(2, -1.0f, 1.0f, -1000.0f);
    mVertexBuffer->SetTexCoord(2, 0.0f, 1.0f);
    mVertexBuffer->SetPosition(3, 1.0f, 1.0f, -1000.0f);
    mVertexBuffer->SetTexCoord(3, 1.0f, 1.0f);
    mShader->Initialize("Resource/Shader/textured.vert", "Resource/Shader/textured.frag");
    mShader->SetTexture("u_texture", "Resource/UI/Skybox2/bottom.jpg");
    mShader->Setvector4("u_lightPosition", 1.0f, 1.0f, 1.0f, 1.0f);
    mShader->Setvector4("u_lightPosition", 1.0f, 1.0f, 1.0f, 1.0f);
    mShader->Setvector4("u_ambientColor", 1.0f, 1.0f, 1.0f, 1.0f);
    mShader->Setvector4("u_diffuseColor", 1.0f, 1.0f, 1.0f, 1.0f);
    mShader->Setvector4("u_ambientMaterial", 0.1f, 0.1f, 0.1f, 1.0f);
    mShader->Setvector4("u_diffuseMaterial", 0.6f, 0.6f, 0.6f, 1.0f);
}
void FullScreenQuad::Draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix) {
    glEnable(GL_DEPTH_TEST);
    mVertexBuffer->Bind();
    mShader->Bind(mModelMatrix, viewMatrix, projectionMatrix);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    mVertexBuffer->Unbind();
}
