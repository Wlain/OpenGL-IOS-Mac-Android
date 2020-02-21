//
//  Light.cpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/20.
//  Copyright © 2020 william. All rights reserved.
//

#include "Light.hpp"

Light::Light() {
    
}


Light::~Light() {
    
}

void Light::SetAmbientColor(float r, float g, float b, float a) {
    float ambientColor[] = {r, g, b, a};
    glLightfv(mLightIdentifier, GL_AMBIENT, ambientColor);
}

void Light::SetDiffuseColor(float r, float g, float b, float a) {
    float diffuseColor[] = {r, g, b, a};
    glLightfv(mLightIdentifier, GL_DIFFUSE, diffuseColor);
}

void Light::SetSpecularColor(float r, float g, float b, float a) {
    float specularColor[] = {r, g, b, a};
    glLightfv(mLightIdentifier, GL_SPECULAR, specularColor);
}

void Light::Enable() {
    glEnable(GL_LIGHTING);
    glEnable(mLightIdentifier);
}

DirectionLight::DirectionLight(GLenum lightID) {
    mLightIdentifier = lightID;
}

DirectionLight::~DirectionLight() {
    
}

void DirectionLight::SetPosition(float x, float y, float z) {
    // 无穷远，对应的w是0
    float position[] = {x, y, z, 0.0f};
    glLightfv(mLightIdentifier, GL_POSITION, position);
}

PointLight::PointLight(GLenum lightID) {
    mLightIdentifier = lightID;
}

PointLight::~PointLight() {
    
}

void PointLight::SetPosition(float x, float y, float z) {
    float position[] = {x, y, z, 1.0f};
    glLightfv(mLightIdentifier, GL_POSITION, position);
}

void PointLight::setConstantAttenuationCoe(float c) {
    glLightf(mLightIdentifier, GL_CONSTANT_ATTENUATION, c);
}

void PointLight::setLinearAttenuationCoe(float l) {
    glLightf(mLightIdentifier, GL_LINEAR_ATTENUATION, l);
}

void PointLight::setQuadraticAttenuationCoe(float q) {
    glLightf(mLightIdentifier, GL_QUADRATIC_ATTENUATION, q);
}

SportLight::SportLight(GLenum lightID):PointLight(lightID) {
    
}

SportLight::~SportLight() {
    
}

void SportLight::SetDirection(float x, float y, float z) {
    float direction[] = {x, y, z};
    glLightfv(mLightIdentifier, GL_SPOT_DIRECTION, direction);
}

void SportLight::SetExponent(float v) {
    glLightf(mLightIdentifier, GL_SPOT_EXPONENT, v);
}

void SportLight::SetCutoff(float v) {
    glLightf(mLightIdentifier, GL_SPOT_CUTOFF, v);
}





