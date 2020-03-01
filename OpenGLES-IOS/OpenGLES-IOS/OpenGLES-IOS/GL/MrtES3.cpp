//
//  MrtES3.cpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/29.
//  Copyright © 2020 william. All rights reserved.
//

#include "MrtES3.hpp"
#include "Utils.hpp"
#define POSITION_ATTRIB 0
typedef struct {
    // Handle to a program object
    GLuint programObject;
    
    // Handle to a vertex buffer object
    GLuint vbo;
    
    // Handle to a element buffer object
    GLuint ebo;

    // Handle to a framebuffer object
    GLuint fbo;

    // Texture handle
    GLuint colorTexId[4];

    // Texture size
    GLsizei textureWidth;
    GLsizei textureHeight;
} UserData;

MrtES3::MrtES3() {

}

MrtES3::~MrtES3() {
    
}

void MrtES3::DrawGeometry(ESContext *esContext) {
    UserData *userData = (UserData *)esContext->userData;
    // Use the program object
    glUseProgram(userData->programObject);
    
    // Load the vertex position
    glBindBuffer(GL_ARRAY_BUFFER, userData->vbo);
    glVertexAttribPointer (POSITION_ATTRIB, 4, GL_FLOAT,
                           GL_FALSE, 4 * sizeof(GLfloat), (void *)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(POSITION_ATTRIB);
    // Draw a quad
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, userData->ebo);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (void *)(0 * sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLboolean MrtES3::InitFbo(ESContext *esContext) {
    UserData *userData = (UserData *)esContext->userData;
    GLint defaultFramebuffer = 0;
    const GLenum attachments[4] = {
        GL_COLOR_ATTACHMENT0,
        GL_COLOR_ATTACHMENT1,
        GL_COLOR_ATTACHMENT2,
        GL_COLOR_ATTACHMENT3
    };
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFramebuffer);
    
    // setup fbo
    glGenFramebuffers(1, &userData->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, userData->fbo);
    
    // setup four output buffers and attach to fbo
    userData->textureWidth = userData->textureHeight = 1334;
    glGenTextures(4, &userData->colorTexId[0]);
    for (int i = 0; i < 4; ++i) {
        glBindTexture(GL_TEXTURE_2D, userData->colorTexId[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                     userData->textureWidth, userData->textureHeight,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        // set the filtering mode
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, attachments[i], GL_TEXTURE_2D, userData->colorTexId[i], 0);
    }
    glDrawBuffers(4, attachments);
    
    if (GL_FRAMEBUFFER_COMPLETE != glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
        return GL_FALSE;
    }
    // Restore the original framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
    return GL_TRUE;
}

void MrtES3::BlitTextures(ESContext *esContext) {
    UserData *userData = (UserData *)esContext->userData;
    // set the fbo for reading
    glBindFramebuffer(GL_READ_FRAMEBUFFER, userData->fbo);
    // copy the output red buffer to lower left quadrant
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glBlitFramebuffer(0, 0, esContext->width, esContext->height,
                      0, 0, esContext->width/2, esContext->height/2,
                      GL_COLOR_BUFFER_BIT, GL_LINEAR);
    // Copy the output green buffer to lower right quadrant
    glReadBuffer(GL_COLOR_ATTACHMENT1);
    glBlitFramebuffer(0, 0, esContext->width, esContext->height,
                      esContext->width/2, 0, esContext->width, esContext->height/2,
                      GL_COLOR_BUFFER_BIT, GL_LINEAR);

    // Copy the output blue buffer to upper left quadrant
    glReadBuffer(GL_COLOR_ATTACHMENT2);
    glBlitFramebuffer(0, 0, esContext->width, esContext->height,
                      0, esContext->height/2, esContext->width/2, esContext->height,
                      GL_COLOR_BUFFER_BIT, GL_LINEAR);

    // Copy the output gray buffer to upper right quadrant
    glReadBuffer(GL_COLOR_ATTACHMENT3);
    glBlitFramebuffer(0, 0, esContext->width, esContext->height,
                      esContext->width/2, esContext->height/2, esContext->width, esContext->height,
                      GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void MrtES3::Initialize(ESContext *esContext) {
    esContext->userData = malloc(sizeof(UserData));
    UserData *userData = (UserData *)esContext->userData;
    int fileSize;
    const GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f,
    };
    GLushort indices[] = {0, 1, 2};
    const char* vertPath = LoadFileContent("Resource/Shader/mrt3.vert", fileSize);
    const char* fragPath = LoadFileContent("Resource/Shader/mrt3.frag", fileSize);
    userData->programObject = CreateProgram(vertPath, fragPath);
    InitFbo(esContext);
    userData->vbo = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(vertices), GL_STATIC_DRAW, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, userData->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    userData->ebo = CreateBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), GL_STATIC_DRAW, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, userData->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void MrtES3::Resize(ESContext *esContext, int width, int height) {
    
}

void MrtES3::Update(ESContext *esContext, float deltaTime) {
    
}

void MrtES3::Draw(ESContext *esContext) {
    UserData *userDate = (UserData *)esContext->userData;
    GLint defaultFramebuffer = 0;
    const GLenum attachments[4] = {
       GL_COLOR_ATTACHMENT0,
       GL_COLOR_ATTACHMENT1,
       GL_COLOR_ATTACHMENT2,
       GL_COLOR_ATTACHMENT3
    };
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFramebuffer);
    // FIRST: use MRTs to output four colors to four buffers
    glBindFramebuffer(GL_FRAMEBUFFER, userDate->fbo);
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glDrawBuffers(4, attachments);
    DrawGeometry(esContext);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, defaultFramebuffer);
    // SECOND: copy the four output buffers into four window quadrants
    // with framebuffer blits
    BlitTextures(esContext);
    GLERROR_CHECK();
}

void MrtES3::Finalize(ESContext *esContext) {
    UserData *userData = (UserData *)esContext->userData;
    glDeleteBuffers(1, &userData->vbo);
    glDeleteBuffers(1, &userData->ebo);
    glDeleteTextures(4, userData->colorTexId);
    glDeleteFramebuffers(1, &userData->fbo);
    glDeleteProgram(userData->programObject);
    SAFE_FREE(esContext->userData);
}
