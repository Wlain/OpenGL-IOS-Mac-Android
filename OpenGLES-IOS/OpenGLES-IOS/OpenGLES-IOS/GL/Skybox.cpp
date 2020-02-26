//
//  Skybox.cpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/26.
//  Copyright © 2020 william. All rights reserved.
//

#include "Skybox.hpp"

Skybox::Skybox()
:mVertexBuffer(nullptr){
    
}

Skybox::~Skybox() {
    
}

void Skybox::Initialize(const char *imageDir) {
    mShader = new Shader[6];
    mVertexBuffer = new VertexBuffer[6];
    const unsigned int fileDirSize = 256;
    char tmpDir[fileDirSize];
    memset(tmpDir, 0, fileDirSize);
    strcpy(tmpDir, imageDir);
    strcat(tmpDir, "front.jpg");
    InitFront(tmpDir);
    memset(tmpDir, 0, fileDirSize);
    strcpy(tmpDir, imageDir);
    strcat(tmpDir, "back.jpg");
    InitBack(tmpDir);
    memset(tmpDir, 0, fileDirSize);
    strcpy(tmpDir, imageDir);
    strcat(tmpDir, "left.jpg");
    InitLeft(tmpDir);
    memset(tmpDir, 0, fileDirSize);
    strcpy(tmpDir, imageDir);
    strcat(tmpDir, "right.jpg");
    InitRight(tmpDir);
    memset(tmpDir, 0, fileDirSize);
    strcpy(tmpDir, imageDir);
    strcat(tmpDir, "top.jpg");
    InitTop(tmpDir);
    memset(tmpDir, 0, fileDirSize);
    strcpy(tmpDir, imageDir);
    strcat(tmpDir, "bottom.jpg");
    InitBottom(tmpDir);
}

void Skybox::InitFront(const char *image) {
    mVertexBuffer[0].SetSize(4);
    mShader[0].Initialize("Resource/Shader/skybox.vert", "Resource/Shader/skybox.frag");
    mShader[0].SetTexture("u_texture", image);
    mVertexBuffer[0].SetPosition(0, -1.0f, -1.0f, -1.0f);
    mVertexBuffer[0].SetTexCoord(0, 0.0f, 0.0f);
    mVertexBuffer[0].SetPosition(1, 1.0f, -1.0f, -1.0f);
    mVertexBuffer[0].SetTexCoord(1, 1.0f, 0.0f);
    mVertexBuffer[0].SetPosition(2, -1.0f, 1.0f, -1.0f);
    mVertexBuffer[0].SetTexCoord(2, 0.0f, 1.0f);
    mVertexBuffer[0].SetPosition(3, 1.0f, 1.0f, -1.0f);
    mVertexBuffer[0].SetTexCoord(3, 1.0f, 1.0f);
}

void Skybox::InitBack(const char *image) {
    mVertexBuffer[1].SetSize(4);
    mShader[1].Initialize("Resource/Shader/skybox.vert", "Resource/Shader/skybox.frag");
    mShader[1].SetTexture("u_texture", image);
    mVertexBuffer[1].SetPosition(1, 1.0f, -1.0f, 1.0f);
    mVertexBuffer[1].SetTexCoord(0, 0.0f, 0.0f);
    mVertexBuffer[1].SetPosition(0, -1.0f, -1.0f, 1.0f);
    mVertexBuffer[1].SetTexCoord(1, 1.0f, 0.0f);
    mVertexBuffer[1].SetPosition(3, 1.0f, 1.0f, 1.0f);
    mVertexBuffer[1].SetTexCoord(2, 0.0f, 1.0f);
    mVertexBuffer[1].SetPosition(2, -1.0f, 1.0f, 1.0f);
    mVertexBuffer[1].SetTexCoord(3, 1.0f, 1.0f);
}

void Skybox::InitLeft(const char *image) {
    mVertexBuffer[2].SetSize(4);
    mShader[2].Initialize("Resource/Shader/skybox.vert", "Resource/Shader/skybox.frag");
    mShader[2].SetTexture("u_texture", image);
    mVertexBuffer[2].SetPosition(0, -1.0f, -1.0f, 1.0f);
    mVertexBuffer[2].SetTexCoord(0, 0.0f, 0.0f);
    mVertexBuffer[2].SetPosition(1, -1.0f, -1.0f, -1.0f);
    mVertexBuffer[2].SetTexCoord(1, 1.0f, 0.0f);
    mVertexBuffer[2].SetPosition(2, -1.0f, 1.0f, 1.0f);
    mVertexBuffer[2].SetTexCoord(2, 0.0f, 1.0f);
    mVertexBuffer[2].SetPosition(3, -1.0f, 1.0f, -1.0f);
    mVertexBuffer[2].SetTexCoord(3, 1.0f, 1.0f);
}

void Skybox::InitRight(const char *image) {
    mVertexBuffer[3].SetSize(4);
    mShader[3].Initialize("Resource/Shader/skybox.vert", "Resource/Shader/skybox.frag");
    mShader[3].SetTexture("u_texture", image);
    mVertexBuffer[3].SetPosition(0, 1.0f, -1.0f, -1.0f);
    mVertexBuffer[3].SetTexCoord(0, 0.0f, 0.0f);
    mVertexBuffer[3].SetPosition(1, 1.0f, -1.0f, 1.0f);
    mVertexBuffer[3].SetTexCoord(1, 1.0f, 0.0f);
    mVertexBuffer[3].SetPosition(2, -1.0f, 1.0f, -1.0f);
    mVertexBuffer[3].SetTexCoord(2, 0.0f, 1.0f);
    mVertexBuffer[3].SetPosition(3, 1.0f, 1.0f, 1.0f);
    mVertexBuffer[3].SetTexCoord(3, 1.0f, 1.0f);
}

void Skybox::InitTop(const char *image) {
    mVertexBuffer[4].SetSize(4);
    mShader[4].SetTexture("u_texture", image);
    mShader[4].Initialize("Resource/Shader/skybox.vert", "Resource/Shader/skybox.frag");
    mVertexBuffer[4].SetPosition(0, -1.0f, 1.0f, -1.0f);
    mVertexBuffer[4].SetTexCoord(0, 0.0f, 0.0f);
    mVertexBuffer[4].SetPosition(1, 1.0f, 1.0f, -1.0f);
    mVertexBuffer[4].SetTexCoord(1, 1.0f, 0.0f);
    mVertexBuffer[4].SetPosition(2, -1.0f, 1.0f, 1.0f);
    mVertexBuffer[4].SetTexCoord(2, 0.0f, 1.0f);
    mVertexBuffer[4].SetPosition(3, 1.0f, 1.0f, 1.0f);
    mVertexBuffer[4].SetTexCoord(3, 1.0f, 1.0f);
}

void Skybox::InitBottom(const char *image) {
    mVertexBuffer[5].SetSize(4);
    mShader[5].Initialize("Resource/Shader/skybox.vert", "Resource/Shader/skybox.frag");
    mShader[5].SetTexture("u_texture", image);
    mVertexBuffer[5].SetPosition(0, -1.0f, -1.0f, 1.0f);
    mVertexBuffer[5].SetTexCoord(0, 0.0f, 0.0f);
    mVertexBuffer[5].SetPosition(1, 1.0f, -1.0f, 1.0f);
    mVertexBuffer[5].SetTexCoord(1, 1.0f, 0.0f);
    mVertexBuffer[5].SetPosition(2, -1.0f, -1.0f, -1.0f);
    mVertexBuffer[5].SetTexCoord(2, 0.0f, 1.0f);
    mVertexBuffer[5].SetPosition(3, 1.0f, -1.0f, -1.0f);
    mVertexBuffer[5].SetTexCoord(3, 1.0f, 1.0f);
}

void Skybox::Draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix) {
    glDisable(GL_DEPTH_TEST);
    for (int i = 0; i < 6; ++i) {
        mVertexBuffer[i].Bind();
        mShader[i].Bind(mModelMatrix, viewMatrix, projectionMatrix);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        mVertexBuffer[i].Unbind();
    }
}

