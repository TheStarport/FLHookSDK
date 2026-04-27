#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include "../ImportSdk.hpp"
#include "../../Typedefs.hpp"

#include <memory>
#include <cmath>

class FLSDK_IMPORT Vector4
{
    public:
        f32 x, y, z, w;

        Vector4();
        Vector4(f32 v);
        Vector4(f32 v1, f32 v2, f32 v3, f32 v4);
        void zero();
        const Vector4& operator+=(const Vector4& v);
        const Vector4& operator-=(const Vector4& v);
        friend Vector4 operator+(const Vector4& v1, const Vector4& v2);
        friend Vector4 operator*(const Vector4& v, f32 s);
        friend Vector4 operator*(f32 s, const Vector4& v);
        const Vector4& operator*=(f32 s);
        friend f32 dot4(const Vector4& v1, const Vector4& v2);
};

#endif
