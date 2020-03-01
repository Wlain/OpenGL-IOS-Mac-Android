//
//  Utils.hpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/22.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include "Base.h"

/// 加载文件内容
/// @param filePath 文件路径
/// @param filesize 文件size
const GLchar* LoadFileContent(const GLchar *filePath, GLint &filesize);

/// 创建program
/// @param vertShader 顶点着色器对象
/// @param fragShader 片元着色器对象
GLuint CreateProgram(GLuint vertShader, GLuint fragShader);

/// 获取帧间隔
GLfloat GetFrameTime();

/// 根据图片地址获取纹理id, 支持PNG,JPG
/// @param path 图片文件路径
/// @param flipVertical 是否翻转图片
GLuint GetTextureFromFile(const GLchar *path, bool flipVertical);

/// 生成一张RGBA图片纹理
/// @param width 纹理宽
/// @param height 纹理高
GLuint CreateProceduretexture(GLsizei width, GLsizei height);


/// 创建一个缓冲对象
/// @param bufferType bufferType
/// @param size size
/// @param usage usage
GLuint CreateBufferObject(GLenum bufferType, GLsizeiptr size, GLenum usage, void *data);

static void PrintGLString(const GLchar* name, GLenum s) {
    const GLchar* v = (const GLchar*)glGetString(s);
    printf("GL %s: %s\n", name, v);
}

// 用于外部加载shader
GLuint CreateShader(GLenum shaderType, const char* src);

GLuint CreateProgram(const char* vertSrc, const char* fragSrc);

#endif /* Utils_hpp */
