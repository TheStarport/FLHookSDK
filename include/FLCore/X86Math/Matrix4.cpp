#include "Matrix4.hpp"

Matrix4::Matrix4() : d{} {}
Matrix4::Matrix4(const bool) { set_identity(); }
Matrix4::Matrix4(const f32 v) { set_diagonal(v); }
Matrix4::Matrix4(const Matrix4& m) { *this = m; }
Matrix4::Matrix4(const f32 v1, const f32 v2, const f32 v3, const f32 v4, const f32 v5, const f32 v6, const f32 v7, const f32 v8,
                 const f32 v9, const f32 v10, const f32 v11, const f32 v12, const f32 v13, const f32 v14, const f32 v15, const f32 v16)
{
    d[0][0] = v1;
    d[0][1] = v2;
    d[0][2] = v3;
    d[0][3] = v4;
    d[1][0] = v5;
    d[1][1] = v6;
    d[1][2] = v7;
    d[1][3] = v8;
    d[2][0] = v9;
    d[2][1] = v10;
    d[2][2] = v11;
    d[2][3] = v12;
    d[3][0] = v13;
    d[3][1] = v14;
    d[3][2] = v15;
    d[3][3] = v16;
}
Matrix4::Matrix4(const Transform& src)
{
    d[0][0] = src.d[0][0];
    d[0][1] = src.d[0][1];
    d[0][2] = src.d[0][2];
    d[0][3] = src.translation.x;

    d[1][0] = src.d[1][0];
    d[1][1] = src.d[1][1];
    d[1][2] = src.d[1][2];
    d[1][3] = src.translation.y;

    d[2][0] = src.d[2][0];
    d[2][1] = src.d[2][1];
    d[2][2] = src.d[2][2];
    d[2][3] = src.translation.z;

    d[3][0] = d[3][1] = d[3][2] = 0.0f;
    d[3][3] = 1.0f;
}
Matrix4::Matrix4(const Matrix& src)
{
    d[0][0] = src.d[0][0];
    d[0][1] = src.d[0][1];
    d[0][2] = src.d[0][2];
    d[0][3] = 0.0f;

    d[1][0] = src.d[1][0];
    d[1][1] = src.d[1][1];
    d[1][2] = src.d[1][2];
    d[1][3] = 0.0f;

    d[2][0] = src.d[2][0];
    d[2][1] = src.d[2][1];
    d[2][2] = src.d[2][2];
    d[2][3] = 0.0f;

    d[3][0] = d[3][1] = d[3][2] = 0.0f;
    d[3][3] = 1.0f;
}
const Matrix4& Matrix4::set_diagonal(const f32 v)
{
    d[0][0] = d[1][1] = d[2][2] = d[3][3] = v;
    d[0][1] = d[0][2] = d[0][3] = d[1][0] = d[1][2] = d[1][3] = d[2][0] = d[2][1] = d[2][3] = d[3][0] = d[3][1] = d[3][2] = 0.0f;
    return *this;
}
const Matrix4& Matrix4::set_identity()
{
    d[0][0] = d[1][1] = d[2][2] = d[3][3] = 1.0f;
    d[0][1] = d[0][2] = d[0][3] = d[1][0] = d[1][2] = d[1][3] = d[2][0] = d[2][1] = d[2][3] = d[3][0] = d[3][1] = d[3][2] = 0.0f;
    return *this;
}
const Matrix4& Matrix4::zero()
{
    memset(this, 0, sizeof(*this));
    return *this;
}
const Matrix4& Matrix4::set_elements(const f32 v)
{
    d[0][0] = d[0][1] = d[0][2] = d[0][3] = d[1][0] = d[1][1] = d[1][2] = d[1][3] = d[2][0] = d[2][1] = d[2][2] = d[2][3] = d[3][0] = d[3][1] = d[3][2] =
        d[3][3] = v;

    return *this;
}
const Matrix4& Matrix4::quadric(const f32 aa, const f32 bb, const f32 cc, const f32 dd)
{
    d[0][0] = aa * aa;
    d[1][1] = bb * bb;
    d[2][2] = cc * cc;
    d[3][3] = dd * dd;

    d[0][1] = d[1][0] = aa * bb;
    d[0][2] = d[2][0] = aa * cc;
    d[0][3] = d[3][0] = aa * dd;

    d[1][2] = d[2][1] = bb * cc;
    d[1][3] = d[3][1] = bb * dd;

    d[2][3] = d[3][2] = cc * dd;

    return *this;
}
const Matrix4& Matrix4::quadric(const Vector v, const f32 dd) { return quadric(v.x, v.y, v.z, dd); }
void Matrix4::transpose()
{

    f32 tmp = d[0][1];
    d[0][1] = d[1][0];
    d[1][0] = tmp;

    tmp = d[0][2];
    d[0][2] = d[2][0];
    d[2][0] = tmp;

    tmp = d[0][3];
    d[0][3] = d[3][0];
    d[3][0] = tmp;

    tmp = d[1][2];
    d[1][2] = d[2][1];
    d[2][1] = tmp;

    tmp = d[1][3];
    d[1][3] = d[3][1];
    d[3][1] = tmp;

    tmp = d[2][3];
    d[2][3] = d[3][2];
    d[3][2] = tmp;
}
Matrix4 Matrix4::get_transpose() const
{
    return Matrix4(
        d[0][0], d[1][0], d[2][0], d[3][0], d[0][1], d[1][1], d[2][1], d[3][1], d[0][2], d[1][2], d[2][2], d[3][2], d[0][3], d[1][3], d[2][3], d[3][3]);
}
const Matrix4& Matrix4::operator+=(const Matrix4& m)
{

    d[0][0] += m.d[0][0];
    d[0][1] += m.d[0][1];
    d[0][2] += m.d[0][2];
    d[0][3] += m.d[0][3];
    d[1][0] += m.d[1][0];
    d[1][1] += m.d[1][1];
    d[1][2] += m.d[1][2];
    d[1][3] += m.d[1][3];
    d[2][0] += m.d[2][0];
    d[2][1] += m.d[2][1];
    d[2][2] += m.d[2][2];
    d[2][3] += m.d[2][3];
    d[3][0] += m.d[3][0];
    d[3][1] += m.d[3][1];
    d[3][2] += m.d[3][2];
    d[3][3] += m.d[3][3];

    return *this;
}
const Matrix4& Matrix4::operator-=(const Matrix4& m)
{
    d[0][0] -= m.d[0][0];
    d[0][1] -= m.d[0][1];
    d[0][2] -= m.d[0][2];
    d[0][3] -= m.d[0][3];
    d[1][0] -= m.d[1][0];
    d[1][1] -= m.d[1][1];
    d[1][2] -= m.d[1][2];
    d[1][3] -= m.d[1][3];
    d[2][0] -= m.d[2][0];
    d[2][1] -= m.d[2][1];
    d[2][2] -= m.d[2][2];
    d[2][3] -= m.d[2][3];
    d[3][0] -= m.d[3][0];
    d[3][1] -= m.d[3][1];
    d[3][2] -= m.d[3][2];
    d[3][3] -= m.d[3][3];

    return *this;
}
const Matrix4& Matrix4::operator*=(const f32 s)
{
    d[0][0] *= s;
    d[0][1] *= s;
    d[0][2] *= s;
    d[0][3] *= s;
    d[1][0] *= s;
    d[1][1] *= s;
    d[1][2] *= s;
    d[1][3] *= s;
    d[2][0] *= s;
    d[2][1] *= s;
    d[2][2] *= s;
    d[2][3] *= s;
    d[3][0] *= s;
    d[3][1] *= s;
    d[3][2] *= s;
    d[3][3] *= s;

    return *this;
}
f32* Matrix4::operator[](const int i) { return d[i]; }
const f32* Matrix4::operator[](const int i) const { return d[i]; }
Transform Matrix4::get_transform() const
{
    Transform result(false);

    result.d[0][0] = d[0][0];
    result.d[0][1] = d[0][1];
    result.d[0][2] = d[0][2];
    result.translation.x = d[0][3];

    result.d[1][0] = d[1][0];
    result.d[1][1] = d[1][1];
    result.d[1][2] = d[1][2];
    result.translation.y = d[1][3];

    result.d[2][0] = d[2][0];
    result.d[2][1] = d[2][1];
    result.d[2][2] = d[2][2];
    result.translation.z = d[2][3];

    return result;
}
f32 Matrix4::get_norm() const
{
    return (d[0][0] * d[0][0] + d[0][1] * d[0][1] + d[0][2] * d[0][2] + d[0][3] * d[0][3] + d[1][0] * d[1][0] + d[1][1] * d[1][1] + d[1][2] * d[1][2] +
            d[1][3] * d[1][3] + d[2][0] * d[2][0] + d[2][1] * d[2][1] + d[2][2] * d[2][2] + d[2][3] * d[2][3] + d[3][0] * d[3][0] + d[3][1] * d[3][1] +
            d[3][2] * d[3][2] + d[3][3] * d[3][3]);
}
f32 det2x2(const f32 a, const f32 b, const f32 c, const f32 d) { return (a * d - b * c); }
Matrix4 operator*(const Matrix4& m1, const Matrix4& m2)
{
    return Matrix4(m1.d[0][0] * m2.d[0][0] + m1.d[0][1] * m2.d[1][0] + m1.d[0][2] * m2.d[2][0] + m1.d[0][3] * m2.d[3][0],
                   m1.d[0][0] * m2.d[0][1] + m1.d[0][1] * m2.d[1][1] + m1.d[0][2] * m2.d[2][1] + m1.d[0][3] * m2.d[3][1],
                   m1.d[0][0] * m2.d[0][2] + m1.d[0][1] * m2.d[1][2] + m1.d[0][2] * m2.d[2][2] + m1.d[0][3] * m2.d[3][2],
                   m1.d[0][0] * m2.d[0][3] + m1.d[0][1] * m2.d[1][3] + m1.d[0][2] * m2.d[2][3] + m1.d[0][3] * m2.d[3][3],

                   m1.d[1][0] * m2.d[0][0] + m1.d[1][1] * m2.d[1][0] + m1.d[1][2] * m2.d[2][0] + m1.d[1][3] * m2.d[3][0],
                   m1.d[1][0] * m2.d[0][1] + m1.d[1][1] * m2.d[1][1] + m1.d[1][2] * m2.d[2][1] + m1.d[1][3] * m2.d[3][1],
                   m1.d[1][0] * m2.d[0][2] + m1.d[1][1] * m2.d[1][2] + m1.d[1][2] * m2.d[2][2] + m1.d[1][3] * m2.d[3][2],
                   m1.d[1][0] * m2.d[0][3] + m1.d[1][1] * m2.d[1][3] + m1.d[1][2] * m2.d[2][3] + m1.d[1][3] * m2.d[3][3],

                   m1.d[2][0] * m2.d[0][0] + m1.d[2][1] * m2.d[1][0] + m1.d[2][2] * m2.d[2][0] + m1.d[2][3] * m2.d[3][0],
                   m1.d[2][0] * m2.d[0][1] + m1.d[2][1] * m2.d[1][1] + m1.d[2][2] * m2.d[2][1] + m1.d[2][3] * m2.d[3][1],
                   m1.d[2][0] * m2.d[0][2] + m1.d[2][1] * m2.d[1][2] + m1.d[2][2] * m2.d[2][2] + m1.d[2][3] * m2.d[3][2],
                   m1.d[2][0] * m2.d[0][3] + m1.d[2][1] * m2.d[1][3] + m1.d[2][2] * m2.d[2][3] + m1.d[2][3] * m2.d[3][3],

                   m1.d[3][0] * m2.d[0][0] + m1.d[3][1] * m2.d[1][0] + m1.d[3][2] * m2.d[2][0] + m1.d[3][3] * m2.d[3][0],
                   m1.d[3][0] * m2.d[0][1] + m1.d[3][1] * m2.d[1][1] + m1.d[3][2] * m2.d[2][1] + m1.d[3][3] * m2.d[3][1],
                   m1.d[3][0] * m2.d[0][2] + m1.d[3][1] * m2.d[1][2] + m1.d[3][2] * m2.d[2][2] + m1.d[3][3] * m2.d[3][2],
                   m1.d[3][0] * m2.d[0][3] + m1.d[3][1] * m2.d[1][3] + m1.d[3][2] * m2.d[2][3] + m1.d[3][3] * m2.d[3][3]);
}
Matrix4 operator+(const Matrix4& m1, const Matrix4& m2)
{
    return Matrix4(m1.d[0][0] + m2.d[0][0],
                   m1.d[0][1] + m2.d[0][1],
                   m1.d[0][2] + m2.d[0][2],
                   m1.d[0][3] + m2.d[0][3],
                   m1.d[1][0] + m2.d[1][0],
                   m1.d[1][1] + m2.d[1][1],
                   m1.d[1][2] + m2.d[1][2],
                   m1.d[1][3] + m2.d[1][3],
                   m1.d[2][0] + m2.d[2][0],
                   m1.d[2][1] + m2.d[2][1],
                   m1.d[2][2] + m2.d[2][2],
                   m1.d[2][3] + m2.d[2][3],
                   m1.d[3][0] + m2.d[3][0],
                   m1.d[3][1] + m2.d[3][1],
                   m1.d[3][2] + m2.d[3][2],
                   m1.d[3][3] + m2.d[3][3]);
}
Matrix4 operator-(const Matrix4& m1, const Matrix4& m2)
{
    return Matrix4(m1.d[0][0] - m2.d[0][0],
                   m1.d[0][1] - m2.d[0][1],
                   m1.d[0][2] - m2.d[0][2],
                   m1.d[0][3] - m2.d[0][3],
                   m1.d[1][0] - m2.d[1][0],
                   m1.d[1][1] - m2.d[1][1],
                   m1.d[1][2] - m2.d[1][2],
                   m1.d[1][3] - m2.d[1][3],
                   m1.d[2][0] - m2.d[2][0],
                   m1.d[2][1] - m2.d[2][1],
                   m1.d[2][2] - m2.d[2][2],
                   m1.d[2][3] - m2.d[2][3],
                   m1.d[3][0] - m2.d[3][0],
                   m1.d[3][1] - m2.d[3][1],
                   m1.d[3][2] - m2.d[3][2],
                   m1.d[3][3] - m2.d[3][3]);
}
Vector4 operator*(const Matrix4& m, const Vector4& v)
{
    return Vector4(v.x * m.d[0][0] + v.y * m.d[0][1] + v.z * m.d[0][2] + v.w * m.d[0][3],
                   v.x * m.d[1][0] + v.y * m.d[1][1] + v.z * m.d[1][2] + v.w * m.d[1][3],
                   v.x * m.d[2][0] + v.y * m.d[2][1] + v.z * m.d[2][2] + v.w * m.d[2][3],
                   v.x * m.d[3][0] + v.y * m.d[3][1] + v.z * m.d[3][2] + v.w * m.d[3][3]);
}
Matrix4 operator*(const f32 s, const Matrix4& m)
{
    return Matrix4(s * m.d[0][0],
                   s * m.d[0][1],
                   s * m.d[0][2],
                   s * m.d[0][3],
                   s * m.d[1][0],
                   s * m.d[1][1],
                   s * m.d[1][2],
                   s * m.d[1][3],
                   s * m.d[2][0],
                   s * m.d[2][1],
                   s * m.d[2][2],
                   s * m.d[2][3],
                   s * m.d[3][0],
                   s * m.d[3][1],
                   s * m.d[3][2],
                   s * m.d[3][3]);
}
Matrix4 operator*(const Matrix4& m, const f32 s) { return (s * m); }
