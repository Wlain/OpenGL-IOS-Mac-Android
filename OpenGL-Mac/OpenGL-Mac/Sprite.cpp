//
//  Sprite.cpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/22.
//  Copyright © 2020 william. All rights reserved.
//

#include "Sprite.hpp"
#include "Utils.hpp"


Sprite::Sprite():mTexture(0) {
    for (int i = 0; i < sizeof(mVertexes) / sizeof(Vector3f); ++i) {
        std::memset(&mVertexes[i], 0, sizeof(Vector3f));
    }
}

Sprite::~Sprite() {
    
}

void Sprite::SetImage(const char *imagePath) {
    mTexture = TextureFromFile(imagePath, true);
}

void Sprite::SetRectangle(float x, float y, float width, float height) {
    // left - bottom
    mVertexes[0].x = x;
    mVertexes[0].y = y;
    // right - bottom
    mVertexes[1].x = x + width;
    mVertexes[1].y = y;
    // right - top
    mVertexes[2].x = x + width;
    mVertexes[2].y = y + height;
    // left - top
    mVertexes[3].x = x;
    mVertexes[3].y = y + height;
}

void Sprite::Draw() {
    glEnable(GL_BLEND);
    // alpha混合对应shader的mix
    // SRC * SRC_ALPHA + DST * (1.0 - SRC_ALPHA);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glDisable(GL_LIGHTING);
    glColor4ub(255, 255, 255, 255);
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(mVertexes[0].x, mVertexes[0].y, mVertexes[0].z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(mVertexes[1].x, mVertexes[1].y, mVertexes[1].z);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(mVertexes[3].x, mVertexes[3].y, mVertexes[3].z);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(mVertexes[3].x, mVertexes[3].y, mVertexes[3].z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(mVertexes[1].x, mVertexes[1].y, mVertexes[1].z);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(mVertexes[2].x, mVertexes[2].y, mVertexes[2].z);
    glEnd();
    glDisable(GL_BLEND);
}



