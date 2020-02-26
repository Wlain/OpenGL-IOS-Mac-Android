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
    void Draw(float x, float y, float z, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
    void SetPosition(float x, float y, float z);
    void SetAmbientMaterial(float r, float g, float b, float a);
    void SetDiffuseMaterial(float r, float g, float b, float a);
    void SetSpecularMaterial(float r, float g, float b, float a);
    void SetTexture(const char *imagePath);
    void SetModelMatrix(glm::mat4 &matrix);
    const glm::mat4& GetModelMatrix() const;
    
private:
    VertexBuffer *mVertexBuffer;
    Shader *mShader;
    glm::mat4 mModelMatrix;
};

#endif /* Model_hpp */
