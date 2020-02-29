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

class RendererES3{
public:
    RendererES3(GLuint m, GLuint v);
    virtual ~RendererES3();
    virtual void Initialize() = 0;
    virtual void Draw() = 0;
protected:
    GLuint mProgram;
    GLuint mVbo;
};

#endif /* RendererES3_hpp */
