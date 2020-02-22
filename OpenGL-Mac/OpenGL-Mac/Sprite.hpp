//
//  Sprite.hpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/22.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp
#include "Vector3f.hpp"
#include "Base.h"

class Sprite {
public:
    Sprite();
    ~Sprite();
    void SetImage(const char *imagePath);
    void SetRectangle(float x, float y, float width, float height);
    void Draw();
private:
    GLuint mTexture;
    Vector3f mVertexes[4];
   
};

#endif /* Sprite_hpp */
