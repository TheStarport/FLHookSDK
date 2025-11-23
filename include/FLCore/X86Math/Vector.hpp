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
    #include <float.h>
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
        SINGLE x, y, z;

        Vector();
        Vector(SINGLE xx, SINGLE yy, SINGLE zz);
        Vector(const PersistVector& src);
        void set(SINGLE xx, SINGLE yy, SINGLE zz);
        void zero();
        SINGLE magnitude_squared() const;
        SINGLE fast_magnitude() const;
        SINGLE magnitude() const;
        const Vector& fast_normalize();
        const Vector& normalize();
        void resize(SINGLE s);
        Vector negative() const { return Vector(-x, -y, -z); }

        const Vector& add(const Vector& v);
        const Vector& subtract(const Vector& v);
        const Vector& add(const Vector& v1, const Vector& v2);
        const Vector& subtract(const Vector& v1, const Vector& v2);
        const Vector& scale(SINGLE s);
        const Vector& scale(const Vector& v, SINGLE s);
        const Vector& scale_by_reciprocal(SINGLE s);
        const Vector& scale_by_reciprocal(const Vector& v, SINGLE s);
        float distance(const Vector& v) const;
        static SINGLE pow2(SINGLE f);
        bool equal(const Vector& v, SINGLE tolerance) const;
        SINGLE dot_product(const Vector& v2) const;
        Vector cross_product(const Vector& v2) const;
        Vector reflection(const Vector& e) const;
        Vector lerp(const Vector& b, float t) const;
        Vector operator-() const;
        const Vector& operator+=(const Vector& v);
        const Vector& operator-=(const Vector& v);
        const Vector& operator*=(SINGLE s);
        const Vector& operator/=(SINGLE s);
        bool operator==(const Vector& v) const;
        FLSDK_IMPORT friend Vector operator+(const Vector& v1, const Vector& v2);
        FLSDK_IMPORT friend Vector operator-(const Vector& v1, const Vector& v2);
        FLSDK_IMPORT friend Vector operator*(const Vector& v, SINGLE s);
        FLSDK_IMPORT friend Vector operator*(SINGLE s, const Vector& v);
        FLSDK_IMPORT friend Vector operator/(const Vector& v, SINGLE s);
};

#endif
