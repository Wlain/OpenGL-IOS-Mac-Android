//
// Created by william on 2020-02-26.
//

#include "Utils.h"

GLuint  CompileShader(GLenum shaderType, const char *shaderSource) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    GLint compileResult = GL_TRUE;
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