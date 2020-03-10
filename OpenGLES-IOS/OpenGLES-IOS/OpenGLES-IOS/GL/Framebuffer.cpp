//
//  Framebuffer.cpp
//  OpenGLES-IOS
//
//  Created by william on 2020/3/10.
//  Copyright © 2020 william. All rights reserved.
//

#include "Framebuffer.hpp"


Framebuffer::Framebuffer():
mFbo(0),
mWidth(0),
mHeight(0) {
    glGenFramebuffers(1, &mFbo);
}

void Framebuffer::AttachColorBuffer(const char *bufferName, GLenum attachment, GLenum dateType, GLint width, GLint height) {
    GLuint colorBuffer;
    glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
    glGenTextures(1, &colorBuffer);
    glBindTexture(GL_TEXTURE_2D, colorBuffer);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    if(dateType == GL_RGBA16F) {
        glTexImage2D(GL_TEXTURE_2D, 0, dateType, width, height, 0, GL_RGBA, GL_UNSIGNED_SHORT, nullptr);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, dateType, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    }
    glBindTexture(GL_TEXTURE_2D, colorBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, colorBuffer, 0);
    mAttachment.push_back(attachment);
    mtextures.insert(std::pair<std::string, GLuint>(bufferName, colorBuffer));
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::AttachDepthBuffer(const char *bufferName, GLint width, GLint height) {
    GLuint depthMap;
    glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    mtextures.insert(std::pair<std::string, GLuint>(bufferName, depthMap));
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Finish() {
    int count = (int)mAttachment.size();
    if (count > 0) {
        GLenum *buffers = new GLenum[count];
        int i = 0;
        while (i < count) {
            buffers[i++] = mAttachment[i];
        }
        glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
        glDrawBuffers(count, buffers);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}

void Framebuffer::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
}

void Framebuffer::UnBind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

const GLuint Framebuffer::GetTexture(const char *bufferName) const {
    auto iter = mtextures.find(bufferName);
    if (iter != mtextures.end()) {
        return iter->second;
    }
    return 0;
}


const GLint Framebuffer::GetWidth() const {
    return this->mWidth;
}

const GLint Framebuffer::GetHeight() const {
    return this->mHeight;
}

