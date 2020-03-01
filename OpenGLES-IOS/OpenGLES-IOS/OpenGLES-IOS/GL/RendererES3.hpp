//
//  RendererES3.hpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/28.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef RendererES3_hpp
#define RendererES3_hpp
#include "Base.h"
#include "Scene.hpp"

class RendererES3 {
public:
    RendererES3();
    virtual ~RendererES3();
    virtual void Initialize(ESContext *esContext) = 0;
    virtual void Draw(ESContext *esContext) = 0;
    virtual void Resize(ESContext *esContext, GLint width, GLint height) = 0;
    virtual void Update(ESContext *esContext, float deltaTime) = 0;
    virtual void Finalize(ESContext *esContext) = 0;
};

#endif /* RendererES3_hpp */
