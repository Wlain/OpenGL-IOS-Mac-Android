//
//  Skybox.hpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/26.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef Skybox_hpp
#define Skybox_hpp

#include "VertexBuffer.hpp"
#include "Shader.hpp"
#include "Base.h"

class Skybox {
public:
    Skybox();
    ~Skybox();
    void Initialize(const GLchar *imageDir);
    void InitFront(const GLchar *image);
    void InitBack(const GLchar *image);
    void InitLeft(const GLchar *image);
    void InitRight(const GLchar *image);
    void InitTop(const GLchar *image);
    void InitBottom(const GLchar *image);
    void Draw(GLfloat x, GLfloat y, GLfloat z, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
private:
    VertexBuffer *mVertexBuffer;
    glm::mat4 mModelMatrix;
    Shader *mShader;
};


#endif /* Skybox_hpp */
