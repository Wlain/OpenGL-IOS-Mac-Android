//
//  ParticleEmitter.hpp
//  OpenGLES-IOS
//
//  Created by william on 2020/3/2.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef ParticleEmitter_hpp
#define ParticleEmitter_hpp
#include "RendererES3.hpp"

class ParticleEmitter : public RendererES3 {
public:
    ParticleEmitter();
    ~ParticleEmitter();
    virtual void Initialize(ESContext *esContext) override;
    virtual void Resize(ESContext *esContext, GLint width, GLint height) override;
    virtual void Update(ESContext *esContext, float deltaTime) override;
    virtual void Draw(ESContext *esContext) override;
    virtual void Finalize(ESContext *esContext) override;
    void SetupVertexAttributes(ESContest *esContext, GLuint vboID);
    void EmitParticles(ESContext *esContext, float deltaTime);
};

#endif /* ParticleEmitter_hpp */
