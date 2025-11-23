/* ---------- headers */

#include "Transform.hpp"

static constexpr float MIN_DET = 1e-8f;

typedef SINGLE OASIS[3][3];

Transform::Transform() { set_identity(); }

Transform::Transform(const Vector& i, const Vector& j, const Vector& k) : Matrix(i, j, k) { translation.zero(); }

Transform::Transform(const Transform& transform) : Matrix(transform) { *this = transform; }

Transform::Transform(const Matrix& matrix)
{
    *static_cast<Matrix*>(this) = matrix;
    translation.zero();
}

Transform::Transform(const Matrix& rot, const Vector& trans)
{
    *static_cast<Matrix*>(this) = rot;
    translation = trans;
}

Transform::Transform(const Vector& trans)
{
    Matrix::set_identity();
    translation = trans;
}

Transform::Transform(bool) {}

Transform::Transform(const PersistTransform& src)
{
    d[0][0] = src.m.e00;
    d[0][1] = src.m.e01;
    d[0][2] = src.m.e02;
    d[1][0] = src.m.e10;
    d[1][1] = src.m.e11;
    d[1][2] = src.m.e12;
    d[2][0] = src.m.e20;
    d[2][1] = src.m.e21;
    d[2][2] = src.m.e22;

    translation.x = src.v.x;
    translation.y = src.v.y;
    translation.z = src.v.z;
}

void Transform::set_identity()
{
    Matrix::set_identity();
    translation.zero();
}

Transform Transform::multiply(const Transform& t) const
{
    Transform result(false);

    result.d[0][0] = d[0][0] * t.d[0][0] + d[0][1] * t.d[1][0] + d[0][2] * t.d[2][0];
    result.d[0][1] = d[0][0] * t.d[0][1] + d[0][1] * t.d[1][1] + d[0][2] * t.d[2][1];
    result.d[0][2] = d[0][0] * t.d[0][2] + d[0][1] * t.d[1][2] + d[0][2] * t.d[2][2];
    result.translation.x = d[0][0] * t.translation.x + d[0][1] * t.translation.y + d[0][2] * t.translation.z + translation.x;
    result.d[1][0] = d[1][0] * t.d[0][0] + d[1][1] * t.d[1][0] + d[1][2] * t.d[2][0];
    result.d[1][1] = d[1][0] * t.d[0][1] + d[1][1] * t.d[1][1] + d[1][2] * t.d[2][1];
    result.d[1][2] = d[1][0] * t.d[0][2] + d[1][1] * t.d[1][2] + d[1][2] * t.d[2][2];
    result.translation.y = d[1][0] * t.translation.x + d[1][1] * t.translation.y + d[1][2] * t.translation.z + translation.y;
    result.d[2][0] = d[2][0] * t.d[0][0] + d[2][1] * t.d[1][0] + d[2][2] * t.d[2][0];
    result.d[2][1] = d[2][0] * t.d[0][1] + d[2][1] * t.d[1][1] + d[2][2] * t.d[2][1];
    result.d[2][2] = d[2][0] * t.d[0][2] + d[2][1] * t.d[1][2] + d[2][2] * t.d[2][2];
    result.translation.z = d[2][0] * t.translation.x + d[2][1] * t.translation.y + d[2][2] * t.translation.z + translation.z;

    return result;
}

void Transform::compose_rotation(const unsigned axis, const SINGLE angle)
{
    translation.zero();
    Matrix::compose_rotation(axis, angle);
}

Transform Transform::get_transpose() const { return Transform(Matrix::get_transpose(), -translation); }

Transform Transform::get_inverse() const { return Transform(Matrix::get_transpose(), -(translation * *static_cast<const Matrix*>(this))); }

Transform Transform::get_general_inverse(SINGLE& w) const
{
    Transform result(false);

    const float determinant = d[0][0] * (d[1][1] * d[2][2] - d[2][1] * d[1][2]) - d[0][1] * (d[1][0] * d[2][2] - d[2][0] * d[1][2]) +
                              d[0][2] * (d[1][0] * d[2][1] - d[2][0] * d[1][1]);

    float dt;
    if (fabs(determinant) > MIN_DET)
    {
        dt = 1.0f / determinant;
    }
    else
    {
        dt = 1.0f; // this will at least give us the adjoint
    }

    result.d[0][0] = (d[1][1] * d[2][2] - d[2][1] * d[1][2]) * dt;
    result.d[0][1] = -(d[0][1] * d[2][2] - d[2][1] * d[0][2]) * dt;
    result.d[0][2] = (d[0][1] * d[1][2] - d[1][1] * d[0][2]) * dt;

    result.d[1][0] = -(d[1][0] * d[2][2] - d[2][0] * d[1][2]) * dt;
    result.d[1][1] = (d[0][0] * d[2][2] - d[2][0] * d[0][2]) * dt;
    result.d[1][2] = -(d[0][0] * d[1][2] - d[1][0] * d[0][2]) * dt;

    result.d[2][0] = (d[1][0] * d[2][1] - d[2][0] * d[1][1]) * dt;
    result.d[2][1] = -(d[0][0] * d[2][1] - d[2][0] * d[0][1]) * dt;
    result.d[2][2] = (d[0][0] * d[1][1] - d[1][0] * d[0][1]) * dt;

    result.translation.x = -(d[0][1] * d[1][2] * translation.z + d[1][1] * d[2][2] * translation.x + d[2][1] * d[0][2] * translation.y -
                             d[0][1] * d[2][2] * translation.y - d[1][1] * d[0][2] * translation.z - d[2][1] * d[1][2] * translation.x) *
                           dt;

    result.translation.y = (d[0][0] * d[1][2] * translation.z + d[1][0] * d[2][2] * translation.x + d[2][0] * d[0][2] * translation.y -
                            d[0][0] * d[2][2] * translation.y - d[1][0] * d[0][2] * translation.z - d[2][0] * d[1][2] * translation.x) *
                           dt;

    result.translation.z = -(d[0][0] * d[1][1] * translation.z + d[1][0] * d[2][1] * translation.x + d[2][0] * d[0][1] * translation.y -
                             d[0][0] * d[2][1] * translation.y - d[1][0] * d[0][1] * translation.z - d[2][0] * d[1][1] * translation.x) *
                           dt;

    w = (d[0][0] * d[1][1] * d[2][2] + d[1][0] * d[2][1] * d[0][2] + d[2][0] * d[0][1] * d[1][2] - d[2][0] * d[1][1] * d[0][2] - d[0][0] * d[2][1] * d[1][2] -
         d[1][0] * d[0][1] * d[2][2]) *
        dt;

    return result;
}

const Vector& Transform::get_position() const { return translation; }

void Transform::set_position(const SINGLE x, const SINGLE y, const SINGLE z)
{
    translation.x = x;
    translation.y = y;
    translation.z = z;
}

void Transform::set_position(const Vector& pos) { translation = pos; }

void Transform::move_position(const SINGLE dx, const SINGLE dy, const SINGLE dz)
{
    const Vector in(dx, dy, dz);

    const Vector out{
        d[0][0] * in.x + d[0][1] * in.y + d[0][2] * in.z,
        d[1][0] * in.x + d[1][1] * in.y + d[1][2] * in.z,
        d[2][0] * in.x + d[2][1] * in.y + d[2][2] * in.z,
    };

    translation += out;
}

void Transform::move_position(const Vector& delta) { move_position(delta.x, delta.y, delta.z); }

const Matrix& Transform::get_orientation() const { return *this; }

void Transform::set_orientation(const SINGLE pitch_degrees, const SINGLE roll_degrees, const SINGLE yaw_degrees)
{
    // sets orientation element of transform, leaving position
    // vector untouched
    // Apply yaw, pitch, roll in order ( angles in degrees )

    Matrix::set_orientation(pitch_degrees, roll_degrees, yaw_degrees);
}

void Transform::set_orientation(const Matrix& mat) { *this = mat; }

void Transform::set_orientation(const Quaternion& q)
{
    const Matrix m(q);
    set_orientation(m);
}

Vector Transform::rotate(const Vector& v) const
{
    const Vector result{
        d[0][0] * v.x + d[0][1] * v.y + d[0][2] * v.z,
        d[1][0] * v.x + d[1][1] * v.y + d[1][2] * v.z,
        d[2][0] * v.x + d[2][1] * v.y + d[2][2] * v.z,
    };

    return result;
}

Vector Transform::rotate_translate(const Vector& v) const { return rotate(v); }

Vector Transform::inverse_rotate(const Vector& v) const
{
    const Vector result{
        d[0][0] * v.x + d[1][0] * v.y + d[2][0] * v.z,
        d[0][1] * v.x + d[1][1] * v.y + d[2][1] * v.z,
        d[0][2] * v.x + d[1][2] * v.y + d[2][2] * v.z,
    };

    return result;
}

Vector Transform::inverse_rotate_translate(const Vector& v) const { return inverse_rotate(v); }

Transform& Transform::operator=(const Matrix& matrix)
{
    *static_cast<Matrix*>(this) = matrix;
    return *this;
}

#ifdef _INC_MEMORY
bool Transform::operator==(const Transform& t) const { return (0 == memcmp(this, &t, sizeof(*this))); }

bool Transform::operator!=(const Transform& t) const { return !(*this == t); }
#endif

bool Transform::equal(const Transform& t, const SINGLE tolerance) const { return translation.equal(t.translation, tolerance) && Matrix::equal(t, tolerance); }

const Transform& Transform::operator*=(const Transform& t)
{
    *this = multiply(t);
    return *this;
}

void Transform::rotate_about_i(SINGLE angle)
{
    OASIS temp;
    SINGLE cosine, sine;

    //	angle *= -PI_RADIANS;		// convert to radians
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

void Transform::rotate_about_j(SINGLE angle)
{
    OASIS temp;
    SINGLE cosine, sine;

    //	angle *= PI_RADIANS;		// convert to radians
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

void Transform::rotate_about_k(SINGLE angle)
{
    OASIS temp;

    //	angle *= -PI_RADIANS;		// convert to radians
    angle = -angle;
    const SINGLE cosine = cos(angle);
    const SINGLE sine = sin(angle);

    memcpy(temp, d, sizeof(d));

    d[0][0] = (cosine * temp[0][0]) + (sine * temp[0][1]);
    d[1][0] = (cosine * temp[1][0]) + (sine * temp[1][1]);
    d[2][0] = (cosine * temp[2][0]) + (sine * temp[2][1]);

    d[0][1] = (cosine * temp[0][1]) - (sine * temp[0][0]);
    d[1][1] = (cosine * temp[1][1]) - (sine * temp[1][0]);
    d[2][1] = (cosine * temp[2][1]) - (sine * temp[2][0]);
}

Vector operator*(const Transform& t, const Vector& v) { return t.rotate_translate(v); }

Vector operator*(const Vector& v, const Transform& t) { return t.inverse_rotate_translate(v); }

Transform operator*(const Transform& t1, const Transform& t2) { return t1.multiply(t2); }

Transform operator+(const Transform& t1, const Transform& t2) { return t1.add(t2); }

Transform operator-(const Transform& t1, const Transform& t2) { return t1.subtract(t2); }

Transform Transform::add(const Transform& m2) const { return { Matrix::add(*static_cast<const Matrix*>(&m2)), (translation + m2.translation) }; }
Transform Transform::subtract(const Transform& m2) const { return { Matrix::subtract(*static_cast<const Matrix*>(&m2)), (translation - m2.translation) }; }
