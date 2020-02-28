//
//  SkyBox.cpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/20.
//  Copyright © 2020 william. All rights reserved.
//

#include "SkyBox.hpp"
#include "Utils.hpp"

SkyBox::SkyBox() {
    
}

SkyBox::~SkyBox() {
    
}



void SkyBox::Initialize(const char *fileDir) {
    const unsigned int fileDirSize = 256;
    char temp[fileDirSize];
    memset(temp, 0, fileDirSize);
    strcpy(temp, fileDir);
    strcat(temp, "front.jpg");
    mTextures[0] = TextureFromFile(temp, true);
    memset(temp, 0, fileDirSize);
    strcpy(temp, fileDir);
    strcat(temp, "back.jpg");
    mTextures[1] = TextureFromFile(temp, true);
    memset(temp, 0, fileDirSize);
    strcpy(temp, fileDir);
    strcat(temp, "left.jpg");
    mTextures[2] = TextureFromFile(temp, true);
    memset(temp, 0, fileDirSize);
    strcpy(temp, fileDir);
    strcat(temp, "right.jpg");
    mTextures[3] = TextureFromFile(temp, true);
    memset(temp, 0, fileDirSize);
    strcpy(temp, fileDir);
    strcat(temp, "top.jpg");
    mTextures[4] = TextureFromFile(temp, true);
    memset(temp, 0, fileDirSize);
    strcpy(temp, fileDir);
    strcat(temp, "bottom.jpg");
    mTextures[5] = TextureFromFile(temp, true);
    mFastDrawCall = CreateDisplayList([this]()->void { DrawCommand(); });
}


void SkyBox::DrawCommand() {
    glPushMatrix();
    // 不希望天空盒受到光照的影响
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mTextures[0]);
    glBegin(GL_TRIANGLE_STRIP);
    glColor4ub(255, 255, 255, 255);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, mTextures[1]);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, mTextures[2]);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, mTextures[3]);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, mTextures[4]);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, mTextures[5]);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();
    glPopMatrix();
}

void SkyBox::Draw(float x, float y, float z) {
    glPushMatrix();
    glTranslated(x, y, z);
    glCallList(mFastDrawCall);
    glPopMatrix();
}


