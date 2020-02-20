//
//  SkyBox.hpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/20.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef SkyBox_hpp
#define SkyBox_hpp
#include "Base.h"

class SkyBox {
public:
    SkyBox();
    virtual ~SkyBox();
public:
    void Initialize(const char *fileDir);
    void Draw();
    void DrawCommand();
private:
    GLuint mTextures[6];
};

#endif /* SkyBox_hpp */
