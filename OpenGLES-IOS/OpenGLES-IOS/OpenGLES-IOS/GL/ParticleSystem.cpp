//
//  ParticleSystem.cpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/26.
//  Copyright © 2020 william. All rights reserved.
//

#include "ParticleSystem.hpp"
#include "Utils.hpp"

ParticleSystem::ParticleSystem()
:mVertexBuffer(nullptr),
mShader(nullptr) {
    
}

ParticleSystem::~ParticleSystem() {
    
}

void ParticleSystem::Initialize(float x, float y, float z) {
    mModelMatrix = glm::translate(x, y + 4.0f, z);
    mVertexBuffer = new VertexBuffer();
    mShader = new Shader();
    mVertexBuffer->SetSize(1);
    mVertexBuffer->SetColor(0, 0.1f, 0.4f, 1.0f);
    mVertexBuffer->SetPosition(0, x, y, z);
    mShader->Initialize("Resource/Shader/particle.vert", "Resource/Shader/particle.frag");
    mShader->SetTexture("u_texture", CreateProceduretexture(256, 256));
}

void ParticleSystem::Draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix) {
    // 点精灵是粒子，没有深度，关闭深度测试
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    mVertexBuffer->Bind();
    mShader->Bind(mModelMatrix, viewMatrix, projectionMatrix);
    glDrawArrays(GL_POINTS, 0, mVertexBuffer->GetVertexCount());
    glDisable(GL_BLEND);
}
