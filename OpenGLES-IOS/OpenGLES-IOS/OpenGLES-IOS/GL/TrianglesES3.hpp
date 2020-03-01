//
//  TrianglesES3.hpp
//  OpenGLES-IOS
//
//  Created by william on 2020/2/29.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef TrianglesES3_hpp
#define TrianglesES3_hpp
#include "RendererES3.hpp"
#include "Shader.hpp"

class TrianglesES3 : public RendererES3 {
public:
    TrianglesES3();
    virtual ~TrianglesES3();
    virtual void Initialize(ESContext *esContext) override;
    virtual void Draw(ESContext *esContext) override;
    virtual void Resize(ESContext *esContext, GLint width, GLint height) override;
    virtual void Update(ESContext *esContext, float deltaTime) override;
    virtual void Finalize(ESContext *esContext)override;
};

#endif /* TrianglesES3_hpp */
