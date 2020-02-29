//
//  TrianglesES3.cpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/29.
//  Copyright © 2020 william. All rights reserved.
//

#include "TrianglesES3.hpp"
#include "Utils.hpp"

#define POSITION_ATTRIB 0
#define COLOR_ATTRIB 1

TrianglesES3::TrianglesES3()
:RendererES3(0, 0)
{
    
}

TrianglesES3::~TrianglesES3() {
    
}

void TrianglesES3::Initialize() {
    const GLfloat vertexes[] = {
        0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
       -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    };
    int fileSize = 0;
    const char* vertPath = LoadFileContent("Resource/Shader/renderes3.vert", fileSize);
    const char* fragPath = LoadFileContent("Resource/Shader/renderes3.frag", fileSize);
    mProgram = CreateProgram(vertPath, fragPath);
    mVbo = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(vertexes), GL_STATIC_DRAW, (void *)vertexes);
}

void TrianglesES3::Draw() {
    glUseProgram (mProgram);
    // Load the vertex data
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glVertexAttribPointer(POSITION_ATTRIB, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(0));
    glEnableVertexAttribArray(POSITION_ATTRIB);
    glVertexAttribPointer(COLOR_ATTRIB, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(0 + 4 * sizeof(float)));
    glEnableVertexAttribArray (COLOR_ATTRIB);
    glDrawArrays (GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
