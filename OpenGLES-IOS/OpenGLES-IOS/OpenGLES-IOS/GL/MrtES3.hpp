//
//  MrtES3.hpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/29.
//  Copyright © 2020 william. All rights reserved.
//

/*
 多重渲染目标（MRT），允许应用程序一次渲染到多格颜色缓冲区；
 */
#ifndef MrtES3_hpp
#define MrtES3_hpp
#include "RendererES3.hpp"
#include "Scene.hpp"

class MrtES3 : public RendererES3 {
public:
    MrtES3();
    virtual ~MrtES3();
    virtual void Initialize(ESContext *esContext) override;
    virtual void Resize(ESContext *esContext, GLint width, GLint height) override;
    virtual void Update(ESContext *esContext, float deltaTime) override;
    virtual void Draw(ESContext *esContext) override;
    virtual void Finalize(ESContext *esContext) override;
    void DrawGeometry(ESContext *esContext);
    // Initialize the framebuffer object and MRTs
    GLboolean InitFbo(ESContext *esContext);
    // Copy MRT output buffers to screen
    void BlitTextures(ESContext *esContext);
};

#endif /* MrtES3_hpp */
