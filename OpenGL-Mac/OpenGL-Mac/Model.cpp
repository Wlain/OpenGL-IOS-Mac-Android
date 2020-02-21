//
//  Model.cpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/20.
//  Copyright © 2020 william. All rights reserved.
//

#include "Model.hpp"
#include "Util.hpp"

Model::Model() {
    memset(mAmbientMaterial, 0, sizeof(mAmbientMaterial));
    memset(mDiffuseMaterial, 0, sizeof(mDiffuseMaterial));
    memset(mSpecularMaterial, 0, sizeof(mSpecularMaterial));
}

Model::~Model() {
    
}

void Model::SetTextureID(GLuint texture) {
    this->mTextureID = texture;
}

int Model::GetTextureID(GLuint texture) const {
    return this->mIndexCount;
}

void Model::SetAmbientMaterial(float r, float g, float b, float a) {
    this->mAmbientMaterial[0] = r;
    this->mAmbientMaterial[1] = g;
    this->mAmbientMaterial[2] = b;
    this->mAmbientMaterial[3] = a;
}

void Model::SetDiffuseMaterial(float r, float g, float b, float a) {
    this->mDiffuseMaterial[0] = r;
    this->mDiffuseMaterial[1] = g;
    this->mDiffuseMaterial[2] = b;
    this->mDiffuseMaterial[3] = a;
}

void Model::SetSpecularMaterial(float r, float g, float b, float a) {
    this->mSpecularMaterial[0] = r;
    this->mSpecularMaterial[1] = g;
    this->mSpecularMaterial[2] = b;
    this->mSpecularMaterial[3] = a;
}

void Model::Initialize(const char *modelPath) {
    struct FloatData {
        float v[3];
    };
    // 定义obj模型里面的一个点
    struct VertexDefine {
        int postionIndex;
        int texcoordIndex;
        int normalIndex;
    };
    int nFileSize = 0;
    GLubyte *fileContent = LoadFileContent(modelPath, nFileSize);
    if (fileContent == nullptr) {
        std::cout << "Error to load modelPath:" << modelPath << std::endl;
        return;
    }
    std::vector<FloatData> positions, texCoords, normals;
    std::vector<VertexDefine> vertexes;
    std::vector<int> indexes;
    // 等价于
    // std::stringstream ssFileContent;
    // ssFileContent.str((char *)fileContent);
    std::stringstream ssFileContent((char *)fileContent);
    std::string temp;
    char oneLineData[256];
    // 对obj文件进行解码
    while (!ssFileContent.eof()) {
        memset(oneLineData, 0, 256);
        // 一行一行读文件
        ssFileContent.getline(oneLineData, 256);
        if(strlen(oneLineData) > 0) {
            if (oneLineData[0] == 'v') {
                std::stringstream ssOneLine(oneLineData);
                if (oneLineData[1] == 't') {
                    // vt 0.000000 0.000000
                    // 此时temp里面的内容是"vt"
                    ssOneLine >> temp;
                    FloatData floatData;
                    ssOneLine >> floatData.v[0];
                    ssOneLine >> floatData.v[1];
                    texCoords.push_back(floatData);
                    printf("texcoord: %f, %f\n", floatData.v[0], floatData.v[1]);
                } else if (oneLineData[1] == 'n') {
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
                // 1/1/1 2/2/2 3/3/3
                std::stringstream ssOneLine(oneLineData);
                ssOneLine >> temp;
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
                    int nCurrentVertexIndex = -1;
                    int CurrentVertexCount = (int)vertexes.size();
                    // 检查是否有重复的点
                    for (int j = 0; j < CurrentVertexCount; ++j) {
                        if (vertexes[j].postionIndex == vd.postionIndex &&
                            vertexes[j].texcoordIndex == vd.texcoordIndex &&
                            vertexes[j].normalIndex == vd.normalIndex ) {
                            nCurrentVertexIndex = j;
                            break;
                        }
                    }
                    // 此时没有重复，需要新建一个点
                    if (nCurrentVertexIndex == -1) {
                        nCurrentVertexIndex = (int)vertexes.size();
                        vertexes.push_back(vd);
                    }
                    indexes.push_back(nCurrentVertexIndex);
                }
                printf("draw command:%s\n", oneLineData);
            }
        }
    }
    mIndexCount = (int)indexes.size();
    mIndexes = new unsigned short[mIndexCount];
    for (int i = 0; i < mIndexCount; ++i) {
        mIndexes[i] = indexes[i];
    }
    // 获取有多少个唯一的点
    unsigned int vertexCount = (int)vertexes.size();
    mVertexes = new VertexData[vertexCount];
    memset(mVertexes, 0, sizeof(VertexData) * vertexCount);
    for (int i = 0; i < positions.size(); ++i) {
        memcpy(mVertexes[i].position, positions[vertexes[i].postionIndex - 1].v, sizeof(float) * 3);
    }
    for (int i = 0; i < texCoords.size(); ++i) {
         memcpy(mVertexes[i].texCoord, texCoords[vertexes[i].texcoordIndex - 1].v, sizeof(float) * 2);
    }
    for (int i = 0; i < normals.size(); ++i) {
        memcpy(mVertexes[i].normal, normals[vertexes[i].normalIndex - 1].v, sizeof(float) * 3);
    }
    delete fileContent;
}

void Model::Draw() {
    glEnable(GL_LIGHTING);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mAmbientMaterial);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuseMaterial);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecularMaterial);
    // 设置镜面反射指数，默认值是0.0
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glEnable(GL_DEPTH_TEST);
    glPushMatrix();
    glTranslated(0.0f, 0.0f, -5.0f);
    glBegin(GL_TRIANGLES);
    glColor4ub(255, 255, 255, 255);
    for (int i = 0; i < mIndexCount; ++i) {
        glTexCoord2fv(mVertexes[mIndexes[i]].texCoord);
        glNormal3fv(mVertexes[mIndexes[i]].normal);
        glVertex3fv(mVertexes[mIndexes[i]].position);
    }
    glEnd();
    glPopMatrix();
}


