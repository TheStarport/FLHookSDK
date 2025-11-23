
#include "Quaternion.hpp"

#include "Transform.hpp"

#define Q_EPSILON 0.00001f

namespace QuaternionNS
{
    constexpr SINGLE epsilon = 1e-03f;
}

Quaternion::Quaternion() : d() {}

Quaternion::Quaternion(const Matrix& m)
{
    static constexpr int nxt[3] = { 1, 2, 0 };

    if (const float trace = m.d[0][0] + m.d[1][1] + m.d[2][2]; trace > 0.0f)
    {
        auto st = sqrtf(trace + 1.0f);
        w = st * 0.5f;
        st = 0.5f / st;

        x = (m.d[2][1] - m.d[1][2]) * st;
        y = (m.d[0][2] - m.d[2][0]) * st;
        z = (m.d[1][0] - m.d[0][1]) * st;
    }
    else
    {
        int i = 0;
        if (m.d[1][1] > m.d[0][0])
        {
            i = 1;
        }
        if (m.d[2][2] > m.d[i][i])
        {
            i = 2;
        }

        int j = nxt[i];
        int k = nxt[j];

        auto st = sqrtf(m.d[i][i] - (m.d[j][j] + m.d[k][k]) + 1.0f);

        d[i + 1] = st * 0.5f;
        st = 0.5f / st;
        w = (m.d[k][j] - m.d[j][k]) * st;
        d[j + 1] = (m.d[j][i] + m.d[i][j]) * st;
        d[k + 1] = (m.d[k][i] + m.d[i][k]) * st;
    }
}

Quaternion::Quaternion(const Vector& axis, const SINGLE angle)
{
    const SINGLE half_angle = angle / 2.0f;

#if !defined(ANONYMOUS_ILLEGAL)
    s = (SINGLE)cos(half_angle);
    v = axis;
    v.normalize();
    v *= (SINGLE)sin(half_angle);
#else
    w = (SINGLE)cos(half_angle);
    Vector V = axis;
    V.normalize();
    V *= (SINGLE)sin(half_angle);
    x = V.x;
    y = V.y;
    z = V.z;
#endif
}

// Creates a quaternion with scalar part ZERO, vector part v. NOTE that this
// is NOT in general equivalent to creating a quaternion with axis == v and
// angle == 0.
Quaternion::Quaternion(const Vector& vec)
{
#if !defined(ANONYMOUS_ILLEGAL)
    s = 0.0f;
    v = vec;
#else
    w = 0.0f;
    x = vec.x;
    y = vec.y;
    z = vec.z;
#endif
}

Quaternion::Quaternion(const SINGLE _w, const SINGLE _x, const SINGLE _y, const SINGLE _z)
{
    w = _w;
    x = _x;
    y = _y;
    z = _z;
}

Quaternion::Quaternion(const PersistQuaternion& src)
{
    w = src.w;
    x = src.x;
    y = src.y;
    z = src.z;
}

void Quaternion::set_identity(void)
{
#if !defined(ANONYMOUS_ILLEGAL)
    s = 1.0f;
    v.zero();
#else
    w = 1.0f;
    x = y = z = 0.0f;
#endif
}

Quaternion Quaternion::get_conjugate() const
{
    Quaternion result;
#if !defined(ANONYMOUS_ILLEGAL)
    result.s = s;
    result.v = -v;
#else
    result.w = w;
    result.x = -x;
    result.y = -y;
    result.z = -z;
#endif
    return result;
}

Quaternion Quaternion::get_inverse() const { return get_conjugate() * (1.0f / norm()); }

// For debugging purposes only. Quaternions representing rotations should
// always have magnitude 1.
SINGLE Quaternion::get_magnitude() const
{
#if !defined(ANONYMOUS_ILLEGAL)
    return (SINGLE)sqrt(s * s + v.magnitude_squared());
#else
    return (SINGLE)sqrt(w * w + Vector(x, y, z).magnitude_squared());
#endif
}

SINGLE Quaternion::norm() const
{
#if !defined(ANONYMOUS_ILLEGAL)
    return s * s + v.magnitude_squared();
#else
    return w * w + Vector(x, y, z).magnitude_squared();
#endif
}

Quaternion Quaternion::get_log() const
{
#if !defined(ANONYMOUS_ILLEGAL)
    if (fabs(s) < 1.0f)
    {
        const SINGLE angle = SINGLE(acos(s));
        const SINGLE sine = SINGLE(sin(angle));

        if (sine >= QuaternionNS::epsilon)
        {
            return Quaternion(v * (angle / sine));
        }
    }

    return Quaternion(v);
#else
    if (fabs(w) < 1.0f)
    {
        const SINGLE angle = acos(w);
        const SINGLE sine = sin(angle);

        if (sine >= QuaternionNS::epsilon)
        {
            return Quaternion(Vector(x, y, z) * (angle / sine));
        }
    }

    return Quaternion(Vector(x, y, z));
#endif
}

// Use on pure quaternions (s == 0)
Quaternion Quaternion::get_exp() const
{
#if !defined(ANONYMOUS_ILLEGAL)
    const SINGLE angle = v.magnitude();
    const SINGLE sine = SINGLE(sin(angle));

    if (sine >= QuaternionNS::epsilon)
    {
        const Vector exp_v = v * (sine / angle);

        return Quaternion(SINGLE(cos(angle)), exp_v.x, exp_v.y, exp_v.z);
    }
    else
    {
        return Quaternion(SINGLE(cos(angle)), v.x, v.y, v.z);
    }
#else
    const Vector _v(x, y, z);
    const SINGLE angle = _v.magnitude();
    const SINGLE sine = sin(angle);

    if (sine >= QuaternionNS::epsilon)
    {
        const Vector exp_v = _v * (sine / angle);

        return Quaternion(cos(angle), exp_v.x, exp_v.y, exp_v.z);
    }
    else
    {
        return Quaternion(cos(angle), x, y, z);
    }
#endif
}

void Quaternion::normalize(void)
{
    SINGLE m = 1.0f / get_magnitude();
#if !defined(ANONYMOUS_ILLEGAL)
    s *= m;
    v *= m;
#else
    w *= m;
    x *= m;
    y *= m;
    z *= m;
#endif
}

Quaternion Quaternion::scale(const SINGLE scalar)
{
#if !defined(ANONYMOUS_ILLEGAL)
    s *= scalar;
    v *= scalar;
#else
    w *= scalar;
    x *= scalar;
    y *= scalar;
    z *= scalar;
#endif
    return *this;
}

Quaternion Quaternion::scale_by_reciprocal(SINGLE scalar)
{
    scalar = 1.0f / scalar;
#if !defined(ANONYMOUS_ILLEGAL)
    s *= scalar;
    v *= scalar;
#else
    w *= scalar;
    x *= scalar;
    y *= scalar;
    z *= scalar;
#endif
    return *this;
}

Quaternion Quaternion::operator*=(const SINGLE scalar) { return scale(scalar); }

Quaternion Quaternion::operator/=(const SINGLE scalar) { return scale_by_reciprocal(scalar); }

Vector Quaternion::transform(const Vector& vec) const
{
    Vector result = vec * (s * s - v.dot_product(v));
    result += v * 2.0f * v.dot_product(vec);
    result += v.cross_product(vec) * s * 2.0f;
    return result;
}

//
// Compute axis & angle representation of quaternion.
//
void Quaternion::compute_axis_angle(Vector& axis, float& angle)
{
    angle = (float)(2.0f * acos(w));
    axis.x = (float)(2.0f * asin(x));
    axis.y = (float)(2.0f * asin(y));
    axis.z = (float)(2.0f * asin(z));

    const float mag = axis.magnitude();
    if (mag > 1e-5f)
    {
        axis /= mag;
    }
}

Quaternion slerp(const Quaternion& q1, const Quaternion& q2, const SINGLE t)
{
    Quaternion dst;

    Quaternion sum, dif, qs;

    sum.w = q1.w + q2.w;
    sum.x = q1.x + q2.x;
    sum.y = q1.y + q2.y;
    sum.z = q1.z + q2.z;

    dif.w = q1.w - q2.w;
    dif.x = q1.x - q2.x;
    dif.y = q1.y - q2.y;
    dif.z = q1.z - q2.z;

    float s1 = dif.w * dif.w + dif.x * dif.x + dif.y * dif.y + dif.z * dif.z;
    float s2 = sum.w * sum.w + sum.x * sum.x + sum.y * sum.y + sum.z * sum.z;

    if (s1 > s2)
    {
        qs.w = -q2.w;
        qs.x = -q2.x;
        qs.y = -q2.y;
        qs.z = -q2.z;
    }
    else
    {
        qs = q2;
    }

    float cos_omega = q1.w * qs.w + q1.x * qs.x + q1.y * qs.y + q1.z * qs.z;

    // Check for cases where rotations are nearly opposite, which causes numerical weirdness.
    if ((1.0f + cos_omega) > Q_EPSILON)
    {
        // Check for case where rotations are very close, which also causes weirdness.
        if ((1.0f - cos_omega) > Q_EPSILON)
        {
            float omega = acos(cos_omega);
            float sin_omega = sin(omega);

            s1 = sin((1.0f - t) * omega) / sin_omega;
            s2 = sin(t * omega) / sin_omega;
        }
        else
        {
            // Too close, do straight linear interpolation.
            s1 = 1.0f - t;
            s2 = t;
        }

        dst.w = s1 * q1.w + s2 * qs.w;
        dst.x = s1 * q1.x + s2 * qs.x;
        dst.y = s1 * q1.y + s2 * qs.y;
        dst.z = s1 * q1.z + s2 * qs.z;
    }
    else
    {
        dst.w = q1.z;
        dst.x = -q1.y;
        dst.y = q1.x;
        dst.z = -q1.w;

        float half_pi = PI / 2.0f;

        s1 = sin((1.0f - t) * half_pi);
        s2 = sin(t * half_pi);

        dst.x = s1 * q1.x + s2 * dst.x;
        dst.y = s1 * q1.y + s2 * dst.y;
        dst.z = s1 * q1.z + s2 * dst.z;
    }

    return dst;
}

Quaternion squad(const Quaternion& q0, const Quaternion& q1, const Quaternion& q2, const Quaternion& q3, const SINGLE t)
{
    return slerp(slerp(q0, q3, t), slerp(q1, q2, t), 2.0f * t * (1.0f - t));
}

Quaternion spline_squad(const Quaternion& q0, const Quaternion& q1, const Quaternion& q2, const Quaternion& q3, const SINGLE t)
{
    const Quaternion q1_inv(q1.get_inverse());
    const Quaternion q2_inv(q2.get_inverse());

    const Quaternion a1(q1 * (((q1_inv * q2).get_log() + (q1_inv * q0).get_log()) * (-0.25f)).get_exp());
    const Quaternion a2(q2 * (((q2_inv * q3).get_log() + (q2_inv * q1).get_log()) * (-0.25f)).get_exp());

    return squad(q1, a1, a2, q2, t);
}

Quaternion mul(const Quaternion& q1, const Quaternion& q2)
{
    Quaternion dst;

    dst.s = q1.s * q2.s - q1.v.dot_product(q2.v);
    dst.v = q1.v * q2.s + q2.v * q1.s + q1.v.cross_product(q2.v);

    return dst;
}

Quaternion operator+(const Quaternion& q1, const Quaternion& q2) { return Quaternion(q1.w + q2.w, q1.x + q2.x, q1.y + q2.y, q1.z + q2.z); }

Quaternion operator-(const Quaternion& q1, const Quaternion& q2) { return Quaternion(q1.w - q2.w, q1.x - q2.x, q1.y - q2.y, q1.z - q2.z); }

Quaternion operator*(const Quaternion& q1, const Quaternion& q2) { return mul(q1, q2); }

Quaternion scale(const Quaternion& q, const SINGLE scalar)
{
    Quaternion result;
#if !defined(ANONYMOUS_ILLEGAL)
    result.s = q.s * scalar;
    result.v = q.v * scalar;
#else
    result.w = q.w * scalar;
    result.x = q.x * scalar;
    result.y = q.y * scalar;
    result.z = q.z * scalar;
#endif
    return result;
}

Quaternion scale_by_reciprocal(const Quaternion& q, SINGLE scalar)
{
    Quaternion result;
    scalar = 1.0f / scalar;
#if !defined(ANONYMOUS_ILLEGAL)
    result.s = q.s * scalar;
    result.v = q.v * scalar;
#else
    result.w = q.w * scalar;
    result.x = q.x * scalar;
    result.y = q.y * scalar;
    result.z = q.z * scalar;
#endif
    return result;
}

Quaternion operator*(const Quaternion& q, const SINGLE scalar) { return scale(q, scalar); }

Quaternion operator/(const Quaternion& q, const SINGLE scalar) { return scale_by_reciprocal(q, scalar); }
