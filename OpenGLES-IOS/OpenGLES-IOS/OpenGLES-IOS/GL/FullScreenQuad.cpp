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
    mVertexBuffer->SetSize(6);
    // position
    glm::vec3 pos1(-1.0f,  1.0f, -1.0f);
    glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
    glm::vec3 pos3( 1.0f, -1.0f, 0.0f);
    glm::vec3 pos4( 1.0f,  1.0f, -1.0f);
    // texture coordinates
    glm::vec2 uv1(0.0f, 1.0f);
    glm::vec2 uv2(0.0f, 0.0f);
    glm::vec2 uv3(1.0f, 0.0f);
    glm::vec2 uv4(1.0f, 1.0f);
    // normal
    glm::vec3 mormal(0.0, 0.0, 1.0);
    glm::vec3 tangent1, bitangent1;
    glm::vec3 tangent2, bitangent2;
    glm::vec3 edge1 = pos2 - pos1;
    glm::vec3 edge2 = pos3 - pos1;
    glm::vec2 deltaUV1 = uv2 - uv1;
    glm::vec2 deltaUV2 = uv3 - uv1;
    GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
    tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent1 = glm::normalize(tangent1);
    bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent1 = glm::normalize(bitangent1);
    edge1 = pos3 - pos1;
    edge2 = pos4 - pos1;
    deltaUV1 = uv3 - uv1;
    deltaUV2 = uv4 - uv1;
    f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
    tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent2 = glm::normalize(tangent2);
    bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent2 = glm::normalize(bitangent2);
    
    mVertexBuffer->SetPosition(0, pos1.x, pos1.y, pos1.z);
    mVertexBuffer->SetTexCoord(0, uv1.s, uv1.t);
    mVertexBuffer->SetNormal(0, mormal.x, mormal.y, mormal.z);
    mVertexBuffer->SetTangent(0, tangent1.x, tangent1.y, tangent1.z);
    mVertexBuffer->SetBitTangent(0, bitangent1.x, bitangent1.y, bitangent1.z);
    mVertexBuffer->SetPosition(1, pos2.x, pos2.y, pos2.z);
    mVertexBuffer->SetTexCoord(1, uv2.s, uv2.t);
    mVertexBuffer->SetNormal(1, mormal.x, mormal.y, mormal.z);
    mVertexBuffer->SetTangent(1, tangent1.x, tangent1.y, tangent1.z);
    mVertexBuffer->SetBitTangent(1, bitangent1.x, bitangent1.y, bitangent1.z);
    mVertexBuffer->SetPosition(2, pos3.x, pos3.y, pos3.z);
    mVertexBuffer->SetTexCoord(2, uv3.s, uv3.t);
    mVertexBuffer->SetNormal(2, mormal.x, mormal.y, mormal.z);
    mVertexBuffer->SetTangent(2, tangent1.x, tangent1.y, tangent1.z);
    mVertexBuffer->SetBitTangent(2, bitangent1.x, bitangent1.y, bitangent1.z);
    
    mVertexBuffer->SetPosition(3, pos1.x, pos1.y, pos1.z);
    mVertexBuffer->SetTexCoord(3, uv1.s, uv1.t);
    mVertexBuffer->SetNormal(3, mormal.x, mormal.y, mormal.z);
    mVertexBuffer->SetTangent(3, tangent2.x, tangent2.y, tangent2.z);
    mVertexBuffer->SetBitTangent(3, bitangent2.x, bitangent2.y, bitangent2.z);
    mVertexBuffer->SetPosition(4, pos3.x, pos3.y, pos3.z);
    mVertexBuffer->SetTexCoord(4, uv3.s, uv3.t);
    mVertexBuffer->SetNormal(4, mormal.x, mormal.y, mormal.z);
    mVertexBuffer->SetTangent(4, tangent2.x, tangent2.y, tangent2.z);
    mVertexBuffer->SetBitTangent(4, bitangent2.x, bitangent2.y, bitangent2.z);
    mVertexBuffer->SetPosition(5, pos4.x, pos4.y, pos4.z);
    mVertexBuffer->SetTexCoord(5, uv4.s, uv4.t);
    mVertexBuffer->SetNormal(5, mormal.x, mormal.y, mormal.z);
    mVertexBuffer->SetTangent(5, tangent2.x, tangent2.y, tangent2.z);
    mVertexBuffer->SetBitTangent(5, bitangent2.x, bitangent2.y, bitangent2.z);
    
    mShader->Initialize("Resource/Shader/illumination/bumpMap.vert", "Resource/Shader/illumination/bumpMap.frag");
    mShader->SetTexture("u_texture", "Resource/UI/albedo.png");
    mShader->SetTexture("u_bumpTexture", "Resource/UI/normal.png");
    mShader->Setvector4("u_lightPosition", 4.0f, 4.0f, 4.0f, 1.0f);
    mShader->Setvector4("u_ambientColor", 1.0f, 1.0f, 1.0f, 1.0f);
    mShader->Setvector4("u_diffuseColor", 1.0f, 1.0f, 1.0f, 1.0f);
    mShader->Setvector4("u_specularColor", 1.0f, 1.0f, 1.0f, 1.0f);
    mShader->Setvector4("u_ambientMaterial", 0.1f, 0.1f, 0.1f, 1.0f);
    mShader->Setvector4("u_diffuseMaterial", 0.6f, 0.6f, 0.6f, 1.0f);
    mShader->Setvector4("u_specularMaterial", 1.0f, 1.0f, 1.0f, 1.0f);
    mModelMatrix = glm::translate(0.0f, 0.0f, -5.0f);
}
void FullScreenQuad::Draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix) {
    glEnable(GL_DEPTH_TEST);
    mVertexBuffer->Bind();
    glUniform1f(glGetUniformLocation(mShader->GetProgram(), "u_shininess"), 64.0f);
    mShader->Bind(mModelMatrix, viewMatrix, projectionMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    mVertexBuffer->Unbind();
}
