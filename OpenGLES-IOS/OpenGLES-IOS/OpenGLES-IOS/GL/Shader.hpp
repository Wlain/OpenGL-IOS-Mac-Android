//
//  Shader.hpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/23.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include "Base.h"

class Shader {
public:
    Shader();
    virtual ~Shader();
    GLuint GetProgram() const;
    void SetProgram(GLuint program);
    GLint GetPositionLocation() const;
    void SetPositionLocation(GLint location);
    GLint GetTexCoordLocation() const;
    void SetTexCoordLocation(GLint location);
    GLint GetColorLocation() const;
    void SetColorLocation(GLint location);
    GLint GetNormalLocation() const;
    void SetNormalLocation(GLint location);
    GLint GetWorldViewProjectionMatrixLocation() const;
    void SetWorldViewProjectionMatrixLocation(GLint location);
    void Initialize(const char *vertShaderPath, const char *fragShaderPath);
    void Bind(float *mvpMatrix);
    
protected:
    GLuint CompileShader(GLenum shaderType, const char*shaderCode);
    
private:
    GLuint mProgram;
    // location 默认是-1
    GLint mPositionLocation;
    GLint mTexCoordLocation;
    GLint mColorLocation;
    GLint mNormalLocation;
    GLint mWorldViewProjectionMatrixLocation;
};

#endif /* Shader_hpp */
