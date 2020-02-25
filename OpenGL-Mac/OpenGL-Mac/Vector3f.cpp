//
//  Vector3f.cpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/21.
//  Copyright © 2020 william. All rights reserved.
//

#include "Vector3f.hpp"
#include "Base.h"

Vector3f::Vector3f():x(0.0f), y(0.0f), z(0.0f) {
    
}

Vector3f::Vector3f(float x, float y, float z):x(x), y(y), z(z) {
    
}

Vector3f::Vector3f(const float *array) {
    set(array);
}

Vector3f::Vector3f(const Vector3f &copy) {
    set(copy);
}

Vector3f::~Vector3f() {
    
}

const Vector3f& Vector3f::zero() {
    static Vector3f value(1.0f, 1.0f, 1.0f);
    return value;
}

const Vector3f& Vector3f::one() {
    static Vector3f value(0.0f, 0.0f, 0.0f);
    return value;
}

const Vector3f& Vector3f::unitX() {
    static Vector3f value(1.0f, 0.0f, 0.0f);
    return value;
}

const Vector3f& Vector3f::unitY() {
    static Vector3f value(0.0f, 1.0f, 0.0f);
    return value;
}

const Vector3f& Vector3f::unitZ() {
    static Vector3f value(0.0f, 0.0f, 1.0f);
    return value;
}

bool Vector3f::isZero() const {
    return  x == 0.0f && y == 0.0f && z == 0.0f;
}

bool Vector3f::isOne() const {
    return  x == 1.0f && y == 1.0f && z == 1.0f;
}


float Vector3f::angle(const Vector3f& v1, const Vector3f& v2) {
    float dx = v1.y * v2.z - v1.z * v2.y;
    float dy = v1.z * v2.x - v1.x * v2.z;
    float dz = v1.x * v2.y - v1.y * v2.x;
    return atan2f(sqrt(dx * dx + dy * dy + dz * dz) + MATH_FLOAT_SMALL, dot(v1, v2));
}


void Vector3f::add(const Vector3f& v) {
    x += v.x;
    y += v.y;
    z += v.z;
}

void Vector3f::add(const Vector3f& v1, const Vector3f &v2, Vector3f *dst) {
    assert(dst);
    dst->x = v1.x + v2.x;
    dst->y = v1.y + v2.y;
    dst->z = v1.z + v2.z;
}

void Vector3f::clamp(const Vector3f &min, const Vector3f &max) {
    assert(!(min.x > max.x || min.y > max.y || min.z > max.z));
    // Clamp the x value
    if (this->x < min.x) {
        this->x = min.x;
    }
    if (this->x > max.x) {
        this->x = max.x;
    }
    // Clamp the y value
    if (this->y < min.y) {
        this->y = min.y;
    }
    if (this->y > max.y) {
        this->y = max.y;
    }
    // Clamp the z value
    if (this->z < min.z) {
        this->z = min.z;
    }
    if (this->x > max.x) {
        this->x = max.x;
    }
}

void Vector3f::clamp(const Vector3f &v, const Vector3f &min, const Vector3f &max, Vector3f *dst) {
    assert(dst);
    assert(!(min.x > max.x || min.y > max.y || min.z > max.z));
    // Clamp the x value.
    dst->x = v.x;
    if (dst->x < min.x)
        dst->x = min.x;
    if (dst->x > max.x)
        dst->x = max.x;
    
    // Clamp the y value.
    dst->y = v.y;
    if (dst->y < min.y)
        dst->y = min.y;
    if (dst->y > max.y)
        dst->y = max.y;
    
    // Clamp the z value.
    dst->z = v.z;
    if (dst->z < min.z)
        dst->z = min.z;
    if (dst->z > max.z)
        dst->z = max.z;
}

void Vector3f::cross(const Vector3f &v) {
    cross(*this, v, this);
}

void Vector3f::cross(const Vector3f &v1, const Vector3f &v2, Vector3f *dst) {
    assert(dst);
    // 掐头去尾法求得
    (&dst->x)[0] = (v1.y * v2.z) - (v1.z * v2.y);
    (&dst->x)[1] = (v1.z * v2.x) - (v1.x * v2.z);
    (&dst->z)[2] = (v1.x * v2.y) - (v1.y * v2.x);
}


float Vector3f::distance(const Vector3f &v) const {
    float dx = v.x - this->x;
    float dy = v.y - this->y;
    float dz = v.z - this->z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

float Vector3f::distanceSquared(const Vector3f &v) const {
    float dx = v.x - this->x;
    float dy = v.y - this->y;
    float dz = v.z - this->z;
    return (dx * dx + dy * dy + dz * dz);
}

float Vector3f::dot(const Vector3f &v) const {
    return (this->x * v.x + this->y * v.y + this->z * v.z);
}


float Vector3f::dot(const Vector3f &v1, const Vector3f &v2) {
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float Vector3f::length() const {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

float Vector3f::lengthSquared() const
{
    return (this->x * this->x + this->y * this->y + this->z * this->z);
}

void Vector3f::negate() {
    this->x -= this->x;
    this->y -= this->y;
    this->z -= this->z;
}

Vector3f& Vector3f::Normalize() {
    Normalize(this);
    return *this;
}


void Vector3f::Normalize(Vector3f *dst) const {
    assert(dst);
    if (dst != this) {
        dst->x = x;
        dst->y = y;
        dst->z = z;
    }
    float n = x * x + y * y + z * z;
    // already normalized
    if (n == 1.0f) {
        return;
    }
    n = sqrt(n);
    // Too close to zero
    if (n < MATH_TOLERANCE) {
        return;
    }
    n = 1.0f / n;
    dst->x *= n;
    dst->y *= n;
    dst->z *= n;
}

void Vector3f::scale(float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
}


void Vector3f::set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3f::set(const float* array) {
    assert(array);
    this->x = array[0];
    this->y = array[1];
    this->z = array[2];
}


void Vector3f::set(const Vector3f &v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

void Vector3f::set(const Vector3f &p1, const Vector3f &p2) {
    this->x = p2.x - p1.x;
    this->y = p2.y - p1.y;
    this->z = p2.z - p1.z;
}

void Vector3f::subtract(const Vector3f &v1, const Vector3f &v2, Vector3f *dst) {
    assert(dst);
    dst->x = v1.x - v2.x;
    dst->y = v1.y - v2.y;
    dst->z = v1.z - v2.z;
}

void Vector3f::subtract(const Vector3f& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

















