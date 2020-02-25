//
//  ground.hpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/23.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef ground_hpp
#define ground_hpp
#include "Utils.hpp"
#include "VertexBuffer.hpp"
#include "Shader.hpp"

class Ground {
public:
    Ground();
    ~Ground();
    void Initialize();
    void Draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
private:
    glm::mat4 mModelMatrix;
    VertexBuffer *mVertexBuffer;
    Shader *mShader;
};

#endif /* ground_hpp */
