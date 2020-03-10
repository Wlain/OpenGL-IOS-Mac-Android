//
//  Framebuffer.hpp
//  OpenGLES-IOS
//
//  Created by william on 2020/3/10.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef Framebuffer_hpp
#define Framebuffer_hpp
#include "Base.h"

class Framebuffer {
public:
    Framebuffer();
    ~Framebuffer();
    const GLint GetWidth() const;
    const GLint GetHeight() const;
    const GLuint GetTexture(const char *bufferName) const;
    void Finish();
    void Bind();
    void UnBind();
    void AttachColorBuffer(const char *bufferName, GLenum attachment, GLenum dateType, GLint width, GLint height);
    void AttachDepthBuffer(const char *bufferName, GLint width, GLint height);
private:
    GLuint mFbo;
    GLint mWidth;
    GLint mHeight;
    std::map<std::string, GLuint> mtextures;
    std::vector<GLenum> mAttachment;
};

#endif /* Framebuffer_hpp */
