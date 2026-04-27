#include "Vector.hpp"

Vector::Vector()
{
    x = 0.f;
    y = 0.f;
    z = 0.f;
}

Vector::Vector(const f32 xx, const f32 yy, const f32 zz)
{
    x = xx;
    y = yy;
    z = zz;
    NAN_CHECK();
}
Vector::Vector(const PersistVector& src)
{
    x = src.x;
    y = src.y;
    z = src.z;
    NAN_CHECK();
}
void Vector::set(const f32 xx, const f32 yy, const f32 zz)
{
    x = xx;
    y = yy;
    z = zz;
    NAN_CHECK();
}
void Vector::zero() { x = y = z = 0.0f; }
f32 Vector::magnitude_squared() const { return x * x + y * y + z * z; }
f32 Vector::fast_magnitude() const { return sqrt(x * x + y * y + z * z); }
f32 Vector::magnitude() const { return sqrt(x * x + y * y + z * z); }
const Vector& Vector::fast_normalize()
{
    const f32 inv_m = 1.0f / sqrt(x * x + y * y + z * z);
    x *= inv_m;
    y *= inv_m;
    z *= inv_m;
    NAN_CHECK();
    return *this;
}
const Vector& Vector::normalize()
{
    const f32 inv_m = 1.0F / magnitude(); // 1*DIV+3*MUL is faster than 3*DIV
    x *= inv_m;
    y *= inv_m;
    z *= inv_m;
    NAN_CHECK();
    return *this;
}
void Vector::resize(const f32 s)
{
    const f32 inv = s / magnitude(); // 1*DIV+3*MUL is faster than 3*DIV
    x *= inv;
    y *= inv;
    z *= inv;
    NAN_CHECK();
}
const Vector& Vector::add(const Vector& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    NAN_CHECK();
    return *this;
}
const Vector& Vector::subtract(const Vector& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    NAN_CHECK();
    return *this;
}
const Vector& Vector::add(const Vector& v1, const Vector& v2)
{
    x = v1.x + v2.x;
    y = v1.y + v2.y;
    z = v1.z + v2.z;
    NAN_CHECK();
    return *this;
}
const Vector& Vector::subtract(const Vector& v1, const Vector& v2)
{
    x = v1.x - v2.x;
    y = v1.y - v2.y;
    z = v1.z - v2.z;
    NAN_CHECK();
    return *this;
}
const Vector& Vector::scale(const f32 s)
{
    x *= s;
    y *= s;
    z *= s;
    NAN_CHECK();
    return *this;
}
const Vector& Vector::scale(const Vector& v, const f32 s)
{
    x = v.x * s;
    y = v.y * s;
    z = v.z * s;
    NAN_CHECK();
    return *this;
}
const Vector& Vector::scale_by_reciprocal(const f32 s)
{
    const f32 inv_s = 1.0F / s; // 1*DIV+3*MUL is faster than 3*DIV
    x *= inv_s;
    y *= inv_s;
    z *= inv_s;
    NAN_CHECK();
    return *this;
}
const Vector& Vector::scale_by_reciprocal(const Vector& v, const f32 s)
{
    const f32 inv_s = 1.0F / s; // 1*DIV+3*MUL is faster than 3*DIV
    x = v.x * inv_s;
    y = v.y * inv_s;
    z = v.z * inv_s;
    NAN_CHECK();
    return *this;
}

f32 Vector::distance(const Vector& v) const
{
    const Vector diff = *this - v;
    return sqrtf(diff.dot_product(diff));
}

f32 Vector::pow2(const f32 f) { return f * f; }
bool Vector::equal(const Vector& v, const f32 tolerance) const
{
    const f32 tolerance_sq = tolerance * tolerance;
    return ((pow2(x - v.x) <= tolerance_sq) && (pow2(y - v.y) <= tolerance_sq) && (pow2(z - v.z) <= tolerance_sq));
}
Vector Vector::operator-() const { return negative(); }
const Vector& Vector::operator+=(const Vector& v) { return add(v); }
const Vector& Vector::operator-=(const Vector& v) { return subtract(v); }
const Vector& Vector::operator*=(const f32 s) { return scale(s); }
const Vector& Vector::operator/=(const f32 s) { return scale_by_reciprocal(s); }
bool Vector::operator==(const Vector& v) const { return (x == v.x && y == v.y && z == v.z); }
f32 Vector::dot_product(const Vector& v2) const { return x * v2.x + y * v2.y + z * v2.z; }
Vector Vector::cross_product(const Vector& v2) const { return { y * v2.z - z * v2.y, z * v2.x - x * v2.z, x * v2.y - y * v2.x }; }
Vector Vector::reflection(const Vector& e) const
{
    Vector ans = *this;
    ans *= (dot_product(e) * 2.0f);
    return ans.subtract(e);
}
Vector Vector::lerp(const Vector& b, const f32 t) const
{
    Vector ans;
    ans.x = x + (b.x - x) * t;
    ans.y = y + (b.y - y) * t;
    ans.z = z + (b.z - z) * t;
    return ans;
}

Vector operator+(const Vector& v1, const Vector& v2) { return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z); }
Vector operator-(const Vector& v1, const Vector& v2) { return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z); }
Vector operator*(const Vector& v, const f32 s) { return Vector(v.x * s, v.y * s, v.z * s); }
Vector operator*(f32 s, const Vector& v) { return Vector(v.x * s, v.y * s, v.z * s); }
Vector operator/(const Vector& v, const f32 s)
{
    const f32 inv_s = 1.0F / s; // 1*DIV+3*MUL is faster than 3*DIV
    return Vector(v.x * inv_s, v.y * inv_s, v.z * inv_s);
}
