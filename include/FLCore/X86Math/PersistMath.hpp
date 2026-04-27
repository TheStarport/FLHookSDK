#ifndef PERSISTMATH_H__
#define PERSISTMATH_H__

#include "../ImportSdk.hpp"
#include "../../Typedefs.hpp"

#include <memory.h>
#include <cmath>

struct PersistVector
{
        f32 x;
        f32 y;
        f32 z;

        PersistVector(void) {}
        PersistVector(f32 a, f32 b, f32 c)
        {
            x = a;
            y = b;
            z = c;
        }

        inline const PersistVector& zero(void)
        {
            memset(this, 0, sizeof(*this));
            return *this;
        }

        inline friend PersistVector operator+(const PersistVector& v1, const PersistVector& v2) { return PersistVector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z); }

        inline friend PersistVector operator-(const PersistVector& v1, const PersistVector& v2) { return PersistVector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z); }
};

struct PersistMatrix
{
        f32 e00;
        f32 e01;
        f32 e02;
        f32 e10;
        f32 e11;
        f32 e12;
        f32 e20;
        f32 e21;
        f32 e22;

        PersistMatrix(void) {}
        PersistMatrix(f32 a1, f32 a2, f32 a3, f32 a4, f32 a5, f32 a6, f32 a7, f32 a8, f32 a9)
        {
            e00 = a1;
            e01 = a2;
            e02 = a3;
            e10 = a4;
            e11 = a5;
            e12 = a6;
            e20 = a7;
            e21 = a8;
            e22 = a9;
        }

        inline const PersistMatrix& zero(void)
        {
            memset(this, 0, sizeof(*this));
            return *this;
        }

        inline const PersistMatrix& identity(void)
        {
            e00 = e11 = e22 = 1.0f;
            e01 = e02 = e10 = e12 = e20 = e21 = 0.0f;

            return *this;
        }

        inline PersistMatrix get_transpose(void) { return PersistMatrix(e00, e10, e20, e01, e11, e21, e02, e12, e22); }

        inline friend PersistVector operator*(const PersistMatrix& m, const PersistVector& v)
        {
            return PersistVector(v.x * m.e00 + v.y * m.e01 + v.z * m.e02, v.x * m.e10 + v.y * m.e11 + v.z * m.e12, v.x * m.e20 + v.y * m.e21 + v.z * m.e22);
        }

        inline friend PersistMatrix operator*(const PersistMatrix& m1, const PersistMatrix& m2)
        {
            return PersistMatrix(m2.e00 * m1.e00 + m2.e01 * m1.e10 + m2.e02 * m1.e20,
                                 m2.e00 * m1.e01 + m2.e01 * m1.e11 + m2.e02 * m1.e21,
                                 m2.e00 * m1.e02 + m2.e01 * m1.e12 + m2.e02 * m1.e22,

                                 m2.e10 * m1.e00 + m2.e11 * m1.e10 + m2.e12 * m1.e20,
                                 m2.e10 * m1.e01 + m2.e11 * m1.e11 + m2.e12 * m1.e21,
                                 m2.e10 * m1.e02 + m2.e11 * m1.e12 + m2.e12 * m1.e22,

                                 m2.e20 * m1.e00 + m2.e21 * m1.e10 + m2.e22 * m1.e20,
                                 m2.e20 * m1.e01 + m2.e21 * m1.e11 + m2.e22 * m1.e21,
                                 m2.e20 * m1.e02 + m2.e21 * m1.e12 + m2.e22 * m1.e22);
        }

        static inline PersistMatrix rotate_x(f32 angle)
        {
            f32 cos_a = (f32)cos(angle);
            f32 sin_a = (f32)sin(angle);
            return PersistMatrix(1.0, 0.0, 0.0, 0.0, cos_a, -sin_a, 0.0, sin_a, cos_a);
        }

        static inline PersistMatrix rotate_y(f32 angle)
        {
            f32 cos_a = (f32)cos(angle);
            f32 sin_a = (f32)sin(angle);
            return PersistMatrix(cos_a, 0.0, sin_a, 0.0, 1.0, 0.0, -sin_a, 0.0, cos_a);
        }

        static inline PersistMatrix rotate_z(f32 angle)
        {
            f32 cos_a = (f32)cos(angle);
            f32 sin_a = (f32)sin(angle);
            return PersistMatrix(cos_a, -sin_a, 0.0, sin_a, cos_a, 0.0, 0.0, 0.0, 1.0);
        }
};

struct PersistTransform
{
        PersistMatrix m;
        PersistVector v;

        PersistTransform(void) {}
        PersistTransform(const PersistMatrix& m1, const PersistVector& v1)
        {
            m = m1;
            v = v1;
        }

        inline const PersistTransform& zero(void)
        {
            memset(this, 0, sizeof(*this));
            return *this;
        }

        inline const PersistTransform& identity(void)
        {
            m.identity();
            v.zero();
            return *this;
        }

        inline friend PersistTransform operator*(const PersistTransform& t1, const PersistTransform& t2)
        {
            return PersistTransform(t2.m * t1.m, (t1.m * t2.v) + t1.v);
        }

        inline friend PersistVector operator*(const PersistTransform& t, const PersistVector& v) { return PersistVector((t.m * v) + t.v); }
};

struct PersistQuaternion
{
        f32 w;
        f32 x;
        f32 y;
        f32 z;

        inline const PersistQuaternion& zero(void)
        {
            memset(this, 0, sizeof(*this));
            return *this;
        }
};

#endif
