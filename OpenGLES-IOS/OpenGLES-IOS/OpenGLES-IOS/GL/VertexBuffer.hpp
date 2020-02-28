//
//  VertexBuffer.hpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/23.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef VertexBuffer_hpp
#define VertexBuffer_hpp

#include "Base.h"

typedef struct _Vertex {
    GLfloat position[4];
    GLfloat texcoord[4];
    GLfloat normal[4];
    GLfloat color[4];
} Vertex;

class VertexBuffer {
public:
    VertexBuffer();
    ~VertexBuffer();
    GLint GetVertexCount() const;
    void SetVertexCount(const GLint count);
    Vertex* GetVertexesPointer() const;
    void SetVertexes(const Vertex& vertexes);
    void SetSize(GLint size);
    void SetPosition(GLint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f);
    void SetColor(GLint index, GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);
    void SetTexCoord(GLint index, GLfloat x, GLfloat y);
    void SetNormal(GLint index, GLfloat x, GLfloat y, GLfloat z);
    void Bind();
    void Unbind();
public:
    GLuint mVbo;
    GLint mVertexCount;
    Vertex *mVertexes;
};

#endif /* VertexBuffer_hpp */
