//
// Created by william on 2020-02-26.
//

#include "Scene.h"
#include "Base.h"


void Initialize() {

}

void SetViewPortSize(float width, float height) {
    glViewport(0, 0, width, height);
}

void Draw() {
    glClearColor(0.1f, 0.4f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}