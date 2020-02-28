//
//  VertexBuffer.cpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/23.
//  Copyright © 2020 william. All rights reserved.
//

#include "VertexBuffer.hpp"
#include "Utils.hpp"

VertexBuffer::VertexBuffer()
:mVertexCount(0),
mVertexes(nullptr) {
    
}
VertexBuffer::~VertexBuffer() {
    
}

int VertexBuffer::GetVertexCount() const {
    return this->mVertexCount;
}

void VertexBuffer::SetVertexCount(const GLint count) {
    this->mVertexCount = count;
}

Vertex* VertexBuffer::GetVertexesPointer() const {
    return mVertexes;
}

void VertexBuffer::SetVertexes(const Vertex& vertexes) {
    *this->mVertexes = vertexes;
}

void VertexBuffer::SetSize(GLint size) {
    mVertexCount = size;
    mVertexes = new Vertex[mVertexCount];
    memset(mVertexes, 0, sizeof(Vertex) * mVertexCount);
    mVbo = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(Vertex) * mVertexCount, GL_STATIC_DRAW, nullptr);
}

void VertexBuffer::SetPosition(GLint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    mVertexes[index].position[0] = x;
    mVertexes[index].position[1] = y;
    mVertexes[index].position[2] = z;
    mVertexes[index].position[3] = w;
}

void VertexBuffer::SetTexCoord(GLint index, GLfloat x, GLfloat y) {
    mVertexes[index].texcoord[0] = x;
    mVertexes[index].texcoord[1] = y;
}


void VertexBuffer::SetNormal(GLint index, GLfloat x, GLfloat y, GLfloat z) {
    mVertexes[index].normal[0] = x;
    mVertexes[index].normal[1] = y;
    mVertexes[index].normal[2] = z;
}

void VertexBuffer::SetColor(GLint index, GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    mVertexes[index].color[0] = r;
    mVertexes[index].color[1] = g;
    mVertexes[index].color[2] = b;
    mVertexes[index].color[3] = a;
}

void VertexBuffer::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * mVertexCount, mVertexes);
}

void VertexBuffer::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

