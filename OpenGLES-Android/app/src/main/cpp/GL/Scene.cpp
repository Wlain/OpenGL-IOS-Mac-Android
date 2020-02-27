//
// Created by william on 2020-02-26.
//

#include "Scene.h"
#include "Common/Base.h"
#include "Common/Utils.h"

GLuint vbo;
GLuint ebo;
GLuint program;
GLint positionLocation;
GLint textureLocation;
GLint texCoordLocation;
GLint modelMatrixLocation;
GLint viewMatrixLocation;
GLint projectionMatrixLocation;
GLuint texture;
glm::mat4 modelMatrix;
glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;
void Initialize() {
    const float vertexes[] = {
            -1.0f, -1.0f, -5.0f, 1.0f, 0.0f, 0.0f,
             1.0f, -1.0f, -5.0f, 1.0f, 1.0f, 0.0f,
            -1.0f,  1.0f, -5.0f, 1.0f, 0.0f, 1.0f,
             1.0f,  1.0f, -5.0f, 1.0f, 1.0f, 1.0f,
    };
    const unsigned short indexes[] = {
            0, 1, 2, 2, 1, 3
    };
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    int filesize = 0;
    unsigned char *vertShaderSource = LoadFileContent("Resource/Shader/textured.vert", filesize);
    unsigned char *fragShaderSource = LoadFileContent("Resource/Shader/textured.frag", filesize);
    GLuint vertShader = CompileShader(GL_VERTEX_SHADER, (char*)vertShaderSource);
    GLuint fragShader = CompileShader(GL_FRAGMENT_SHADER, (char*)fragShaderSource);
    SAFE_DELETE_ARRAY(vertShaderSource);
    SAFE_DELETE_ARRAY(fragShaderSource);
    program = CreateProgram(vertShader, fragShader);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    positionLocation = glGetAttribLocation(program, "a_position");
    texCoordLocation = glGetAttribLocation(program, "a_texCoord");
    modelMatrixLocation = glGetUniformLocation(program, "u_modelMatrix");
    viewMatrixLocation = glGetUniformLocation(program, "u_viewMatrix");
    projectionMatrixLocation = glGetUniformLocation(program, "u_projectionMatrix");
    textureLocation = glGetUniformLocation(program, "u_texture");
    texture = CreateTextureFromFile("Resource/UI/logo.png", true);
}

void SetViewPortSize(float width, float height) {
    projectionMatrix = glm::perspective(45.0f, width / height, 0.1f, 100.0f);
    glViewport(0, 0, width, height);
}

void Draw() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    const float frameTime = GetFrameTime();
//    LOGE("current fps: %f\n", 1.0 / frameTime);
    glUseProgram(program);
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureLocation, 0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)0);
    glEnableVertexAttribArray(texCoordLocation);
    glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)(0 + 4 * sizeof(float)));
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}