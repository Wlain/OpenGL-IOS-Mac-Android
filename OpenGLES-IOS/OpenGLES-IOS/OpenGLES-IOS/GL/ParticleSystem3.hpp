//
//  ParticleSystem3.hpp
//  OpenGLES-IOS
//
//  Created by william on 2020/3/1.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef ParticleSystem3_hpp
#define ParticleSystem3_hpp
#include "RendererES3.hpp"

class ParticleSystem3 : public RendererES3  {
public:
    ParticleSystem3();
    ~ParticleSystem3();
    virtual void Initialize(ESContext *esContext) override;
    virtual void Resize(ESContext *esContext, GLint width, GLint height) override;
    virtual void Update(ESContext *esContext, float deltaTime) override;
    virtual void Draw(ESContest *esContext) override;
    virtual void Finalize(ESContext *esContext) override;
};

#endif /* ParticleSystem3_hpp */
