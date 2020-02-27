//
// Created by william on 2020-02-26.
//

#ifndef OPENGLES_ANDROID_UTILS_H
#define OPENGLES_ANDROID_UTILS_H

#include "Base.h"

unsigned char* LoadFileContent(const char *filePath, int &fileSize);

GLuint  CompileShader(GLenum shaderType, const char *shaderSource);

GLuint CreateProgram(GLuint vertShader, GLuint fragShader);

GLuint CreateTextureFromFile(const char *filePath, bool flipVertical);

GLuint CreateProceduretexture(int size);

float GetFrameTime();



#endif //OPENGLES_ANDROID_UTILS_H
