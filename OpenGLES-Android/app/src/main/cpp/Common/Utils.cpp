//
// Created by william on 2020-02-26.
//

#include "Utils.h"

GLuint  CompileShader(GLenum shaderType, const char *shaderSource) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    GLint compileResult = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
    if (compileResult == GL_FALSE) {
        char errorLog[1024] = {0};
        GLsizei logLen = 0;
        glGetShaderInfoLog(shader, 1024, &logLen, errorLog);
        LOGE("Compile Shader failed error log: %s \nshader Code: %s\n", errorLog, shaderSource);
        glDeleteShader(shader);
        shader = 0;
    }
    return shader;
}


GLuint CreateProgram(GLuint vertShader, GLuint fragShader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    glDetachShader(program, vertShader);
    glDetachShader(program, fragShader);
    GLint linkResult = GL_TRUE;
    glGetShaderiv(program, GL_LINK_STATUS, &linkResult);
    if (linkResult == GL_FALSE) {
        char errorLog[1024] = {0};
        GLsizei logLen = 0;
        glGetProgramInfoLog(program, 1024, &logLen, errorLog);
        LOGE("Create gpu program falied, link error: %s\n", errorLog);
        glDeleteProgram(program);
        program = 0;
    }
    return program;
}

GLuint CreateProceduretexture(int size) {
    GLubyte *imageData = new GLubyte[size * size * 4];
    float halfSize = (float)size / 2.0f;
    float maxDistance = sqrtf(halfSize * halfSize + halfSize * halfSize);
    float centerX = halfSize;
    float centerY = halfSize;
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            int currentPixelOffset = (x + y * size) * 4;
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    glBindTexture(GL_TEXTURE_2D, 0);
    delete[] imageData;
    return texture;
}

GLuint CreateBufferObject(GLenum bufferType, GLsizei size, GLenum usage, void *data) {
    GLuint object;
    glGenBuffers(1, &object);
    glBindBuffer(bufferType, object);
    glBufferData(bufferType, size, data, usage);
    glBindBuffer(bufferType, 0);
    return object;
}