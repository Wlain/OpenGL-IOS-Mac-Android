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
#include "Ground.hpp"

GLuint vbo;
GLuint ebo;
GLuint program;
GLint positionLocation;
GLint worldViewProjectionMatrixLocation;
GLuint texCoordLocation;
GLuint textureLocation;
GLuint texture;
GLuint texture2;
glm::mat4 modelViewMatrix;
glm::mat4 projectionMatrix;
glm::mat4 worldViewProjectionMatrix;
Ground ground;

void Initialize() {
    const float vertexes[] = {
        -0.5f, -0.5f, -4.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -4.0f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -4.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -4.0f, 1.0f, 1.0f, 1.0f,
    };
    const unsigned short indexes[] = {
        0, 1, 2, 1, 2, 3,
    };
    // create vbo
    vbo = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(vertexes), GL_STATIC_DRAW, (void *)vertexes);
    // create ebo
    ebo = CreateBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), GL_STATIC_DRAW, (void *)indexes);
    GLuint vertShader = CompileShader(GL_VERTEX_SHADER, "Resource/Shader/textured.vert");
    GLuint fragShader = CompileShader(GL_FRAGMENT_SHADER, "Resource/Shader/textured.frag");
    program = CreateProgram(vertShader, fragShader);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    positionLocation = glGetAttribLocation(program, "a_position");
    texCoordLocation = glGetAttribLocation(program, "a_texCoord");
    worldViewProjectionMatrixLocation = glGetUniformLocation(program, "u_worldViewProjectionMatrix");
    textureLocation = glGetUniformLocation(program, "u_texture");
    texture = GetTextureFromPNGFile("Resource/UI/logo.png", true);
    ground.Initialize();
}

void SetViewPort(float width, float height) {
    glViewport(0, 0, width, height);
    projectionMatrix = glm::perspective(45.0f, width / height, 0.1f, 100.0f);
    worldViewProjectionMatrix = modelViewMatrix * projectionMatrix;
}

void Draw() {
    float frameTime = GetFrameTime();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ground.Draw(worldViewProjectionMatrix);
    glUseProgram(program);
    glUniformMatrix4fv(worldViewProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(worldViewProjectionMatrix));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureLocation, 0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)0);
    glEnableVertexAttribArray(texCoordLocation);
    glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)(0 + 4 * sizeof(float)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}
