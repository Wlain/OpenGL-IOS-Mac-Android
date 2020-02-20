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
private:
    VertexData *mVertexes;
    unsigned short *mIndexes;
    int mIndexCount;
};

#endif /* Model_hpp */
