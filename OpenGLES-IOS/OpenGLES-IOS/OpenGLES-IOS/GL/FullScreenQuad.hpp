//
//  FullScreenQuad.hpp
//  OpenGLES-IOS
//
//  Created by william on 2020/3/10.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef FullScreenQuad_hpp
#define FullScreenQuad_hpp

#include "Utils.hpp"
#include "VertexBuffer.hpp"
#include "Shader.hpp"

class FullScreenQuad {
public:
    FullScreenQuad();
    ~FullScreenQuad();
    void Initialize();
    void Draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
private:
    glm::mat4 mModelMatrix;
    VertexBuffer *mVertexBuffer;
    Shader *mShader;
};


#endif /* FullScreenQuad_hpp */
