//
//  Util.cpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/19.
//  Copyright © 2020 william. All rights reserved.
//
// 工具类

#include "Utils.hpp"

GLuint CreateDisplayList(std::function<void()>foo) {
    // 申请一个显示列表
    GLuint displayList = glGenLists(1);
    glNewList(displayList, GL_COMPILE);
    foo();
    glEndList();
    return displayList;
}

GLuint CreateProceduretexture(int size) {
    GLubyte *imageData = new GLubyte[size * size * 4];
    float halfSize = (float)size / 2.0f;
    float maxDistance = sqrtf(halfSize * halfSize + halfSize * halfSize);
    float centerX = halfSize;
    float centerY = halfSize;
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            int currentPixelOffset = (x + y * size) * 4;
            imageData[currentPixelOffset] = 255;
            imageData[currentPixelOffset + 1] = 255;
            imageData[currentPixelOffset + 2] = 255;
            float deltaX = (float)x - centerX;
            float deltaY = (float)y - centerY;
            float distance = sqrtf(deltaX * deltaX + deltaY * deltaY);
            float alpha = powf(1.0f - (distance / maxDistance), 10.0f);
            alpha = alpha > 1.0f ? 1.0f : alpha;
            imageData[currentPixelOffset + 3] = (unsigned char)(alpha * 255.0f);
        }
    }
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    glBindTexture(GL_TEXTURE_2D, 0);
    delete[] imageData;
    return texture;
}
