//
//  ParticleSystem.hpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/26.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp

#include "Shader.hpp"
#include "VertexBuffer.hpp"

class ParticleSystem {
public:
    ParticleSystem();
    ~ParticleSystem();
    void Initialize(float x, float y, float z);
    void Draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
private:
    VertexBuffer *mVertexBuffer;
    Shader *mShader;
    glm::mat4 mModelMatrix;
};

#endif /* ParticleSystem_hpp */
