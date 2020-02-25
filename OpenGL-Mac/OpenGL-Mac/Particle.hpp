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
    float GetLifeTime() const;
    void SetLifeTime(float time);
    float GetStartTime() const;
    void SetStartTime(float time);
    float GetCurrentTime() const;
    void SetCurrentTime(float time);
    float GetEndTime() const;
    void SetEndTime(float time);
    GLubyte* const GetColor();
    void SetColor(GLubyte color[]);
    const Vector3f& GetPosition() const;
    void SetPosition(const Vector3f &v);
    void Init(GLubyte r, GLubyte g, GLubyte b, GLubyte a, float life);
    void Draw();
    void Update(float deltaTime);
private:
    GLuint mTexture;
    float mHalfSize;
    float mLifeTime;        // 粒子生命值
    float mStartTime;       // 粒子开始出生的时间
    float mCurrentTime;     // 粒子出生到现在存活的时间
    float mEndTime;         // 粒子死亡的时间
    GLubyte mColor[4];      // 粒子颜色
    Vector3f mPosition;
};


#endif /* Particle_hpp */
