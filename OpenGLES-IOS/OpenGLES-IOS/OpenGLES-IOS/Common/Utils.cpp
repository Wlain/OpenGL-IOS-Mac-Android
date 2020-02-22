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
