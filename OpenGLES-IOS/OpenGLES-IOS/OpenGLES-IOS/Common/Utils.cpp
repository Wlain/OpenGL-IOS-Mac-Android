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
    // 设置解包对齐，默认值是4,这边改为1，就意味着数据被紧密打包
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
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


GLuint CreateShader(GLenum shaderType, const char* src) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        return 0;
    }
    glShaderSource(shader, 1, &src, NULL);

    GLint compiled = GL_FALSE;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLogLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
        if (infoLogLen > 0) {
            GLchar* infoLog = (GLchar*)malloc(infoLogLen);
            if (infoLog) {
                glGetShaderInfoLog(shader, infoLogLen, NULL, infoLog);
                printf("Could not compile %s shader:\n%s\n",
                        shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment",
                        infoLog);
                free(infoLog);
            }
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}


GLuint CreateProgram(const char* vertSrc, const char* fragSrc) {
    GLuint vertShader = 0;
    GLuint fragShader = 0;
    GLuint program = 0;
    GLint linked = GL_FALSE;

    vertShader = CreateShader(GL_VERTEX_SHADER, vertSrc);
    if (!vertShader)
        goto exit;

    fragShader = CreateShader(GL_FRAGMENT_SHADER, fragSrc);
    if (!fragShader)
        goto exit;

    program = glCreateProgram();
    if (!program) {
        goto exit;
    }
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        printf("Could not link program");
        GLint infoLogLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
        if (infoLogLen) {
            GLchar* infoLog = (GLchar*)malloc(infoLogLen);
            if (infoLog) {
                glGetProgramInfoLog(program, infoLogLen, NULL, infoLog);
                printf("Could not link program:\n%s\n", infoLog);
                free(infoLog);
            }
        }
        glDeleteProgram(program);
        program = 0;
    }

exit:
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    return program;
}

