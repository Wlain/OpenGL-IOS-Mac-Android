//
//  Scene.cpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/22.
//  Copyright © 2020 william. All rights reserved.
//

#include "Scene.hpp"
#include "Base.h"
#include "Utils.hpp"


GLuint vbo;
GLuint ebo;
GLuint program;
GLint positionLocation;
GLint worldViewProjectionMatrixLocation;
GLuint colorLocation;
glm::mat4 modelViewMatrix;
glm::mat4 projectionMatrix;
glm::mat4 worldViewProjectionMatrix;


const float color[] = {
    0.9, 1.0, 0.8, 1.0
};

void Init() {
    const float vertexes[] = {
        -0.2f, -0.2f, -1.0f, 1.0f,
         0.2f, -0.2f, -1.0f, 1.0f,
         0.0f,  0.2f, -1.0f, 1.0f,
    };
    const unsigned short indexes[] = {
        0, 1, 2
    };

    // vbo
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // ebo
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    GLuint vertShader = CompileShader(GL_VERTEX_SHADER, "Resource/Shader/textured.vert");
    GLuint fragShader = CompileShader(GL_FRAGMENT_SHADER, "Resource/Shader/textured.frag");
    program = CreateProgram(vertShader, fragShader);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    positionLocation = glGetAttribLocation(program, "a_position");
    worldViewProjectionMatrixLocation = glGetUniformLocation(program, "u_worldViewProjectionMatrix");
    colorLocation = glGetUniformLocation(program, "u_color");
}

void SetViewPort(float width, float height) {
    projectionMatrix = glm::perspective(45.0f, width / height, 0.1f, 100.0f);
    worldViewProjectionMatrix = modelViewMatrix * projectionMatrix;
}

void Draw() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    float frameTime = GetFrameTime();
    glUseProgram(program);
    glUniformMatrix4fv(worldViewProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(worldViewProjectionMatrix));
    glUniform4fv(colorLocation, 1, color);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
//    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}
