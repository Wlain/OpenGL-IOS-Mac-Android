//
//  ParticleSystem3.cpp
//  OpenGLES-IOS
//
//  Created by william on 2020/3/1.
//  Copyright © 2020 william. All rights reserved.
//

#include "ParticleSystem3.hpp"
#include "Utils.hpp"

#define NUM_PARTICLES   1000
#define PARTICLE_SIZE   7

#define ATTRIBUTE_LIFETIME_LOCATION       0
#define ATTRIBUTE_STARTPOSITION_LOCATION  1
#define ATTRIBUTE_ENDPOSITION_LOCATION    2

typedef struct {
    // Handle to a program object
    GLuint programObject;
    
    // Uniform location
    GLint timeLocation;
    GLint colorLocation;
    GLint centerPositionLocation;
    GLint samplerLocation;
    
    // Texture handle;
    GLuint textureID;
    
    // Particle vertex Date
    float particleData[NUM_PARTICLES * PARTICLE_SIZE];
    
    // vbo
    GLuint vbo;
    
    // vao
    GLuint vao;
    
    // Current time
    GLfloat time;
} UserData;

ParticleSystem3::ParticleSystem3() {
    
}

ParticleSystem3::~ParticleSystem3() {
    
}

void ParticleSystem3::Initialize(ESContext *esContext) {
    esContext->userData = malloc(sizeof(UserData));
    UserData *userData = (UserData *)esContext->userData;
    int fileSize = 0;
    const char* vertPath = LoadFileContent("Resource/Shader/ParticleSystem3.vert", fileSize);
    const char* fragPath = LoadFileContent("Resource/Shader/ParticleSystem3.frag", fileSize);
    userData->programObject = CreateProgram(vertPath, fragPath);
    SAFE_DELETE_ARRAY(vertPath);
    SAFE_DELETE_ARRAY(fragPath);
    userData->timeLocation = glGetUniformLocation(userData->programObject, "u_time");
    userData->centerPositionLocation = glGetUniformLocation(userData->programObject, "u_centerPosition");
    userData->colorLocation = glGetUniformLocation(userData->programObject, "u_color");
    userData->samplerLocation = glGetUniformLocation(userData->programObject, "u_texture");
    
    // Fill in particle data array
    srand(0);
    
    for (int i = 0; i < NUM_PARTICLES; ++i) {
        GLfloat *particleData = &userData->particleData[i * PARTICLE_SIZE];
        
        // LifeTime of particle
        *particleData++ = (float)(rand() % 10000) / 10000.0f;
        
        // End position of particle
        *particleData++ = (float)(rand() % 10000) / 5000.0f - 1.0f;
        *particleData++ = (float)(rand() % 10000) / 5000.0f - 1.0f;
        *particleData++ = (float)(rand() % 10000) / 5000.0f - 1.0f;
        
        // Start Position of particle
        *particleData++ = (float)(rand() % 10000) / 40000.0f - 0.125f;
        *particleData++ = (float)(rand() % 10000) / 40000.0f - 0.125f;
        *particleData++ = (float)(rand() % 10000) / 40000.0f - 0.125f;
    }
    // Initialize time to cause reset on first update
    userData->time = 1.0f;
    
    userData->textureID = GetTextureFromFile("Resource/UI/smoke.png", true);
    
    if (userData->textureID <= 0) {
        esLogMessage("create textureID error");
    }
    userData->vbo = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(userData->particleData), GL_STATIC_DRAW, nullptr);
    
    glBindBuffer(GL_ARRAY_BUFFER, userData->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(userData->particleData), userData->particleData, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &userData->vao);
    glBindVertexArray(userData->vao);
    glBindBuffer(1, userData->vbo);
    glVertexAttribPointer(ATTRIBUTE_LIFETIME_LOCATION, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *)(0 * sizeof(GLfloat)));
    glVertexAttribPointer(ATTRIBUTE_ENDPOSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat),  (void *)(1 * sizeof(GLfloat)));
    glVertexAttribPointer(ATTRIBUTE_STARTPOSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat),  (void *)(4 * sizeof(GLfloat)));
    glEnableVertexAttribArray(ATTRIBUTE_LIFETIME_LOCATION);
    glEnableVertexAttribArray(ATTRIBUTE_ENDPOSITION_LOCATION);
    glEnableVertexAttribArray(ATTRIBUTE_STARTPOSITION_LOCATION);
    glBindBuffer(1, 0);
    glBindVertexArray(0);
}

void ParticleSystem3::Resize(ESContext *esContext, GLint width, GLint height) {
    
}

void ParticleSystem3::Update(ESContext *esContext, float deltaTime) {
    UserData *userData = (UserData *)esContext->userData;
    userData->time += deltaTime / 8;
    glUseProgram(userData->programObject);
    if (userData->time >= 1.0f) {
        GLfloat centerPosition[3];
        GLfloat color[4];
        userData->time = 0.0;
        // new a new start location and color
        centerPosition[0] = (float)(rand() % 10000) / 10000.0f - 0.5f;
        centerPosition[1] = (float)(rand() % 10000) / 10000.0f - 0.5f;
        centerPosition[2] = (float)(rand() % 10000) / 10000.0f - 0.5f;
        
        glUniform3fv(userData->centerPositionLocation, 1, centerPosition);
        
        color[0] = (float)(rand() % 10000) / 20000.0f + 0.5f;
        color[1] = (float)(rand() % 10000) / 20000.0f + 0.5f;
        color[2] = (float)(rand() % 10000) / 20000.0f + 0.5f;
        color[3] = 0.5f;
        
        glUniform4fv(userData->colorLocation, 1, color);
    }
    
    // Load uniform time variable
    glUniform1f(userData->timeLocation, userData->time);
}

void ParticleSystem3::Draw(ESContest *esContext) {
    UserData *userData = (UserData *)esContext->userData;
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(userData->programObject);

    glBindVertexArray(userData->vao);
    // Blend particles
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, userData->textureID);
    
    // Set the sample texture unid to 0
    glUniform1i(userData->samplerLocation, 0);
    glDrawArrays(GL_POINTS, 0, NUM_PARTICLES);
    glBindVertexArray(0);
}

void ParticleSystem3::Finalize(ESContext *esContext) {
    UserData *userData = (UserData *)esContext->userData;
    glDeleteVertexArrays(1, &userData->vao);
    glDeleteBuffers(1, &userData->vbo);
    glDeleteTextures(1, &userData->textureID);
    glDeleteProgram(userData->programObject);
    SAFE_FREE(esContext->userData);
}
