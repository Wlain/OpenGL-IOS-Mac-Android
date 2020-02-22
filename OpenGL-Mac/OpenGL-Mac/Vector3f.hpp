//
//  Vector3f.hpp
//  OpenGL-Mac
//
//  Created by william on 2020/2/21.
//  Copyright © 2020 william. All rights reserved.
//

#ifndef Vector3f_hpp
#define Vector3f_hpp

class Vector3f {
public:
    float x;
    float y;
    float z;
    Vector3f();
    Vector3f(float x, float y, float z);
    Vector3f(const float *array);
    Vector3f(const Vector3f &copy);
    ~Vector3f();
    float getMagnitude();
    static const Vector3f& zero();
    static const Vector3f& one();
    static const Vector3f& unitX();
    static const Vector3f& unitY();
    static const Vector3f& unitZ();
    bool isZero() const;
    bool isOne() const;
    static float angle(const Vector3f &v1, const Vector3f& v2);
    void add(const Vector3f &v);
    static void add(const Vector3f& v1, const Vector3f &v2, Vector3f *dst);
    void clamp(const Vector3f &min, const Vector3f &max);
    static void clamp(const Vector3f &v, const Vector3f &min, const Vector3f &max, Vector3f *dst);
    void cross(const Vector3f &v);
    static void cross(const Vector3f &v1, const Vector3f &v2, Vector3f *dst);
    float distance(const Vector3f &v) const;
    float distanceSquared(const Vector3f &v) const;
    float dot(const Vector3f &v) const;
    static float dot(const Vector3f &v1, const Vector3f &v2);
    float length() const;
    float lengthSquared() const;
    void negate();
    Vector3f& Normalize();
    void Normalize(Vector3f *dst) const;
    void scale(float scalar);
    void set(float x, float y, float z);
    void set(const float* array);
    void set(const Vector3f &v);
    void set(const Vector3f &p1, const Vector3f &p2);
    void subtract(const Vector3f &v);
    static void subtract(const Vector3f &v1, const Vector3f &v2, Vector3f *dst);
    inline const Vector3f operator+(const Vector3f &v) const;
    inline Vector3f& operator+=(const Vector3f &v);
    inline const Vector3f operator-(const Vector3f &v) const;
    inline Vector3f& operator-=(const Vector3f &v);
    inline const Vector3f operator-() const;
    inline const Vector3f operator*(float x) const;
    inline const Vector3f operator*=(float x);
    inline const Vector3f operator/(float x) const;
    inline bool operator<(const Vector3f &v) const;
    inline bool operator==(const Vector3f &v) const;
    inline bool operator!=(const Vector3f &v) const;
};

inline const Vector3f operator*(float x, const Vector3f &v);

inline const Vector3f Vector3f::operator+(const Vector3f &v) const {
    Vector3f result(*this);
    result.add(v);
    return result;
}

inline Vector3f& Vector3f::operator+=(const Vector3f &v) {
    add(v);
    return *this;
}

inline const Vector3f Vector3f::operator-(const Vector3f &v) const {
    Vector3f result(*this);
    result.subtract(v);
    return result;
}

inline Vector3f& Vector3f::operator-=(const Vector3f &v) {
    subtract(v);
    return *this;
}

inline const Vector3f Vector3f::operator-() const {
    Vector3f result(*this);
    result.negate();
    return result;
}

inline const Vector3f Vector3f::operator*(float x) const {
    Vector3f result(*this);
    result.scale(x);
    return result;
}

inline const Vector3f Vector3f::operator*=(float x) {
    scale(x);
    return *this;
}

inline const Vector3f Vector3f::operator/(const float x) const
{
    return Vector3f(this->x / x, this->y / x, this->z / x);
}

inline bool Vector3f::operator<(const Vector3f &v) const
{
    if (this->x == v.x)
    {
        if (this->y == v.y)
        {
            return this->z < v.z;
        }
        return this->y < v.y;
    }
    return this->x < v.x;
}

inline bool Vector3f::operator==(const Vector3f &v) const
{
    return this->x==v.x && this->y==v.y && this->z==v.z;
}

inline bool Vector3f::operator!=(const Vector3f &v) const
{
    return x!=v.x || y!=v.y || z!=v.z;
}

inline const Vector3f operator*(float x, const Vector3f &v)
{
    Vector3f result(v);
    result.scale(x);
    return result;
}

#endif /* Vector3f_hpp */
