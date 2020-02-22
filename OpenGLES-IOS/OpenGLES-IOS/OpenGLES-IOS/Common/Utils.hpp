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

#endif /* Utils_hpp */
