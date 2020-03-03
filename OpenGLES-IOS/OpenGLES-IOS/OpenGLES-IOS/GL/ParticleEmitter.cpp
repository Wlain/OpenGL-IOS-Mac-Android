//
//  ParticleEmitter.cpp
//  OpenGLES-IOS
//
//  Created by william on 2020/3/2.
//  Copyright © 2020 william. All rights reserved.
//
#include "ParticleEmitter.hpp"
#include "Base.h"
#include "Utils.hpp"
#include "Noise3D.hpp"
#include <stddef.h>

#define NUM_PARTICLES   200
#define EMISSION_RATE   0.3f
#define ACCELERATION   -1.0f

#define ATTRIBUTE_POSITION      0
#define ATTRIBUTE_VELOCITY      1
#define ATTRIBUTE_SIZE          2
#define ATTRIBUTE_CURTIME       3
#define ATTRIBUTE_LIFETIME      4

typedef struct {
    GLfloat position[2];
    GLfloat velocity[2];
    GLfloat size;
    GLfloat currenttime;
    GLfloat lifetime;
} Particle;

typedef struct {
    // Handle to a program object
    GLuint emitProgramObject;
    GLuint drawProgramObject;
    
    // Emit shader uniform location
    GLint emitTimeLocation;
    // 粒子发射率
    GLint emitEmissionRateLocation;
    GLint emitNoiseSamplerLocation;
    
    // Draw shader uniform location
    GLint drawTimeLocation;
    GLint drawColorLocation;
    GLint drawAccelerationLocation;
    GLint samplerLocation;
    
    // Texture handles
    GLuint textureId;
    GLuint noiseTextureId;
    
    // Particle vertex data
    Particle particleData[NUM_PARTICLES];
    
    // Particle vbos;
    GLuint particleVBOs[2];
    
    // 索引到粒子VBO的源（0 或者 1）
    GLuint curSrcIndex;
    
    // Current time
    GLfloat time;
    
    // 同步对象以同步变换反馈结果和绘图
    GLsync emitSync;

} Userdata;


ParticleEmitter::ParticleEmitter() {
    
}

ParticleEmitter::~ParticleEmitter() {
    
}

void ParticleEmitter::SetupVertexAttributes(ESContest *esContext, GLuint vboID) {
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glVertexAttribPointer(ATTRIBUTE_POSITION, 2, GL_FLOAT,
                          GL_FALSE, sizeof(Particle),
                          (const void *)(0));
    
    glVertexAttribPointer(ATTRIBUTE_VELOCITY, 2, GL_FLOAT,
                          GL_FALSE, sizeof(Particle),
                          (const void *)offsetof(Particle, velocity[0]));
    
    glVertexAttribPointer(ATTRIBUTE_SIZE, 1, GL_FLOAT,
                          GL_FALSE, sizeof(Particle),
                          (const void *)offsetof(Particle, size));
    
    glVertexAttribPointer(ATTRIBUTE_CURTIME, 1, GL_FLOAT,
                          GL_FALSE, sizeof(Particle),
                          (const void *)offsetof(Particle, currenttime));
    
    glVertexAttribPointer(ATTRIBUTE_LIFETIME, 1, GL_FLOAT,
                          GL_FALSE, sizeof(Particle),
                          (const void *)offsetof(Particle, lifetime));
    glEnableVertexAttribArray(ATTRIBUTE_POSITION);
    glEnableVertexAttribArray(ATTRIBUTE_VELOCITY);
    glEnableVertexAttribArray(ATTRIBUTE_SIZE);
    glEnableVertexAttribArray(ATTRIBUTE_CURTIME);
    glEnableVertexAttribArray(ATTRIBUTE_LIFETIME);
}

void ParticleEmitter::EmitParticles(ESContext *esContext, float deltaTime) {
    Userdata *userData = (Userdata *)esContext->userData;
    GLuint srcVBO = userData->particleVBOs[userData->curSrcIndex];
    GLuint dstVBO = userData->particleVBOs[(userData->curSrcIndex + 1) % 2];
    glUseProgram(userData->emitProgramObject);
    SetupVertexAttributes(esContext, srcVBO);
    
    // Set transform feedback buffer
    glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, dstVBO);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, dstVBO);
    
    // turn off trasterization
    glEnable(GL_RASTERIZER_DISCARD);
    
    glUniform1f(userData->emitTimeLocation, userData->time);
    glUniform1f(userData->emitEmissionRateLocation, EMISSION_RATE);
    
    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, userData->noiseTextureId);
    glUniform1i(userData->emitNoiseSamplerLocation, 0);
    
    // Emit particles using transform feedback
    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS, 0, NUM_PARTICLES);
    glEndTransformFeedback();
    
    // create a sync object to ensure transform feedback result are completed before the draw that uses them
    userData->emitSync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
    
    // Restore state
    glDisable(GL_RASTERIZER_DISCARD);
    glUseProgram(0);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_3D, 0);
    
    // sync thr buffers
    userData->curSrcIndex = (userData->curSrcIndex + 1) % 2;
}

void ParticleEmitter::Initialize(ESContext *esContext) {
    Particle particleData[NUM_PARTICLES];
    esContext->userData = malloc(sizeof(Userdata));
    Userdata *userData = (Userdata *)esContext->userData;
    int fileSize = 0;
    const char *vertEmitterSrc = nullptr;
    const char *fragEmitterSrc = nullptr;
    const char *vertEmitterDrawSrc = nullptr;
    const char *fragEmitterDrawSrc = nullptr;
    vertEmitterSrc = LoadFileContent("Resource/Shader/ParticleEmitter3.vert", fileSize);
    fragEmitterSrc = LoadFileContent("Resource/Shader/ParticleEmitter3.frag", fileSize);
    userData->emitProgramObject = CreateProgram(vertEmitterSrc, fragEmitterSrc);
    if (userData->emitProgramObject == 0) {
        esLogMessage("create Program emitProgramObject failed");
        goto exit;
    }
    vertEmitterDrawSrc = LoadFileContent("Resource/Shader/ParticleDraw3.vert", fileSize);
    fragEmitterDrawSrc = LoadFileContent("Resource/Shader/ParticleDraw3.frag", fileSize);
    userData->drawProgramObject = CreateProgram(vertEmitterDrawSrc, fragEmitterDrawSrc);
    if (userData->drawProgramObject == 0) {
        esLogMessage("create Program drawProgramObject failed");
        goto exit;
    }
    {
        const char *feedbackVaryings[5] = {
            "v_position",
            "v_velocity",
            "v_size",
            "v_currenttime",
            "v_lifetime"
        };
        
        // set the vertex shader outputs as transform feedback varyings
        glTransformFeedbackVaryings(userData->emitProgramObject, 5, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);
        
        // link program must occur after calling glTransformFeedbackVaryings
        glLinkProgram(userData->emitProgramObject);
        
        // 获取uniform的位置，这也需要在再次调用glLinkProgram之后发生，确保输出到变量的uniform是激活的
        userData->emitTimeLocation = glGetUniformLocation(userData->emitProgramObject, "u_time");
        userData->emitEmissionRateLocation = glGetUniformLocation(userData->emitProgramObject, "u_emissionRate");
        userData->emitNoiseSamplerLocation = glGetUniformLocation(userData->emitProgramObject, "s_noiseTexture");
    }
    {
        userData->drawTimeLocation = glGetUniformLocation(userData->drawProgramObject, "u_time");
        userData->drawColorLocation = glGetUniformLocation(userData->drawProgramObject, "u_color");
        userData->drawAccelerationLocation = glGetUniformLocation(userData->drawProgramObject, "u_acceleration");
        userData->samplerLocation = glGetUniformLocation(userData->drawProgramObject, "u_texture");
        
        userData->time = 0.0f;
        userData->curSrcIndex = 0;
        
        userData->noiseTextureId = Create3DNoiseTexture(128, 50.0);
        if (userData->noiseTextureId <= 0) {
            esLogMessage("create noiseTextureId failed");
            goto exit;
        }
        userData->textureId = GetTextureFromFile("Resource/UI/ball.png", true);
        if (userData->textureId <= 0) {
            esLogMessage("create textureId failed");
            goto exit;
        }
        // Initialize particle data
        for (int i = 0; i < NUM_PARTICLES; ++i) {
            Particle *particle = &particleData[i];
            particle->position[0] = 0.0f;
            particle->position[1] = 0.0f;
            particle->velocity[0] = 0.0f;
            particle->velocity[1] = 0.0f;
            particle->size = 0.0f;
            particle->currenttime = 0.0f;
            particle->lifetime = 0.0f;
        }
        
        // Create the particle vbos
        glGenBuffers(2, &userData->particleVBOs[0]);
        for (int i = 0; i < 2; ++i) {
            glBindBuffer(GL_ARRAY_BUFFER, userData->particleVBOs[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * NUM_PARTICLES, particleData, GL_DYNAMIC_COPY);
        }
    }
exit:
    SAFE_DELETE_ARRAY(vertEmitterSrc);
    SAFE_DELETE_ARRAY(fragEmitterSrc);
    SAFE_DELETE_ARRAY(vertEmitterDrawSrc);
    SAFE_DELETE_ARRAY(fragEmitterDrawSrc);
}

void ParticleEmitter::Resize(ESContext *esContext, GLint width, GLint height) {
    
}

void ParticleEmitter::Update(ESContext *esContext, float deltaTime) {
    Userdata *userData = (Userdata *)esContext->userData;
    userData->time += deltaTime;
    EmitParticles(esContext, deltaTime);
}

void ParticleEmitter::Draw(ESContext *esContext) {
    Userdata *userData = (Userdata *)esContext->userData;
    
    // Block the gl server until transform feedback results are completed
    glWaitSync(userData->emitSync, 0, GL_TIMEOUT_IGNORED);
    glDeleteSync(userData->emitSync);
    
    glUseProgram(userData->drawProgramObject);
    
    // Load the vbo and vertex attrib
    SetupVertexAttributes(esContext, userData->particleVBOs[userData->curSrcIndex]);
    
    // set uniforms
    glUniform1f(userData->drawTimeLocation, userData->time);
    glUniform4f(userData->drawColorLocation, (float)(rand() % 10000) / 5000.0f - 1.0f, (float)(rand() % 10000) / 5000.0f - 1.0f, (float)(rand() % 10000) / 5000.0f - 1.0f, 1.0f );
    glUniform2f(userData->drawAccelerationLocation, 0.0f, ACCELERATION);
    
    // blend uniform
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, userData->textureId);
    
    // Set the sampler texture unit to 0
    glUniform1i(userData->samplerLocation, 0);
    glDrawArrays(GL_POINTS, 0, NUM_PARTICLES);
}

void ParticleEmitter::Finalize(ESContext *esContext) {
    Userdata *userData = (Userdata *)esContext->userData;
    glDeleteTextures(1, &userData->textureId);
    glDeleteTextures(1, &userData->noiseTextureId);
    glDeleteProgram(userData->drawProgramObject);
    glDeleteProgram(userData->emitProgramObject);
    glDeleteBuffers(2, &userData->particleVBOs[0]);
    SAFE_FREE(esContext->userData);
}
