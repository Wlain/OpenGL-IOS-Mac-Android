//
//  Utils.cpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/22.
//  Copyright © 2020 william. All rights reserved.
//

#include "Utils.hpp"
#include "Base.h"



GLuint CompileShader(GLenum shaderType, const char *shaderPath){
    assert(shaderPath);
    GLuint shader = glCreateShader(shaderType);
    if (shader == 0){
        printf("glCreateShader fail\n");
        return 0;
    }
    int nFileSize = 0;
    const GLchar* shaderCode = (GLchar*)LoadFileContent(shaderPath, nFileSize);
    if (shaderCode == nullptr){
        printf("load shader code from file : %s fail\n", shaderPath);
        glDeleteShader(shader);
        return 0;
    }
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    GLint compileResult = GL_TRUE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
    if (compileResult == GL_FALSE){
        GLchar errorlog[1024] = { 0 };
        GLsizei logLen = 0;
        glGetShaderInfoLog(shader, 1024, &logLen, errorlog);
        printf("Compile Shader fail error log : %s \nshader code :\n%s\n", errorlog, shaderCode);
        glDeleteShader(shader);
        shader = 0;
    }
    delete shaderCode;
    return shader;
}

GLuint CreateProgram(GLuint vertShader, GLuint fragShader) {
    GLuint program = glCreateProgram();
    // 绑定
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    // 解绑定
    glDetachShader(program, vertShader);
    glDetachShader(program, fragShader);
    GLint nResult;
    glGetProgramiv(program, GL_LINK_STATUS, &nResult);
    if (nResult == GL_FALSE){
        GLchar errorlog[1024] = {0};
        GLsizei logLen = 0;
        glGetProgramInfoLog(program, 1024, &logLen, errorlog);
        printf("create gpu program fail,link error : %s\n", errorlog);
        glDeleteProgram(program);
        program = 0;
    }
    return program;
}


GLuint CreateProceduretexture(GLsizei width, GLsizei height) {
    GLubyte *imageData = new GLubyte[width * height * 4];
    float halfSize = (float)width / 2.0f;
    float maxDistance = sqrtf(halfSize * halfSize + halfSize * halfSize);
    float centerX = halfSize;
    float centerY = halfSize;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int currentPixelOffset = (x + y * width) * 4;
            imageData[currentPixelOffset] = 255;
            imageData[currentPixelOffset + 1] = 255;
            imageData[currentPixelOffset + 2] = 255;
            float deltaX = (float)x - centerX;
            float deltaY = (float)y - centerY;
            float distance = sqrtf(deltaX * deltaX + deltaY * deltaY);
            float alpha = powf(1.0f - (distance / maxDistance), 10.0f);
            alpha = alpha > 1.0f ? 1.0f : alpha;
            imageData[currentPixelOffset + 3] = (unsigned char)(alpha * 255.0f);
        }
    }
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    glBindTexture(GL_TEXTURE_2D, 0);
    delete[] imageData;
    return texture;
}
