#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "../ImportSdk.hpp"

#include <memory>
#include "Vector4.hpp"
#include "Transform.hpp"

class FLSDK_IMPORT Matrix4
{
    public:
        f32 d[4][4];

        Matrix4();
        explicit Matrix4(bool);
        explicit Matrix4(f32 v);
        Matrix4(const Matrix4& m);

        Matrix4(f32 v1, f32 v2, f32 v3, f32 v4, f32 v5, f32 v6, f32 v7, f32 v8, f32 v9, f32 v10, f32 v11, f32 v12,
                f32 v13, f32 v14, f32 v15, f32 v16);

        explicit Matrix4(const Transform& src);
        explicit Matrix4(const Matrix& src);

        const Matrix4& set_diagonal(f32 v);
        const Matrix4& set_identity();
        const Matrix4& zero();
        const Matrix4& set_elements(f32 v);

        const Matrix4& quadric(f32 aa, f32 bb, f32 cc, f32 dd);
        const Matrix4& quadric(Vector v, f32 dd);
        void transpose();
        Matrix4 get_transpose() const;
        bool inverse();
        Matrix4 get_adjoint() const;
        f32 det4x4() const;
        friend f32 det3x3(f32 a1, f32 a2, f32 a3, f32 b1, f32 b2, f32 b3, f32 c1, f32 c2, f32 c3);
        friend f32 det2x2(f32 a, f32 b, f32 c, f32 d);
        const Matrix4& operator+=(const Matrix4& m);
        const Matrix4& operator-=(const Matrix4& m);
        friend Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
        friend Matrix4 operator+(const Matrix4& m1, const Matrix4& m2);
        friend Matrix4 operator-(const Matrix4& m1, const Matrix4& m2);
        friend Vector4 operator*(const Matrix4& m, const Vector4& v);
        const Matrix4& operator*=(f32 s);
        friend Matrix4 operator*(f32 s, const Matrix4& m);
        friend Matrix4 operator*(const Matrix4& m, f32 s);
        f32* operator[](int i);
        const f32* operator[](int i) const;
        Transform get_transform() const;
        f32 get_norm() const;
};

#endif
