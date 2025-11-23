#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include "../ImportSdk.hpp"

#include <memory>
#include <cmath>

class FLSDK_IMPORT Vector4
{
    public:
        float x, y, z, w;

        Vector4();
        Vector4(float v);
        Vector4(float v1, float v2, float v3, float v4);
        void zero();
        const Vector4& operator+=(const Vector4& v);
        const Vector4& operator-=(const Vector4& v);
        friend Vector4 operator+(const Vector4& v1, const Vector4& v2);
        friend Vector4 operator*(const Vector4& v, float s);
        friend Vector4 operator*(float s, const Vector4& v);
        const Vector4& operator*=(float s);
        friend float dot4(const Vector4& v1, const Vector4& v2);
};

#endif
