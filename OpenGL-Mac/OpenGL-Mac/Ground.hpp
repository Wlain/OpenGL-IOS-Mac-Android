//
//  Ground.hpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/20.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef Ground_hpp
#define Ground_hpp
#include "Base.h"

class Ground {
public:
    Ground();
    virtual ~Ground();
    void Draw();
    void SetAmbientMaterial(float r, float g, float b, float a);
    void SetDiffuseMaterial(float r, float g, float b, float a);
    void SetSpecularMaterial(float r, float g, float b, float a);
private:
    float mAmbientMaterial[4];
    float mDiffuseMaterial[4];
    float mSpecularMaterial[4];
};

#endif /* Ground_hpp */
