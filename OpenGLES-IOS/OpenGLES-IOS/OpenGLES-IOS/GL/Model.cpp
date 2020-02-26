//
//  Model.cpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/24.
//  Copyright © 2020 william. All rights reserved.
//

#include "Model.hpp"
#include "Utils.hpp"

Model::Model() {
    
}

Model::~Model() {
    
}

void Model::Initialize(const char *modelPath) {
    typedef struct _FloatData {
        float v[3];
    } FloatData;
    
    // 定义obj模型里面的一个点
    typedef struct _VertexDefine {
        int postionIndex;
        int texcoordIndex;
        int normalIndex;
    } VertexDefine;
    int fileSize = 0;
    unsigned char *fileContent = LoadFileContent(modelPath, fileSize);
    if (fileContent == nullptr) {
        std::cout << "Error to load modelPath:" << modelPath << std::endl;
        return;
    }
    std::vector<FloatData> positions, texcoords, normals;
    std::vector<VertexDefine> vertexes;
    std::stringstream ssFileContent((char *)fileContent);
    std::string temp;
    char oneLineData[256];
    // 对obj 进行解码
    while (!ssFileContent.eof()) {
        memset(oneLineData, 0, 256);
        // 一行一行读取
        ssFileContent.getline(oneLineData, 256);
        if (strlen(oneLineData) > 0) {
            if (oneLineData[0] == 'v') {
                std::stringstream ssOneLine(oneLineData);
                if (oneLineData[1] == 't') {
                    // vt 0.000000 0.000000
                    // 此时temp里面的内容是"vt"
                    ssOneLine >> temp;
                    FloatData floatData;
                    ssOneLine >> floatData.v[0];
                    ssOneLine >> floatData.v[1];
                    texcoords.push_back(floatData);
                    printf("texcoord: %f, %f\n", floatData.v[0], floatData.v[1]);
                } else if(oneLineData[1] == 'n') {
                    // vn 0.000000 0.000000 1.000000
                    ssOneLine >> temp;
                    FloatData floatData;
                    ssOneLine >> floatData.v[0];
                    ssOneLine >> floatData.v[1];
                    ssOneLine >> floatData.v[2];
                    normals.push_back(floatData);
                    printf("normal: %f, %f, %f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
                } else {
                    // v 0.500000 0.500000 0.000000
                    ssOneLine >> temp;
                    FloatData floatData;
                    ssOneLine >> floatData.v[0];
                    ssOneLine >> floatData.v[1];
                    ssOneLine >> floatData.v[2];
                    positions.push_back(floatData);
                    printf("position: %f, %f, %f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
                }
            } else if (oneLineData[0] == 'f') {
                // 位置索引/纹理坐标索引/法线索引
                // 1/1/1 2/2/2 3/3/3
                std::stringstream ssOneLine(oneLineData);
                ssOneLine >> temp;
                // temp 此时也就是'f'
                std::string vertexStr;
                for (int i = 0; i < 3; ++i) {
                    ssOneLine >> vertexStr;
                    size_t pos = vertexStr.find_first_of('/');
                    std::string posIndexStr = vertexStr.substr(0, pos);
                    size_t pos1 = vertexStr.find_first_of('/', pos + 1);
                    std::string texCoordIndexStr = vertexStr.substr(pos + 1, pos1 - 1 - pos);
                    std::string normalIndexStr = vertexStr.substr(pos1 + 1, vertexStr.length() - 1 - pos1);
                    VertexDefine vd;
                    vd.postionIndex = atoi(posIndexStr.c_str());
                    vd.texcoordIndex = atoi(texCoordIndexStr.c_str());
                    vd.normalIndex = atoi(normalIndexStr.c_str());
                    vertexes.push_back(vd);
                }
                printf("draw command: %s", oneLineData);
            }
        }
    }
    SAFE_DELETE(fileContent);
    int vertexCount = (int)(vertexes.size());
    mVertexBuffer = new VertexBuffer();
    mVertexBuffer->SetSize(vertexCount);
    for (int i = 0; i < vertexCount; ++i) {
        float *temp = nullptr;
        if (positions.size() > 0) {
            temp = &positions[vertexes[i].postionIndex - 1].v[0];
            mVertexBuffer->SetPosition(i, temp[0], temp[1], temp[2]);
        }
        if (texcoords.size() > 0) {
            temp = &texcoords[vertexes[i].texcoordIndex - 1].v[0];
            mVertexBuffer->SetTexCoord(i, temp[0], temp[1]);
        }
        if (normals.size()) {
            temp = &normals[vertexes[i].normalIndex - 1].v[0];
            mVertexBuffer->SetNormal(i, temp[0], temp[1], temp[2]);
        }
    }
    mShader = new Shader();
    mShader->Initialize("Resource/Shader/model.vert", "Resource/Shader/model.frag");
    mShader->Setvector4("u_lightPosition", 0.0f, 1.0f, 1.0f, 0.0f);// 方向光
    mShader->Setvector4("u_ambientColor", 1.0f, 1.0f, 1.0f, 1.0f);
    mShader->Setvector4("u_diffuseColor", 0.0f, 0.6f, 1.0f, 1.0f);
    mShader->Setvector4("u_specularColor", 1.0f, 1.0f, 1.0f, 1.0f);
    mShader->Setvector4("u_optionalParam", 30.0f, 0.0f, 0.0f, 0.0f);
    SetAmbientMaterial(0.1f, 0.1f, 0.1f, 1.0f);
    SetDiffuseMaterial(0.6f, 0.6f, 0.6f, 1.0f);
    SetSpecularMaterial(1.0f, 1.0f, 1.0f, 1.0f);
}


void Model::Draw( float x, float y, float z, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix) {
    mShader->Setvector4("u_cameraPosition", x, y, z, 1.0);
    glEnable(GL_DEPTH_TEST);
    mVertexBuffer->Bind();
    glm::mat4 inverseTransposeMatrix = glm::inverseTranspose(mModelMatrix);
    mShader->Bind(mModelMatrix, viewMatrix, projectionMatrix);
    glUniformMatrix4fv(glGetUniformLocation(mShader->GetProgram(), "u_inverseTransposeMatrix"), 1, GL_FALSE, glm::value_ptr(inverseTransposeMatrix));
    glDrawArrays(GL_TRIANGLES, 0, mVertexBuffer->mVertexCount);
    mVertexBuffer->Unbind();
}

void Model::SetPosition(float x, float y, float z) {
    mModelMatrix = glm::translate(x, y, z);
}


void Model::SetAmbientMaterial(float r, float g, float b, float a) {
    mShader->Setvector4("u_ambientMaterial", r, g, b, a);
}

void Model::SetDiffuseMaterial(float r, float g, float b, float a) {
     mShader->Setvector4("u_diffuseMaterial", r, g, b, a);
}

void Model::SetSpecularMaterial(float r, float g, float b, float a) {
    mShader->Setvector4("u_specularMaterial", r, g, b, a) ;
}

void Model::SetTexture(const char *imagePath) {
    mShader->SetTexture("u_texture", imagePath);
}
