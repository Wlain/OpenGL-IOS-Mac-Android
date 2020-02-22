//
//  Model.hpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/20.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp
#include "Base.h"

struct VertexData {
    float position[3]; // 顶点
    float texCoord[2]; // 纹理
    float normal[3];   // 法线
};

class Model {
public:
    Model();
    virtual ~Model();
    void Initialize(const char * modelPath);
    void Draw();
    void SetTextureID(GLuint texture);
    int GetTextureID(GLuint texture) const;
    void SetAmbientMaterial(float r, float g, float b, float a);
    void SetDiffuseMaterial(float r, float g, float b, float a);
    void SetSpecularMaterial(float r, float g, float b, float a);
private:
    VertexData *mVertexes;
    unsigned short *mIndexes;
    int mIndexCount;
    GLuint mTexture;
    float mAmbientMaterial[4];
    float mDiffuseMaterial[4];
    float mSpecularMaterial[4];
};


#endif /* Model_hpp */
