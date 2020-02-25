//
//  Model.hpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/24.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include "Base.h"
#include "Shader.hpp"
#include "VertexBuffer.hpp"


class Model {
public:
    Model();
    ~Model();
    void Initialize(const char *modelPath);
    void Draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
    void SetPosition(float x, float y, float z);
    
private:
    VertexBuffer *mVertexBuffer;
    Shader *mShader;
    glm::mat4 mModelMatrix;
};

#endif /* Model_hpp */
