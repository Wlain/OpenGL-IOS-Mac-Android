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

void Model::Initialize(const GLchar *modelPath) {
    typedef struct _GLfloatData {
        GLfloat v[3];
    } GLfloatData;
    // 定义obj模型里面的一个点
    typedef struct _VertexDefine {
        int postionIndex;
        int texcoordIndex;
        int normalIndex;
    } VertexDefine;
    int fileSize = 0;
    const GLchar *fileContent = LoadFileContent(modelPath, fileSize);
    if (fileContent == nullptr) {
        std::cout << "Error to load modelPath:" << modelPath << std::endl;
        return;
    }
    std::vector<GLfloatData> positions, texcoords, normals;
    std::vector<VertexDefine> vertexes;
    std::stringstream ssFileContent((GLchar *)fileContent);
    std::string temp;
    GLchar oneLineData[256];
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
                    GLfloatData GLfloatData;
                    ssOneLine >> GLfloatData.v[0];
                    ssOneLine >> GLfloatData.v[1];
                    texcoords.push_back(GLfloatData);
                } else if(oneLineData[1] == 'n') {
                    // vn 0.000000 0.000000 1.000000
                    ssOneLine >> temp;
                    GLfloatData GLfloatData;
                    ssOneLine >> GLfloatData.v[0];
                    ssOneLine >> GLfloatData.v[1];
                    ssOneLine >> GLfloatData.v[2];
                    normals.push_back(GLfloatData);
                } else {
                    // v 0.500000 0.500000 0.000000
                    ssOneLine >> temp;
                    GLfloatData GLfloatData;
                    ssOneLine >> GLfloatData.v[0];
                    ssOneLine >> GLfloatData.v[1];
                    ssOneLine >> GLfloatData.v[2];
                    positions.push_back(GLfloatData);
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
            }
        }
    }
    SAFE_DELETE(fileContent);
    int vertexCount = (int)(vertexes.size());
    mVertexBuffer = new VertexBuffer();
    mVertexBuffer->SetSize(vertexCount);
    for (int i = 0; i < vertexCount; ++i) {
        GLfloat *temp = nullptr;
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
    mShader->Initialize("Resource/Shader/illumination/gouraud_point.vert", "Resource/Shader/illumination/gouraud_point.frag");
    mShader->Setvector4("u_ambientColor", 1.0f, 1.0f, 1.0f, 1.0f);
    mShader->Setvector4("u_diffuseColor", 1.0f, 1.0f, 1.0f, 1.0f);
    mShader->Setvector4("u_specularColor", 1.0f, 1.0f, 1.0f, 1.0f);
    mShader->Setvector4("u_lightPosition", 1.0f, 1.0f, 0.0f, 0.0f);
    SetSpecularMaterial( 1.0f, 1.0f, 1.0f, 1.0f);
    SetAmbientMaterial(0.1f, 0.1f, 0.1f, 1.0f);
    SetDiffuseMaterial(0.8f, 0.8f, 0.8f, 1.0f);
}


void Model::Draw( GLfloat x, GLfloat y, GLfloat z, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix) {
    mShader->Setvector4("u_cameraPosition", x, y, z, 1.0);
    mNormalMatrix = glm::inverseTranspose(mModelMatrix);
    glEnable(GL_DEPTH_TEST);
    mVertexBuffer->Bind();
    mShader->Bind(mModelMatrix, viewMatrix, projectionMatrix);
    glUniformMatrix4fv(glGetUniformLocation(mShader->GetProgram(), "u_normalMatrix"), 1, GL_FALSE, glm::value_ptr(mNormalMatrix));
    glUniform1f(glGetUniformLocation(mShader->GetProgram(), "u_shininess"), 32.0f);
    glDrawArrays(GL_TRIANGLES, 0, mVertexBuffer->mVertexCount);
    mVertexBuffer->Unbind();
}

void Model::SetPosition(GLfloat x, GLfloat y, GLfloat z) {
    mModelMatrix = glm::translate(x, y, z);
}


void Model::SetAmbientMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    mShader->Setvector4("u_ambientMaterial", r, g, b, a);
}

void Model::SetDiffuseMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
     mShader->Setvector4("u_diffuseMaterial", r, g, b, a);
}

void Model::SetSpecularMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    mShader->Setvector4("u_specularMaterial", r, g, b, a) ;
}

void Model::SetTexture(const GLchar *imagePath) {
    mShader->SetTexture("u_texture", imagePath);
}

void Model::SetModelMatrix(glm::mat4 &matrix) {
    mModelMatrix = matrix;
}

const glm::mat4& Model::GetModelMatrix() const {
    return this->mModelMatrix;
}
