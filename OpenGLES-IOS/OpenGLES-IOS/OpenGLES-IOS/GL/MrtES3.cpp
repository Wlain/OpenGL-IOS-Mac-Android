//
//  MrtES3.cpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/29.
//  Copyright © 2020 william. All rights reserved.
//

#include "MrtES3.hpp"
#include "Utils.hpp"

MrtES3::MrtES3()
:RendererES3(0, 0, 0),
mFbo(0),
mWidth(0),
mHeight(0),
mTextureWidth(0),
mTextureHeight(0){

}

MrtES3::~MrtES3() {
    
}

void MrtES3::DrawGeometry()
{
   GLfloat vVertices[] = { -1.0f,  1.0f, 0.0f,
                           -1.0f, -1.0f, 0.0f,
                            1.0f, -1.0f, 0.0f,
                            1.0f,  1.0f, 0.0f,
                         };
   GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

   // Clear the color buffer
   glClear ( GL_COLOR_BUFFER_BIT );

   // Use the program object
   glUseProgram(mProgram);

   // Load the vertex position
   glVertexAttribPointer ( 0, 3, GL_FLOAT,
                           GL_FALSE, 3 * sizeof ( GLfloat ), vVertices );
   glEnableVertexAttribArray ( 0 );

   // Draw a quad
   glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

GLboolean MrtES3::InitFbo() {
    GLint defaultFramebuffer = 0;
    const GLenum attachments[4] = {
        GL_COLOR_ATTACHMENT0,
        GL_COLOR_ATTACHMENT1,
        GL_COLOR_ATTACHMENT2,
        GL_COLOR_ATTACHMENT3
    };
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFramebuffer);
    
    // setup fbo
    glGenFramebuffers(1, &mFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
    
    // setup four output buffers and attach to fbo
    mTextureHeight = mTextureWidth = 200;
    glGenTextures(4, &mColorTexId[0]);
    for (int i = 0; i < 4; ++i) {
        glBindTexture(GL_TEXTURE_2D, mColorTexId[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mTextureWidth, mTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        // set the filtering mode
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, attachments[i], GL_TEXTURE_2D, mColorTexId[i], 0);
    }
    glDrawBuffers(4, attachments);
    
    if (GL_FRAMEBUFFER_COMPLETE != glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
        return GL_FALSE;
    }
    // Restore the original framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
    return GL_TRUE;
}

void MrtES3::BlitTextures() {
    // set the fbo for reading
    glBindFramebuffer(GL_READ_FRAMEBUFFER, mFbo);
    
    // copy the output red buffer to lower left quadrant
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glBlitFramebuffer(0, 0, mTextureWidth, mTextureHeight,
                      0, 0, mWidth/2, mHeight/2,
                      GL_COLOR_BUFFER_BIT, GL_LINEAR);
    // Copy the output green buffer to lower right quadrant
    glReadBuffer(GL_COLOR_ATTACHMENT1 );
    glBlitFramebuffer( 0, 0, mTextureWidth, mTextureHeight,
                       mWidth/2, 0, mWidth, mHeight/2,
                       GL_COLOR_BUFFER_BIT, GL_LINEAR);
    
    // Copy the output blue buffer to upper left quadrant
    glReadBuffer(GL_COLOR_ATTACHMENT2 );
    glBlitFramebuffer( 0, 0, mTextureWidth, mTextureHeight,
                       0, mHeight/2, mWidth/2, mHeight,
                       GL_COLOR_BUFFER_BIT, GL_LINEAR);
    
    // CCopy the output blue buffer to upper left quadrant
    glReadBuffer(GL_COLOR_ATTACHMENT3 );
    glBlitFramebuffer( 0, 0, mTextureWidth, mTextureHeight,
                       mWidth/2, mHeight/2, mWidth, mHeight,
                       GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void MrtES3::Initialize() {
    int fileSize;
    const char* vertPath = LoadFileContent("Resource/Shader/mrt3.vert", fileSize);
    const char* fragPath = LoadFileContent("Resource/Shader/mrt3.frag", fileSize);
    mProgram = CreateProgram(vertPath, fragPath);
    InitFbo();
}

void MrtES3::Resize(int width, int height) {
    mWidth = width;
    mHeight = height;
}

void MrtES3::Draw() {
    GLint defaultFramebuffer = 0;
    const GLenum attachments[4] =
    {
       GL_COLOR_ATTACHMENT0,
       GL_COLOR_ATTACHMENT1,
       GL_COLOR_ATTACHMENT2,
       GL_COLOR_ATTACHMENT3
    };
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
    glDrawBuffers(4, attachments);
    DrawGeometry();
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, defaultFramebuffer);
    BlitTextures();
}
