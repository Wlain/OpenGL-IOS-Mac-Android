//
//  Scene.cpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/19.
//  Copyright © 2020 william. All rights reserved.
//
//                 y  ^
//                    |
//                    |
//                    |
//                    |
//    ------------------------------------------->
//                    | (0,0,0)                        x
//                    |
//                    |
//                    |
// z轴指向屏幕外面

#include "Scene.hpp"

void Initialize() {
    std::cout << "initialize" << std::endl;
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Draw() {
    std::cout << "draw" << std::endl;
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    // 默认情况下，逆时针是OpenGL的正面
    glColor4ub(255, 0, 0, 255);
    glVertex3f(-0.2f, -0.2f, -1.0f);
    glColor4ub(0, 255, 0, 255);
    glVertex3f(0.2f, -0.2f, -1.0f);
    glColor4ub(0, 0, 255, 255);
    glVertex3f(0.0f, 0.2f, -1.0f);
    glEnd();
}
