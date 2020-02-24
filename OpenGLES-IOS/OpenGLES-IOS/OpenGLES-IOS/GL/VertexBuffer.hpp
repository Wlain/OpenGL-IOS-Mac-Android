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
    float position[4];
    float texcoord[4];
    float normal[4];
    float color[4];
} Vertex;

class VertexBuffer {
public:
    VertexBuffer();
    ~VertexBuffer();
    int GetVertexCount() const;
    void SetVertexCount(const int count);
    Vertex* GetVertexesPointer() const;
    void SetVertexes(const Vertex& vertexes);
    void SetSize(int size);
    void SetPosition(int index, float x, float y, float z, float w = 1.0f);
    void SetColor(int index, float r, float g, float b, float a = 1.0f);
    void SetTexCoord(int index, float x, float y);
    void SetNormal(int index, float x, float y, float z);
    void Bind();
    void Unbind();
public:
    GLuint mVbo;
    int mVertexCount;
    Vertex *mVertexes;
};

#endif /* VertexBuffer_hpp */
