#include "Vector4.hpp"
Vector4::Vector4() : x(0), y(0), z(0), w(0) {}
Vector4::Vector4(const f32 v) { x = y = z = w = v; }
Vector4::Vector4(const f32 v1, const f32 v2, const f32 v3, const f32 v4)
{
    x = v1;
    y = v2;
    z = v3;
    w = v4;
}
void Vector4::zero() { memset(this, 0, sizeof(*this)); }
const Vector4& Vector4::operator+=(const Vector4& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;

    return *this;
}
const Vector4& Vector4::operator-=(const Vector4& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;

    return *this;
}
const Vector4& Vector4::operator*=(const f32 s)
{
    x *= s;
    y *= s;
    z *= s;
    w *= s;

    return *this;
}
Vector4 operator+(const Vector4& v1, const Vector4& v2) { return Vector4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w); }
Vector4 operator*(const Vector4& v, const f32 s) { return Vector4(v.x * s, v.y * s, v.z * s, v.w * s); }
Vector4 operator*(const f32 s, const Vector4& v) { return v * s; }
f32 dot4(const Vector4& v1, const Vector4& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w; }
