//
//  Utils.cpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/22.
//  Copyright © 2020 william. All rights reserved.
//

#include "Utils.hpp"
#include "Base.h"

GLuint CreateProgram(GLuint vertShader, GLuint fragShader) {
    GLuint program = 0;
    GLint linked = GL_FALSE;
    program = glCreateProgram();
    if (!program) {
        goto exit;
    }
    // 绑定
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    // 解绑定
    glDetachShader(program, vertShader);
    glDetachShader(program, fragShader);
   
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE){
        printf("could not link program\n");
        GLint infoLogLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
        if (infoLogLen) {
            GLchar *infoLog = (GLchar *)malloc(infoLogLen);
            if (infoLog) {
                glGetProgramInfoLog(program, infoLogLen, nullptr, infoLog);
                printf("could not link program\n%s\n", infoLog);
                free(infoLog);
            }
        }
        glDeleteProgram(program);
        program = 0;
    }
    return program;
exit:
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    return program;
}


GLuint CreateProceduretexture(GLsizei width, GLsizei height) {
    GLubyte *imageData = new GLubyte[width * height * 4];
    GLfloat halfSize = (GLfloat)width / 2.0f;
    GLfloat maxDistance = sqrtf(halfSize * halfSize + halfSize * halfSize);
    GLfloat centerX = halfSize;
    GLfloat centerY = halfSize;
    for (GLint y = 0; y < height; ++y) {
        for (GLint x = 0; x < width; ++x) {
            GLint currentPixelOffset = (x + y * height) * 4;
            imageData[currentPixelOffset] = 255;
            imageData[currentPixelOffset + 1] = 255;
            imageData[currentPixelOffset + 2] = 255;
            GLfloat deltaX = (GLfloat)x - centerX;
            GLfloat deltaY = (GLfloat)y - centerY;
            GLfloat distance = sqrtf(deltaX * deltaX + deltaY * deltaY);
            GLfloat alpha = powf(1.0f - (distance / maxDistance), 10.0f);
            alpha = alpha > 1.0f ? 1.0f : alpha;
            imageData[currentPixelOffset + 3] = (GLubyte)(alpha * 255.0f);
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
    SAFE_DELETE_ARRAY(imageData)
    return texture;
}


GLuint CreateBufferObject(GLenum bufferType, GLsizeiptr size, GLenum usage, void *data) {
    GLuint object;
    glGenBuffers(1, &object);
    glBindBuffer(bufferType, object);
    glBufferData(bufferType, size, data, usage);
    glBindBuffer(bufferType, 0);
    return object;
}


bool CheckGlError(const GLchar* funcName) {
    GLint err = glGetError();
    if (err != GL_NO_ERROR) {
        printf("GL error after %s(): 0x%08x in filename = %s, line = %i\n", funcName, err, __FILE__, __LINE__);
        return true;
    }
    return false;
}


