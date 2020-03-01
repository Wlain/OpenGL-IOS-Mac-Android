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

typedef struct
{
    // Handle to a program object
    GLuint programObject;
    GLuint posVbo;
    GLuint colorVbo;
    GLuint vao;
} UserData;

TrianglesES3::TrianglesES3()
{
    
}

TrianglesES3::~TrianglesES3() {
    
}

void TrianglesES3::Initialize(ESContext *esContext) {
    esContext->userData = malloc(sizeof(UserData));
    UserData *userData = (UserData *)esContext->userData;
    const GLfloat vertexes[] = {
        0.0f,  0.5f, 0.0f, 1.0f,
       -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f,
    };
    GLfloat color[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
    };
    int fileSize = 0;
    const char* vertPath = LoadFileContent("Resource/Shader/renderes3.vert", fileSize);
    const char* fragPath = LoadFileContent("Resource/Shader/renderes3.frag", fileSize);
    userData->programObject = CreateProgram(vertPath, fragPath);
    GLfloat *vboMappedBuf;
    userData->posVbo = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(vertexes), GL_STATIC_DRAW, (void *)vertexes);
    glBindBuffer(GL_ARRAY_BUFFER, userData->posVbo);
    vboMappedBuf = (GLfloat *)glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(vertexes), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
    if (vboMappedBuf == nullptr) {
       printf("Error mapping positionVertex buffer object.");
    }
    memcpy(vboMappedBuf, vertexes, sizeof(vertexes));
    // Unmap the buffer
    if(glUnmapBuffer(GL_ARRAY_BUFFER) == GL_FALSE) {
       printf("Error unmapping array buffer object.");
    }
    // Copy the data into the mapped buffer
    GLfloat *colorVboMappedBuf;
    userData->colorVbo = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(color), GL_STATIC_DRAW, (void *)color);
    glBindBuffer(GL_ARRAY_BUFFER, userData->colorVbo);
    colorVboMappedBuf = (GLfloat *)glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(color), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
    if (colorVboMappedBuf == nullptr) {
       printf("Error mapping colorVertex buffer object.");
    }
    memcpy(colorVboMappedBuf, color, sizeof(color));
    // Unmap the buffer
    if(glUnmapBuffer(GL_ARRAY_BUFFER) == GL_FALSE) {
       printf("Error unmapping array buffer object.");
    }
    // Generate VAO Id
    glGenVertexArrays(1, &userData->vao);
    // Bind the VAO and then setup the vertex
    // attributes
    glBindVertexArray(userData->vao);
    glBindBuffer(GL_ARRAY_BUFFER, userData->posVbo);
    glVertexAttribPointer(POSITION_ATTRIB, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void *)(0));
    glEnableVertexAttribArray(POSITION_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, userData->colorVbo);
    glVertexAttribPointer(COLOR_ATTRIB, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void *)(0));
    glEnableVertexAttribArray(COLOR_ATTRIB);
    glBindVertexArray(0);
}

void TrianglesES3::Draw(ESContext *esContext) {
    UserData *userData = (UserData *)esContext->userData;
    glUseProgram(userData->programObject);
    glBindVertexArray(userData->vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void TrianglesES3::Update(ESContext *esContext, float deltaTime) {
    
}

void TrianglesES3::Resize(ESContext *esContext,int width, int height) {
    
}

void TrianglesES3::Finalize(ESContext *esContext) {
    UserData *userData = (UserData *)esContext->userData;
    glDeleteBuffers(1, &userData->posVbo);
    glDeleteBuffers(1, &userData->colorVbo);
    glDeleteVertexArrays(1, &userData->vao);
    glDeleteProgram(userData->programObject);
    SAFE_FREE(esContext->userData);
}
