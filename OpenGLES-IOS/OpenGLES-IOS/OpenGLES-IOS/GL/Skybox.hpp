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
    void Initialize(const char *imageDir);
    void InitFront(const char *image);
    void InitBack(const char *image);
    void InitLeft(const char *image);
    void InitRight(const char *image);
    void InitTop(const char *image);
    void InitBottom(const char *image);
    void Draw(float x, float y, float z, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
private:
    VertexBuffer *mVertexBuffer;
    glm::mat4 mModelMatrix;
    Shader *mShader;
};


#endif /* Skybox_hpp */
