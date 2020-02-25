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
mModelMatrixLocation(-1),
mViewMatrixLocation(-1),
mProjectionMatrixLocation(-1){
    
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


GLint Shader::GetModelMatrixLocation() const {
    return this->mModelMatrixLocation;
}

void Shader::SetModelMatrixLocation(GLint location) {
     this->mModelMatrixLocation = location;
}

GLint Shader::GetViewMatrixLocation() const {
     return this->mViewMatrixLocation;
}

void Shader::SetViewMatrixLocation(GLint location) {
    this->mViewMatrixLocation = location;
}

GLint Shader::GetProjectionMatrixLocation() const {
     return this->mProjectionMatrixLocation;
}

void Shader::SetProjectionMatrixLocation(GLint location) {
    this->mProjectionMatrixLocation = location;
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

void Shader::SetTexture(const char *name, const char *imagePath) {
    auto iter = mUniformTextures.find(name);
    if (iter == mUniformTextures.end()) {
        GLint location = glGetUniformLocation(mProgram, name);
        if (location != -1) {
            UniformTexture *texture = new UniformTexture();
            texture->mLocation = location;
            texture->mTexture = GetTextureFromFile(imagePath, true);
            mUniformTextures.insert(std::pair<std::string, UniformTexture *>(name, texture));
        }
    } else {
        glDeleteTextures(1, &iter->second->mTexture);
        iter->second->mTexture = GetTextureFromFile(imagePath, true);
    }
}

void Shader::Setvector4(const char *name, float x, float y, float z, float w) {
    auto iter = mUniformVector4s.find(name);
    if (iter == mUniformVector4s.end()) {
        GLint location = glGetUniformLocation(mProgram, name);
        if (location != -1) {
            UniformVector4 *vector4 = new UniformVector4();
            vector4->mLocation = location;
            vector4->v[0] = x;
            vector4->v[1] = y;
            vector4->v[2] = z;
            vector4->v[3] = w;
            mUniformVector4s.insert(std::pair<std::string, UniformVector4 *>(name, vector4));
        }
    } else {
        iter->second->v[0] = x;
        iter->second->v[1] = y;
        iter->second->v[2] = z;
        iter->second->v[3] = w;
    }
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
        mModelMatrixLocation = glGetUniformLocation(mProgram, "u_modelMatrix");
        mViewMatrixLocation = glGetUniformLocation(mProgram, "u_viewMatrix");
        mProjectionMatrixLocation = glGetUniformLocation(mProgram, "u_projectionMatrix");
    }
}

void Shader::Bind(glm::mat4 &modelMatrix, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix) {
    glUseProgram(mProgram);
    int index = 0;
    for (auto iter = mUniformTextures.begin(); iter != mUniformTextures.end(); ++iter) {
        glActiveTexture(GL_TEXTURE0 + index);
        glBindTexture(GL_TEXTURE_2D, iter->second->mTexture);
        glUniform1i(iter->second->mLocation, index++);
    }
    for (auto iter = mUniformVector4s.begin(); iter != mUniformVector4s.end(); ++iter) {
        glUniform4fv(iter->second->mLocation, 1, iter->second->v);
    }
    glUniformMatrix4fv(mModelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(mViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(mProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glEnableVertexAttribArray(mPositionLocation);
    glVertexAttribPointer(mPositionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(mTexCoordLocation);
    glVertexAttribPointer(mTexCoordLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0 + 4 * sizeof(float)));
    glEnableVertexAttribArray(mNormalLocation);
    glVertexAttribPointer(mNormalLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0 + 8 * sizeof(float)));
    glEnableVertexAttribArray(mColorLocation);
    glVertexAttribPointer(mColorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0 + 12 * sizeof(float) ));
}

