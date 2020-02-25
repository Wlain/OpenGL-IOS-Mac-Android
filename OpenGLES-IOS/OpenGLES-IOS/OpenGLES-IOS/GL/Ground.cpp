//
//  ground.cpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/23.
//  Copyright © 2020 william. All rights reserved.
//

#include "Ground.hpp"
Ground::Ground() {
    
}

Ground::~Ground() {
    
}

void Ground::Initialize() {
    mVertexBuffer = new VertexBuffer();
    mShader = new Shader();
    mVertexBuffer->SetSize(1600);
    for (int z = 0; z < 20; ++z) {
        float zStart = 100.0f - z*10.0f;
        for (int x = 0; x < 20; ++x) {
            int offset = (x + z * 20) * 4;
            float xStart = x*10.0f - 100.0f;
            mVertexBuffer->SetPosition(offset, xStart, -1.0f, zStart);
            mVertexBuffer->SetPosition(offset + 1, xStart + 10.0f, -1.0f, zStart);
            mVertexBuffer->SetPosition(offset + 2, xStart, -1.0f, zStart - 10.0f);
            mVertexBuffer->SetPosition(offset + 3, xStart + 10.0f, -1.0f, zStart - 10.0f);
            mVertexBuffer->SetNormal(offset, 0.0f, 1.0f, 0.0f);
            mVertexBuffer->SetNormal(offset + 1, 0.0f, 1.0f, 0.0f);
            mVertexBuffer->SetNormal(offset + 2, 0.0f, 1.0f, 0.0f);
            mVertexBuffer->SetNormal(offset + 3, 0.0f, 1.0f, 0.0f);
            if ((z % 2) ^ (x % 2)) {
                mVertexBuffer->SetColor(offset, 0.1f, 0.1f, 0.1f);
                mVertexBuffer->SetColor(offset+1, 0.1f, 0.1f, 0.1f);
                mVertexBuffer->SetColor(offset+2, 0.1f, 0.1f, 0.1f);
                mVertexBuffer->SetColor(offset+3, 0.1f, 0.1f, 0.1f);
            } else {
                mVertexBuffer->SetColor(offset, 0.0f, 0.8f, 0.8f);
                mVertexBuffer->SetColor(offset+1, 0.0f, 0.8f, 0.8f);
                mVertexBuffer->SetColor(offset+2, 0.0f, 0.8f, 0.8f);
                mVertexBuffer->SetColor(offset+3, 0.0f, 0.8f, 0.8f);
            }
        }
    }
    mShader->Initialize("Resource/Shader/ground.vert", "Resource/Shader/ground.frag");
    mShader->Setvector4("u_lightPosition", 1.0f, 1.0f, 1.0f, 1.0f);
    mShader->Setvector4("u_lightPosition", 1.0f, 1.0f, 1.0f, 1.0f);
    mShader->Setvector4("u_ambientColor", 1.0f, 1.0f, 1.0f, 1.0f);
    mShader->Setvector4("u_diffuseColor", 1.0f, 1.0f, 1.0f, 1.0f);
    mShader->Setvector4("u_ambientMaterial", 0.1f, 0.1f, 0.1f, 1.0f);
    mShader->Setvector4("u_diffuseMaterial", 0.6f, 0.6f, 0.6f, 1.0f);
    
}
void Ground::Draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix) {
    glEnable(GL_DEPTH_TEST);
    mVertexBuffer->Bind();
    mShader->Bind(mModelMatrix, viewMatrix, projectionMatrix);
    for (int i = 0; i < 400; ++i) {
        glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
    }
    mVertexBuffer->Unbind();
}
