#ifndef VECTOR_H
#define VECTOR_H

#include "../ImportSdk.hpp"

#ifndef PERSISTMATH_H__
    #include "PersistMath.hpp"
#endif

#ifndef _INC_MATH
    #include <cmath>
#endif

#if defined(_DEBUG_VECTORS)
    #include <assert.h>
    #include <f32.h>
    #define FIND_NAN(_x) assert(!_isnan(_x))
    #define NAN_CHECK() \
        FIND_NAN(x);    \
        FIND_NAN(y);    \
        FIND_NAN(z);
#else
    #define NAN_CHECK() //
#endif

class FLSDK_IMPORT Vector
{
    public:
        f32 x, y, z;

        Vector();
        Vector(f32 xx, f32 yy, f32 zz);
        Vector(const PersistVector& src);
        void set(f32 xx, f32 yy, f32 zz);
        void zero();
        f32 magnitude_squared() const;
        f32 fast_magnitude() const;
        f32 magnitude() const;
        const Vector& fast_normalize();
        const Vector& normalize();
        void resize(f32 s);
        Vector negative() const { return Vector(-x, -y, -z); }

        const Vector& add(const Vector& v);
        const Vector& subtract(const Vector& v);
        const Vector& add(const Vector& v1, const Vector& v2);
        const Vector& subtract(const Vector& v1, const Vector& v2);
        const Vector& scale(f32 s);
        const Vector& scale(const Vector& v, f32 s);
        const Vector& scale_by_reciprocal(f32 s);
        const Vector& scale_by_reciprocal(const Vector& v, f32 s);
        f32 distance(const Vector& v) const;
        static f32 pow2(f32 f);
        bool equal(const Vector& v, f32 tolerance) const;
        f32 dot_product(const Vector& v2) const;
        Vector cross_product(const Vector& v2) const;
        Vector reflection(const Vector& e) const;
        Vector lerp(const Vector& b, f32 t) const;
        Vector operator-() const;
        const Vector& operator+=(const Vector& v);
        const Vector& operator-=(const Vector& v);
        const Vector& operator*=(f32 s);
        const Vector& operator/=(f32 s);
        bool operator==(const Vector& v) const;
        FLSDK_IMPORT friend Vector operator+(const Vector& v1, const Vector& v2);
        FLSDK_IMPORT friend Vector operator-(const Vector& v1, const Vector& v2);
        FLSDK_IMPORT friend Vector operator*(const Vector& v, f32 s);
        FLSDK_IMPORT friend Vector operator*(f32 s, const Vector& v);
        FLSDK_IMPORT friend Vector operator/(const Vector& v, f32 s);
};

#endif
