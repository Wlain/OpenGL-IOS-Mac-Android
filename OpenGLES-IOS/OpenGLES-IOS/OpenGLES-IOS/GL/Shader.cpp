//
//  Shader.cpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/23.
//  Copyright © 2020 william. All rights reserved.
//

#include "Shader.hpp"
#include "Utils.hpp"
#include "VertexBuffer.hpp"

Shader::Shader()
:mProgram(0),
mColorLocation(-1),
mNormalLocation(-1),
mTexCoordLocation(-1),
mPositionLocation(-1),
mWorldViewProjectionMatrixLocation(-1){
    
}

Shader::~Shader() {
    
}


GLuint Shader::GetProgram() const {
    return this->mProgram;
}

void Shader::SetProgram(GLuint program) {
    this->mProgram = program;
}

GLint Shader::GetPositionLocation() const {
    return this->mPositionLocation;
}

void Shader::SetPositionLocation(GLint location) {
    this->mPositionLocation = location;
}

GLint Shader::GetTexCoordLocation() const {
    return this->mTexCoordLocation;
}

void Shader::SetTexCoordLocation(GLint location) {
    this->mTexCoordLocation = location;
}

GLint Shader::GetColorLocation() const {
    return this->mColorLocation;
}

void Shader::SetColorLocation(GLint location) {
    this->mColorLocation = location;
}

GLint Shader::GetNormalLocation() const {
    return this->mNormalLocation;
}

void Shader::SetNormalLocation(GLint location) {
    this->mNormalLocation = location;
}

GLint Shader::GetWorldViewProjectionMatrixLocation() const {
    return this->mWorldViewProjectionMatrixLocation;
}

void Shader::SetWorldViewProjectionMatrixLocation(GLint location) {
    this->mWorldViewProjectionMatrixLocation = location;
}

GLuint Shader::CompileShader(GLenum shaderType, const char*shaderCode) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    GLint compileResult = GL_TRUE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
    if (compileResult == GL_FALSE) {
        char errorlog[1024] = { 0 };
        GLsizei logLen = 0;
        glGetShaderInfoLog(shader, 1024, &logLen, errorlog);
        printf("Compile Shader fail error log : %s \nshader code :\n%s\n", errorlog, shaderCode);
        glDeleteShader(shader);
        shader = 0;
    }
    return shader;
}

void Shader::Initialize(const char *vertShaderPath, const char *fragShaderPath) {
    int fileSize = 0;
    const char *vertShaderSource = (char *)LoadFileContent(vertShaderPath, fileSize);
    GLuint vertShader = CompileShader(GL_VERTEX_SHADER, vertShaderSource);
    if (vertShader == 0) {
        SAFE_DELETE_ARRAY(vertShaderSource);
        return;
    }
    const char *fragShaderSource = (char *)LoadFileContent(fragShaderPath, fileSize);
    GLuint fragShader = CompileShader(GL_FRAGMENT_SHADER, fragShaderSource);
    if (fragShader == 0) {
        SAFE_DELETE_ARRAY(vertShaderSource);
        SAFE_DELETE_ARRAY(fragShaderSource);
        return;
    }
    SAFE_DELETE_ARRAY(vertShaderSource);
    SAFE_DELETE_ARRAY(fragShaderSource);
    mProgram = CreateProgram(vertShader, fragShader);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    if (mProgram != 0) {
        mPositionLocation = glGetAttribLocation(mProgram, "a_position");
        mTexCoordLocation = glGetAttribLocation(mProgram, "a_texCoord");
        mNormalLocation = glGetAttribLocation(mProgram, "a_normal");
        mColorLocation = glGetAttribLocation(mProgram, "a_color");
        mWorldViewProjectionMatrixLocation = glGetUniformLocation(mProgram, "u_worldViewProjectionMatrix");
    }
}

void Shader::Bind(float *mvpMatrix) {
    glUseProgram(mProgram);
    glUniformMatrix4fv(mWorldViewProjectionMatrixLocation, 1, GL_FALSE, mvpMatrix);
    glEnableVertexAttribArray(mPositionLocation);
    glVertexAttribPointer(mPositionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(mTexCoordLocation);
    glVertexAttribPointer(mTexCoordLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0 + 4 * sizeof(float)));
    glEnableVertexAttribArray(mNormalLocation);
    glVertexAttribPointer(mNormalLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0 + 8 * sizeof(float)));
    glEnableVertexAttribArray(mColorLocation);
    glVertexAttribPointer(mColorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0 + 12 * sizeof(float) ));
}

