//
//  Light.hpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/20.
//  Copyright © 2020 william. All rights reserved.
//

/*
 c:常数衰减因子
 l:线性衰减因子
 q:平方衰减因子
 d:受光点与光源的距离因子
 f = 1 / (c + l * d + q * q * d );
 光的亮度： 初始亮度 * f
 */

#ifndef Light_hpp
#define Light_hpp
#include "Base.h"

// 基类
class Light {
protected:
    GLenum mLightIdentifier;
    Light();
    
public:
    void SetAmbientColor(float r, float g, float b, float a);
    void SetDiffuseColor(float r, float g, float b, float a);
    void SetSpecularColor(float r, float g, float b, float a);
    void Enable();
    virtual ~Light();
    // 设置光源位置
    virtual void SetPosition(float x, float y, float z) = 0;
};

// 方向光
class DirectionLight : public Light {
public:
    DirectionLight(GLenum lightID);
    ~DirectionLight();
    virtual void SetPosition(float x, float y, float z) override;
};


// 点光源
class PointLight : public Light {
public:
    PointLight(GLenum lightID);
    ~PointLight();
    virtual void SetPosition(float x, float y, float z) override;
    // 设置常数衰减系数
    void setConstantAttenuationCoe(float c);
    // 设置线性衰减系数
    void setLinearAttenuationCoe(float l);
    // 设置平方衰减系数
    void setQuadraticAttenuationCoe(float q);
};

// 聚光灯
class SportLight : public PointLight {
public:
    SportLight(GLenum lightID);
    ~SportLight();
    // 设置聚光灯方向（Direction）
    void SetDirection(float x, float y, float z);
    // 设置聚光灯角衰减指数（Angular attenuation exponent）
    void SetExponent(float v);
    // 设置聚光灯截光角（Cutoff angle：between 0 and 90)
    void SetCutoff(float v);
};

#endif /* Light_hpp */
