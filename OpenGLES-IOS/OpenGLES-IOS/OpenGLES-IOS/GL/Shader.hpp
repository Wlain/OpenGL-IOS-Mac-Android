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

struct UniformTexture {
    GLint mLocation;
    GLuint mTexture;
    UniformTexture() {
        mLocation = -1; // 纹理位置
        mTexture = 0;   // 纹理对象
    }
};

struct UniformVector4 {
    GLint mLocation;
    GLfloat v[4];
    UniformVector4() {
        mLocation = -1;          // 纹理位置
        memset(v, 0, sizeof(v)); // 顶点数据
    }
};


class Shader {
public:
    Shader();
    virtual ~Shader();
    GLuint GetProgram() const;
    void SetTexture(const GLchar *name, GLuint texture);
    void SetTexture(const GLchar *name, const GLchar *imagePath);
    void Setvector4(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void Initialize(const GLchar *vertShaderPath, const GLchar *fragShaderPath);
    void Bind(glm::mat4 &modelMatrix, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
protected:
    GLuint CompileShader(GLenum shaderType, const GLchar* src);
private:
    GLuint mProgram;
    // location 默认是-1
    GLint mPositionLocation;
    GLint mTexCoordLocation;
    GLint mColorLocation;
    GLint mNormalLocation;
    GLint mModelMatrixLocation;
    GLint mViewMatrixLocation;
    GLint mProjectionMatrixLocation;
    std::map<std::string, UniformTexture *> mUniformTextures;
    std::map<std::string, UniformVector4 *> mUniformVector4s;
};

#endif /* Shader_hpp */
