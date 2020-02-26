//
// Created by william on 2020-02-26.
//

#include "Scene.h"
#include "Common/Base.h"
#include "Common/Utils.h"

GLuint vbo;
GLuint program;
GLint positionLocation;
GLint modelMatrixLocation;
GLint viewMatrixLocation;
GLint projectionMatrixLocation;
glm::mat4 modelMatrix;
glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;
void Initialize() {
    float vertices[] = {
            -0.2f, -0.2f, -2.0f, 1.0f,
             0.2f, -0.2f, -2.0f, 1.0f,
             0.0f,  0.2f, -2.0f, 1.0f
    };
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
    modelMatrixLocation = glGetUniformLocation(program, "u_modelMatrix");
    viewMatrixLocation = glGetUniformLocation(program, "u_viewMatrix");
    projectionMatrixLocation = glGetUniformLocation(program, "u_projectionMatrix");
}

void SetViewPortSize(float width, float height) {
    projectionMatrix = glm::perspective(45.0f, width / height, 0.1f, 100.0f);
    glViewport(0, 0, width, height);
}

void Draw() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void *)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}