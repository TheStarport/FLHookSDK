#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "../ImportSdk.hpp"

#include <memory>
#include "Vector4.hpp"
#include "Transform.hpp"

class FLSDK_IMPORT Matrix4
{
    public:
        SINGLE d[4][4];

        Matrix4();
        explicit Matrix4(bool);
        explicit Matrix4(SINGLE v);
        Matrix4(const Matrix4& m);

        Matrix4(SINGLE v1, SINGLE v2, SINGLE v3, SINGLE v4, SINGLE v5, SINGLE v6, SINGLE v7, SINGLE v8, SINGLE v9, SINGLE v10, SINGLE v11, SINGLE v12,
                SINGLE v13, SINGLE v14, SINGLE v15, SINGLE v16);

        explicit Matrix4(const Transform& src);
        explicit Matrix4(const Matrix& src);

        const Matrix4& set_diagonal(SINGLE v);
        const Matrix4& set_identity();
        const Matrix4& zero();
        const Matrix4& set_elements(SINGLE v);

        const Matrix4& quadric(SINGLE aa, SINGLE bb, SINGLE cc, SINGLE dd);
        const Matrix4& quadric(Vector v, SINGLE dd);
        void transpose();
        Matrix4 get_transpose() const;
        bool inverse();
        Matrix4 get_adjoint() const;
        SINGLE det4x4() const;
        friend SINGLE det3x3(SINGLE a1, SINGLE a2, SINGLE a3, SINGLE b1, SINGLE b2, SINGLE b3, SINGLE c1, SINGLE c2, SINGLE c3);
        friend SINGLE det2x2(SINGLE a, SINGLE b, SINGLE c, SINGLE d);
        const Matrix4& operator+=(const Matrix4& m);
        const Matrix4& operator-=(const Matrix4& m);
        friend Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
        friend Matrix4 operator+(const Matrix4& m1, const Matrix4& m2);
        friend Matrix4 operator-(const Matrix4& m1, const Matrix4& m2);
        friend Vector4 operator*(const Matrix4& m, const Vector4& v);
        const Matrix4& operator*=(SINGLE s);
        friend Matrix4 operator*(SINGLE s, const Matrix4& m);
        friend Matrix4 operator*(const Matrix4& m, SINGLE s);
        SINGLE* operator[](int i);
        const SINGLE* operator[](int i) const;
        Transform get_transform() const;
        SINGLE get_norm() const;
};

#endif
