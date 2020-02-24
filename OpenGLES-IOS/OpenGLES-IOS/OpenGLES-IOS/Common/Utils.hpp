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
GLubyte* LoadFileContent(const char *filePath, int &filesize);

/// 编译shader
/// @param shaderType shader类型
/// @param shaderPath shader路径
GLuint CompileShader(GLenum shaderType, const char *shaderPath);

/// 创建program
/// @param vertShader 顶点着色器对象
/// @param fragShader 片元着色器对象
GLuint CreateProgram(GLuint vertShader, GLuint fragShader);

/// 获取帧间隔
float GetFrameTime();

/// 根据图片地址获取纹理id
/// @param path 图片文件路径
/// @param flipVertical 是否翻转图片
GLuint GetTextureFromPNGFile(const char *path, bool flipVertical);

/// 生成一张RGBA图片纹理
/// @param width 纹理宽
/// @param height 纹理高
GLuint CreateProceduretexture(GLsizei width, GLsizei height);


/// 创建一个缓冲对象
/// @param bufferType bufferType
/// @param size size
/// @param usage usage
GLuint CreateBufferObject(GLenum bufferType, GLsizeiptr size, GLenum usage, void *data);


#endif /* Utils_hpp */
