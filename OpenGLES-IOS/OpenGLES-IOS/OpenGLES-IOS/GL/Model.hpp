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
    void Initialize(const GLchar *modelPath);
    void Draw(GLfloat x, GLfloat y, GLfloat z, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
    void SetPosition(GLfloat x, GLfloat y, GLfloat z);
    void SetAmbientMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void SetDiffuseMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void SetSpecularMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void SetTexture(const GLchar *imagePath);
    void SetModelMatrix(glm::mat4 &matrix);
    const glm::mat4& GetModelMatrix() const;
    
private:
    VertexBuffer *mVertexBuffer;
    Shader *mShader;
    glm::mat4 mModelMatrix;
};

#endif /* Model_hpp */
