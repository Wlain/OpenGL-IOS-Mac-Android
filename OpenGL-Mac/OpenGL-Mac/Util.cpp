//
//  Util.cpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/19.
//  Copyright © 2020 william. All rights reserved.
//
// 工具类

#include "Util.hpp"

GLuint CreateDisplayList(std::function<void()>foo) {
    // 申请一个显示列表
    GLuint displayList = glGenLists(1);
    glNewList(displayList, GL_COMPILE);
    foo();
    glEndList();
    return displayList;
}
