//
//  Particle.hpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/22.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef Particle_hpp
#define Particle_hpp
#include "Vector3f.hpp"
#include "Base.h"

class Particle {
public:
    Particle();
    ~Particle();
    GLuint GetTexture() const;
    void SetTexture(GLuint texture);
    float GetHalfSize() const;
    void SetHalfSize(float size);
    const Vector3f& GetPosition() const;
    void SetPosition(const Vector3f &v);
    void Draw();
private:
    GLuint mTexture;
    float mHalfSize;
    Vector3f mPosition;
};


#endif /* Particle_hpp */
