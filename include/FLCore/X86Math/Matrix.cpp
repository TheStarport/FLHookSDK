#include "Matrix.hpp"
#include "Quaternion.hpp"

static constexpr f32 MIN_DET = 1e-8f;

#ifndef PI
    #define PI 3.14159265358979323846f
#endif

#ifndef MUL_DEG_TO_RAD
    #define MUL_DEG_TO_RAD (PI / 180.0f)
#endif

Matrix::Matrix() : d() { set_identity(); }

Matrix::Matrix(const Vector& i, const Vector& j, const Vector& k)
{
    d[0][0] = i.x;
    d[1][0] = i.y;
    d[2][0] = i.z;

    d[0][1] = j.x;
    d[1][1] = j.y;
    d[2][1] = j.z;

    d[0][2] = k.x;
    d[1][2] = k.y;
    d[2][2] = k.z;
}

Matrix::Matrix(const Quaternion& q)
{
    const f32 s = 2.0f / (q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);

    const f32 xs = q.x * s;
    const f32 ys = q.y * s;
    const f32 zs = q.z * s;

    const f32 wx = q.w * xs;
    const f32 wy = q.w * ys;
    const f32 wz = q.w * zs;

    const f32 xx = q.x * xs;
    const f32 xy = q.x * ys;
    const f32 xz = q.x * zs;
    const f32 yy = q.y * ys;
    const f32 yz = q.y * zs;
    const f32 zz = q.z * zs;

    d[0][0] = 1.0f - (yy + zz);
    d[0][1] = xy - wz;
    d[0][2] = xz + wy;

    d[1][0] = xy + wz;
    d[1][1] = 1.0f - (xx + zz);
    d[1][2] = yz - wx;

    d[2][0] = xz - wy;
    d[2][1] = yz + wx;
    d[2][2] = 1.0f - (xx + yy);
}

Matrix::Matrix(const f32 e00, const f32 e01, const f32 e02, const f32 e10, const f32 e11, const f32 e12, const f32 e20,
               const f32 e21, const f32 e22)
{
    d[0][0] = e00;
    d[0][1] = e01;
    d[0][2] = e02;

    d[1][0] = e10;
    d[1][1] = e11;
    d[1][2] = e12;

    d[2][0] = e20;
    d[2][1] = e21;
    d[2][2] = e22;
}

Matrix::Matrix(const PersistMatrix& src)
{
    d[0][0] = src.e00;
    d[0][1] = src.e01;
    d[0][2] = src.e02;
    d[1][0] = src.e10;
    d[1][1] = src.e11;
    d[1][2] = src.e12;
    d[2][0] = src.e20;
    d[2][1] = src.e21;
    d[2][2] = src.e22;
}

f32 Matrix::det() const
{
    return (d[0][0] * d[1][1] * d[2][2] + d[0][1] * d[1][2] * d[2][0] + d[0][2] * d[1][0] * d[2][1] - d[0][0] * d[1][2] * d[2][1] -
            d[0][1] * d[1][0] * d[2][2] - d[0][2] * d[1][1] * d[2][0]);
}

const Matrix& Matrix::set_identity()
{
    d[0][0] = d[1][1] = d[2][2] = 1.0f;
    d[0][1] = d[0][2] = d[1][0] = d[1][2] = d[2][0] = d[2][1] = 0.0f;

    return *this;
}

void Matrix::make_orthogonal()
{
    Vector i = get_i();
    Vector j = get_j();
    i.fast_normalize();
    j.fast_normalize();
    Vector k = i.cross_product(j);
    k.fast_normalize();
    j = k.cross_product(i);
    j.fast_normalize();
    set_i(i);
    set_j(j);
    set_k(k);
}

void Matrix::rotate_around_i(f32 angle)
{
    f32 temp[3][3];
    f32 cosine, sine;

    angle = -angle;
    cosine = cos(angle);
    sine = sin(angle);

    memcpy(temp, d, sizeof(d));
    d[0][1] = (cosine * temp[0][1]) - (sine * temp[0][2]);
    d[1][1] = (cosine * temp[1][1]) - (sine * temp[1][2]);
    d[2][1] = (cosine * temp[2][1]) - (sine * temp[2][2]);

    d[0][2] = (cosine * temp[0][2]) + (sine * temp[0][1]);
    d[1][2] = (cosine * temp[1][2]) + (sine * temp[1][1]);
    d[2][2] = (cosine * temp[2][2]) + (sine * temp[2][1]);
}

void Matrix::rotate_around_j(f32 angle)
{
    f32 temp[3][3];
    f32 cosine, sine;

    // angle *= PI_RADIANS; // convert to radians
    cosine = cos(angle);
    sine = sin(angle);
    memcpy(temp, d, sizeof(d));

    d[0][0] = (cosine * temp[0][0]) + (sine * temp[0][2]);
    d[1][0] = (cosine * temp[1][0]) + (sine * temp[1][2]);
    d[2][0] = (cosine * temp[2][0]) + (sine * temp[2][2]);

    d[0][2] = (cosine * temp[0][2]) - (sine * temp[0][0]);
    d[1][2] = (cosine * temp[1][2]) - (sine * temp[1][0]);
    d[2][2] = (cosine * temp[2][2]) - (sine * temp[2][0]);
}

void Matrix::rotate_around_k(f32 angle)
{
    f32 temp[3][3];
    f32 cosine, sine;

    // angle *= -PI_RADIANS; // convert to radians
    angle = -angle;
    cosine = cos(angle);
    sine = sin(angle);

    memcpy(temp, d, sizeof(d));

    d[0][0] = (cosine * temp[0][0]) + (sine * temp[0][1]);
    d[1][0] = (cosine * temp[1][0]) + (sine * temp[1][1]);
    d[2][0] = (cosine * temp[2][0]) + (sine * temp[2][1]);

    d[0][1] = (cosine * temp[0][1]) - (sine * temp[0][0]);
    d[1][1] = (cosine * temp[1][1]) - (sine * temp[1][0]);
    d[2][1] = (cosine * temp[2][1]) - (sine * temp[2][0]);
}

const Matrix& Matrix::zero()
{
    memset(d, 0, sizeof(f32) * 9);
    return *this;
}

Matrix Matrix::get_transpose() const { return Matrix(d[0][0], d[1][0], d[2][0], d[0][1], d[1][1], d[2][1], d[0][2], d[1][2], d[2][2]); }

Matrix Matrix::get_inverse() const
{
    Matrix result;

    const f32 determinant = det();

    if (fabs(determinant) > MIN_DET)
    {
        const f32 dt = 1.0f / determinant; //compiler should use fld1 instruction (but doesn't)

        result.d[0][0] = (d[1][1] * d[2][2] - d[1][2] * d[2][1]) * dt;
        result.d[1][0] = -(d[1][0] * d[2][2] - d[1][2] * d[2][0]) * dt;
        result.d[2][0] = (d[1][0] * d[2][1] - d[1][1] * d[2][0]) * dt;
        result.d[0][1] = -(d[0][1] * d[2][2] - d[0][2] * d[2][1]) * dt;
        result.d[1][1] = (d[0][0] * d[2][2] - d[0][2] * d[2][0]) * dt;
        result.d[2][1] = -(d[0][0] * d[2][1] - d[0][1] * d[2][0]) * dt;
        result.d[0][2] = (d[0][1] * d[1][2] - d[0][2] * d[1][1]) * dt;
        result.d[1][2] = -(d[0][0] * d[1][2] - d[0][2] * d[1][0]) * dt;
        result.d[2][2] = (d[0][0] * d[1][1] - d[0][1] * d[1][0]) * dt;
    }
    else
    {
        // this is the adjoint which can still be usefull
        result.d[0][0] = (d[1][1] * d[2][2] - d[1][2] * d[2][1]);
        result.d[1][0] = -(d[1][0] * d[2][2] - d[1][2] * d[2][0]);
        result.d[2][0] = (d[1][0] * d[2][1] - d[1][1] * d[2][0]);
        result.d[0][1] = -(d[0][1] * d[2][2] - d[0][2] * d[2][1]);
        result.d[1][1] = (d[0][0] * d[2][2] - d[0][2] * d[2][0]);
        result.d[2][1] = -(d[0][0] * d[2][1] - d[0][1] * d[2][0]);
        result.d[0][2] = (d[0][1] * d[1][2] - d[0][2] * d[1][1]);
        result.d[1][2] = -(d[0][0] * d[1][2] - d[0][2] * d[1][0]);
        result.d[2][2] = (d[0][0] * d[1][1] - d[0][1] * d[1][0]);
    }

    return result;
}

const Matrix& Matrix::scale(const f32 s)
{
    d[0][0] = d[0][0] * s;
    d[0][1] = d[0][1] * s;
    d[0][2] = d[0][2] * s;
    d[1][0] = d[1][0] * s;
    d[1][1] = d[1][1] * s;
    d[1][2] = d[1][2] * s;
    d[2][0] = d[2][0] * s;
    d[2][1] = d[2][1] * s;
    d[2][2] = d[2][2] * s;

    return *this;
}

const Matrix& Matrix::scale_by_reciprocal(const f32 s) { return scale(1.0f / s); }

const Matrix& Matrix::mul(const Matrix& m)
{
    Matrix result;

    for (int i = 0; i < 3; i++)
    {
        result.d[i][0] = d[i][0] * m.d[0][0] + d[i][1] * m.d[1][0] + d[i][2] * m.d[2][0];
        result.d[i][1] = d[i][0] * m.d[0][1] + d[i][1] * m.d[1][1] + d[i][2] * m.d[2][1];
        result.d[i][2] = d[i][0] * m.d[0][2] + d[i][1] * m.d[1][2] + d[i][2] * m.d[2][2];
    }

    *this = result;
    return *this;
}

const Matrix& Matrix::operator+=(const Matrix& m)
{
    d[0][0] += m.d[0][0];
    d[0][1] += m.d[0][1];
    d[0][2] += m.d[0][2];

    d[1][0] += m.d[1][0];
    d[1][1] += m.d[1][1];
    d[1][2] += m.d[1][2];

    d[2][0] += m.d[2][0];
    d[2][1] += m.d[2][1];
    d[2][2] += m.d[2][2];

    return *this;
}

const Matrix& Matrix::operator-=(const Matrix& m)
{
    d[0][0] -= m.d[0][0];
    d[0][1] -= m.d[0][1];
    d[0][2] -= m.d[0][2];

    d[1][0] -= m.d[1][0];
    d[1][1] -= m.d[1][1];
    d[1][2] -= m.d[1][2];

    d[2][0] -= m.d[2][0];
    d[2][1] -= m.d[2][1];
    d[2][2] -= m.d[2][2];

    return *this;
}

const Matrix& Matrix::operator*=(const f32 s) { return scale(s); }

const Matrix& Matrix::operator/=(const f32 s) { return scale_by_reciprocal(s); }

const Matrix& Matrix::operator*=(const Matrix& m) { return mul(m); }

#ifdef _INC_MEMORY
bool Matrix::operator==(const Matrix& m) const { return (0 == memcmp(this, &m, sizeof(*this))); }

bool Matrix::operator!=(const Matrix& m) const { return !(*this == m); }
#endif

f32 Matrix::pow2(const f32 f)
{
    // avoids calling fabs below
    return f * f;
}

bool Matrix::equal(const Matrix& m, const f32 tolerance) const
{
    const f32 tolerance_sq = tolerance * tolerance;
    return ((pow2(d[0][0] - d[0][0]) <= tolerance_sq) && (pow2(d[0][1] - d[0][1]) <= tolerance_sq) &&
            (pow2(d[0][2] - d[0][2]) <= tolerance_sq) && (pow2(d[1][0] - d[1][0]) <= tolerance_sq) &&
            (pow2(d[1][1] - d[1][1]) <= tolerance_sq) && (pow2(d[1][2] - d[1][2]) <= tolerance_sq) &&
            (pow2(d[2][0] - d[2][0]) <= tolerance_sq) && (pow2(d[2][1] - d[2][1]) <= tolerance_sq) &&
            (pow2(d[2][2] - d[2][2]) <= tolerance_sq));
}

Vector Matrix::euler(const bool inDegrees) const
{
    Vector vec;
    f32 h = (f32)_hypot(d[0][0], d[1][0]);
    if (h > 1 / 524288.0f)
    {
        vec.x = atan2f(d[2][1], d[2][2]);
        vec.y = atan2f(-d[2][0], h);
        vec.z = atan2f(d[1][0], d[0][0]);
    }
    else
    {
        vec.x = atan2f(-d[1][2], d[1][1]);
        vec.y = atan2f(-d[2][0], h);
        vec.z = 0;
    }

    if (inDegrees)
    {
        constexpr f32 mod = 180.f / PI;
        vec *= mod;
    }
    return vec;
}

Matrix Matrix::from_direction(Vector vec)
{
    vec.x *= -1.f;
    vec.z *= -1.f;

    Matrix mat;
    mat.d[0][1] = vec.x;
    mat.d[1][1] = vec.y;
    mat.d[2][1] = vec.z;

    mat.d[0][2] = vec.z;
    mat.d[1][2] = vec.x;
    mat.d[2][2] = vec.y;

    mat.d[0][0] = vec.y;
    mat.d[1][0] = vec.z;
    mat.d[2][0] = vec.x;

    return mat;
}

Vector Matrix::get_i() const { return Vector(d[0][0], d[1][0], d[2][0]); }

Vector Matrix::get_j() const { return Vector(d[0][1], d[1][1], d[2][1]); }

Vector Matrix::get_k() const { return Vector(d[0][2], d[1][2], d[2][2]); }

void Matrix::set_i(const Vector& i)
{
    d[0][0] = i.x;
    d[1][0] = i.y;
    d[2][0] = i.z;
}

void Matrix::set_j(const Vector& j)
{
    d[0][1] = j.x;
    d[1][1] = j.y;
    d[2][1] = j.z;
}

void Matrix::set_k(const Vector& k)
{
    d[0][2] = k.x;
    d[1][2] = k.y;
    d[2][2] = k.z;
}

void Matrix::compose_rotation(const unsigned axis, const f32 angle)
{
    switch (axis)
    {
        case PITCH: set_x_rotation(angle * MUL_DEG_TO_RAD); break;

        case YAW: set_y_rotation(angle * MUL_DEG_TO_RAD); break;

        case ROLL: set_z_rotation(angle * MUL_DEG_TO_RAD); break;
    }
}

void Matrix::set_orientation(const f32 pitch_degrees, const f32 roll_degrees, const f32 yaw_degrees)
{
    // Apply yaw, pitch, roll in order ( angles in degrees )
    set_y_rotation(yaw_degrees * MUL_DEG_TO_RAD);
    x_rotate_left(pitch_degrees * MUL_DEG_TO_RAD);
    z_rotate_left(roll_degrees * MUL_DEG_TO_RAD);
}

void Matrix::set_x_rotation(const f32 angle) // pitch
{
    const f32 _cos = cos(angle);
    const f32 _sin = sin(angle);

    d[0][0] = 1.0f;
    d[0][1] = 0.0f;
    d[0][2] = 0.0f;
    d[1][0] = 0.0f;
    d[1][1] = _cos;
    d[1][2] = -_sin;
    d[2][0] = 0.0f;
    d[2][1] = _sin;
    d[2][2] = _cos;
}

void Matrix::set_y_rotation(const f32 angle) // yaw
{
    const f32 _cos = cos(angle);
    const f32 _sin = sin(angle);

    d[0][0] = _cos;
    d[0][1] = 0.0f;
    d[0][2] = _sin;
    d[1][0] = 0.0f;
    d[1][1] = 1.0f;
    d[1][2] = 0.0f;
    d[2][0] = -_sin;
    d[2][1] = 0.0f;
    d[2][2] = _cos;
}

void Matrix::set_z_rotation(const f32 angle) // roll
{
    const f32 _cos = cos(angle);
    const f32 _sin = sin(angle);

    d[0][0] = _cos;
    d[0][1] = -_sin;
    d[0][2] = 0.0f;
    d[1][0] = _sin;
    d[1][1] = _cos;
    d[1][2] = 0.0f;
    d[2][0] = 0.0f;
    d[2][1] = 0.0f;
    d[2][2] = 1.0f;
}

void Matrix::x_rotate_left(const f32 angle) // pitch
{
    const f32 _cos = cos(angle);
    const f32 _sin = sin(angle);

    for (int i = 0; i < 3; i++)
    {
        const f32 tmp = d[1][i];
        d[1][i] = tmp * _cos - d[2][i] * _sin;
        d[2][i] = tmp * _sin + d[2][i] * _cos;
    }
}

void Matrix::y_rotate_left(const f32 angle) // yaw
{
    const f32 _cos = cos(angle);
    const f32 _sin = sin(angle);

    for (int i = 0; i < 3; i++)
    {
        const f32 tmp = d[0][i];
        d[0][i] = tmp * _cos + d[2][i] * _sin;
        d[2][i] = d[2][i] * _cos - tmp * _sin;
    }
}

void Matrix::z_rotate_left(const f32 angle) // roll
{
    const f32 _cos = cos(angle);
    const f32 _sin = sin(angle);

    for (int i = 0; i < 3; i++)
    {
        const f32 tmp = d[0][i];
        d[0][i] = tmp * _cos - d[1][i] * _sin;
        d[1][i] = tmp * _sin + d[1][i] * _cos;
    }
}

void Matrix::x_rotate_right(const f32 angle) // pitch
{
    const f32 _cos = cos(angle);
    const f32 _sin = sin(angle);

    for (auto& i : d)
    {
        const f32 tmp = i[1];
        i[1] = i[2] * _sin + tmp * _cos;
        i[2] = i[2] * _cos - tmp * _sin;
    }
}

void Matrix::y_rotate_right(const f32 angle) // yaw
{
    const auto _cos = cos(angle);
    const auto _sin = sin(angle);

    for (auto& i : d)
    {
        const f32 tmp = i[0];
        i[0] = tmp * _cos - i[2] * _sin;
        i[2] = tmp * _sin + i[2] * _cos;
    }
}

void Matrix::z_rotate_right(const f32 angle) // roll
{
    const auto _cos = cos(angle);
    const auto _sin = sin(angle);

    for (auto& i : d)
    {
        const f32 tmp = i[0];
        i[0] = i[1] * _sin + tmp * _cos;
        i[1] = i[1] * _cos - tmp * _sin;
    }
}

Matrix operator+(const Matrix& m1, const Matrix& m2) { return m1.add(m2); }
Matrix operator-(const Matrix& m1, const Matrix& m2) { return m1.subtract(m2); }
Matrix operator*(const Matrix& m, const f32 s) { return m.mul(s); }
Matrix operator*(const f32 s, const Matrix& m) { return m.mul(s); }
Matrix operator/(const Matrix& m, const f32 s) { return m.mul(1.0f / s); }
Vector operator*(const Matrix& m, const Vector& v) { return m.mul(v); }
Vector operator*(const Vector& v, const Matrix& m) { return m.transpose_mul(v); }
Matrix operator*(const Matrix& m1, const Matrix& m2) { return m1.mul(m2); }

Matrix Matrix::mul(const f32 s) const
{
    Matrix result = *this;
    result.scale(s);
    return result;
}

Vector Matrix::mul(const Vector& v) const
{
    const Vector result{
        d[0][0] * v.x + d[0][1] * v.y + d[0][2] * v.z,
        d[1][0] * v.x + d[1][1] * v.y + d[1][2] * v.z,
        d[2][0] * v.x + d[2][1] * v.y + d[2][2] * v.z,
    };

    return result;
}

Vector Matrix::transpose_mul(const Vector& v) const
{
    const Vector result{
        d[0][0] * v.x + d[1][0] * v.y + d[2][0] * v.z,
        d[0][1] * v.x + d[1][1] * v.y + d[2][1] * v.z,
        d[0][2] * v.x + d[1][2] * v.y + d[2][2] * v.z,
    };

    return result;
}

Matrix Matrix::mul(const Matrix& m2) const
{
    Matrix result = *this;
    result.mul(m2);
    return result;
}

Matrix Matrix::add(const Matrix& m2) const
{
    return Matrix(d[0][0] + m2.d[0][0],
                  d[0][1] + m2.d[0][1],
                  d[0][2] + m2.d[0][2],
                  d[1][0] + m2.d[1][0],
                  d[1][1] + m2.d[1][1],
                  d[1][2] + m2.d[1][2],
                  d[2][0] + m2.d[2][0],
                  d[2][1] + m2.d[2][1],
                  d[2][2] + m2.d[2][2]);
}

Matrix Matrix::subtract(const Matrix& m2) const
{
    return Matrix(d[0][0] - m2.d[0][0],
                  d[0][1] - m2.d[0][1],
                  d[0][2] - m2.d[0][2],
                  d[1][0] - m2.d[1][0],
                  d[1][1] - m2.d[1][1],
                  d[1][2] - m2.d[1][2],
                  d[2][0] - m2.d[2][0],
                  d[2][1] - m2.d[2][1],
                  d[2][2] - m2.d[2][2]);
}

Matrix Matrix::dual(const Vector& v) const { return Matrix(0.0f, -v.z, v.y, v.z, 0.0f, -v.x, -v.y, v.x, 0.0f); }
