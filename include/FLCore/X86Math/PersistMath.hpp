#ifndef PERSISTMATH_H__
#define PERSISTMATH_H__

#include "../ImportSdk.hpp"

#include <memory.h>
#include <cmath>

#ifndef SINGLE
typedef float SINGLE;
#endif

struct PersistVector
{
        SINGLE x;
        SINGLE y;
        SINGLE z;

        PersistVector(void) {}
        PersistVector(SINGLE a, SINGLE b, SINGLE c)
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
        SINGLE e00;
        SINGLE e01;
        SINGLE e02;
        SINGLE e10;
        SINGLE e11;
        SINGLE e12;
        SINGLE e20;
        SINGLE e21;
        SINGLE e22;

        PersistMatrix(void) {}
        PersistMatrix(SINGLE a1, SINGLE a2, SINGLE a3, SINGLE a4, SINGLE a5, SINGLE a6, SINGLE a7, SINGLE a8, SINGLE a9)
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

        static inline PersistMatrix rotate_x(SINGLE angle)
        {
            SINGLE cos_a = (SINGLE)cos(angle);
            SINGLE sin_a = (SINGLE)sin(angle);
            return PersistMatrix(1.0, 0.0, 0.0, 0.0, cos_a, -sin_a, 0.0, sin_a, cos_a);
        }

        static inline PersistMatrix rotate_y(SINGLE angle)
        {
            SINGLE cos_a = (SINGLE)cos(angle);
            SINGLE sin_a = (SINGLE)sin(angle);
            return PersistMatrix(cos_a, 0.0, sin_a, 0.0, 1.0, 0.0, -sin_a, 0.0, cos_a);
        }

        static inline PersistMatrix rotate_z(SINGLE angle)
        {
            SINGLE cos_a = (SINGLE)cos(angle);
            SINGLE sin_a = (SINGLE)sin(angle);
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
        SINGLE w;
        SINGLE x;
        SINGLE y;
        SINGLE z;

        inline const PersistQuaternion& zero(void)
        {
            memset(this, 0, sizeof(*this));
            return *this;
        }
};

#endif
