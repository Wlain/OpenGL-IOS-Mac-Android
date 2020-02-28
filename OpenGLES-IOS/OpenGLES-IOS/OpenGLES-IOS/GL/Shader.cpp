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

GLuint Shader::CompileShader(GLenum shaderType, const GLchar *src) {
    GLuint shader = glCreateShader(shaderType);
    if (!shader) {
        CheckGlError("glCreateShader");
        return 0;
    }
    glShaderSource(shader, 1, &src, nullptr);
    GLint compiled = GL_TRUE;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        GLsizei infoLogLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
        if (infoLogLen > 0) {
            GLchar *infoLog = (GLchar *)malloc(infoLogLen);
            if (infoLog) {
                glGetShaderInfoLog(shader, infoLogLen, nullptr, infoLog);
                printf("Cound not compile %s shader:\n%s\n",
                        shaderType == GL_VERTEX_SHADER ? "vertex " : "fragment", infoLog);
                free(infoLog);
            }
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

void Shader::SetTexture(const GLchar *name, GLuint texture) {
    auto iter = mUniformTextures.find(name);
       if (iter == mUniformTextures.end()) {
           GLint location = glGetUniformLocation(mProgram, name);
           if (location != -1) {
               UniformTexture *uniformTexture = new UniformTexture();
               uniformTexture->mLocation = location;
               uniformTexture->mTexture = texture;
               mUniformTextures.insert(std::pair<std::string, UniformTexture *>(name, uniformTexture));
           }
       } else {
           glDeleteTextures(1, &iter->second->mTexture);
           iter->second->mTexture = texture;
   }
}

void Shader::SetTexture(const GLchar *name, const GLchar *imagePath) {
    GLuint texture = GetTextureFromFile(imagePath, true);
    this->SetTexture(name, texture);
}

void Shader::Setvector4(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
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

void Shader::Initialize(const GLchar *vertShaderPath, const GLchar *fragShaderPath) {
    int fileSize = 0;
    const GLchar *vertShaderSource = (GLchar *)LoadFileContent(vertShaderPath, fileSize);
    GLuint vertShader = CompileShader(GL_VERTEX_SHADER, vertShaderSource);
    if (vertShader == 0) {
        SAFE_DELETE_ARRAY(vertShaderSource);
        return;
    }
    const GLchar *fragShaderSource = (GLchar *)LoadFileContent(fragShaderPath, fileSize);
    GLuint fragShader = CompileShader(GL_FRAGMENT_SHADER, fragShaderSource);
    if (fragShader == 0) {
        SAFE_DELETE_ARRAY(vertShaderSource);
        SAFE_DELETE_ARRAY(fragShaderSource);
        return;
    }
    SAFE_DELETE_ARRAY(vertShaderSource);
    SAFE_DELETE_ARRAY(fragShaderSource);
    glGetError();
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
    glVertexAttribPointer(mTexCoordLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0 + 4 * sizeof(GLfloat)));
    glEnableVertexAttribArray(mNormalLocation);
    glVertexAttribPointer(mNormalLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0 + 8 * sizeof(GLfloat)));
    glEnableVertexAttribArray(mColorLocation);
    glVertexAttribPointer(mColorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(0 + 12 * sizeof(GLfloat) ));
}

