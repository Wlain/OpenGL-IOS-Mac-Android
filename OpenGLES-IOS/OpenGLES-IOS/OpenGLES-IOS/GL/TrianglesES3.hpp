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

class TrianglesES3 : public RendererES3 {
public:
    TrianglesES3();
    virtual ~TrianglesES3();
    virtual void Initialize() override;
    virtual void Draw() override;
private:
    GLuint mColorVbo;
};

#endif /* TrianglesES3_hpp */
