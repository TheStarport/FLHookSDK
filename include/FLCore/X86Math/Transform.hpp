#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "../ImportSdk.hpp"

/* ---------- headers */

#include "Matrix.hpp"

/* ---------- constants */

#ifndef PI // #TODO: Move into global math constants header
    #define PI 3.14159265358979323846f
#endif

#ifndef MUL_DEG_TO_RAD // #TODO: Move into global math constants header
    #define MUL_DEG_TO_RAD (PI / 180.0f)
#endif

/* ---------- definitions */

// 3x4 Transform class.
class FLSDK_IMPORT Transform : public Matrix
{
        Transform add(const Transform& m2) const;
        Transform subtract(const Transform& m2) const;

    public:
        /* ---------- member variables */

        // 4x4 matrix in [row][col] order -- 4th row is implicit { 0 0 0 1 }
        Vector translation;
        //f32 element[3][4];

        /* ---------- constructors & destructors */

        Transform(void);
        Transform(const Vector& i, const Vector& j, const Vector& k);
        Transform(const Transform& transform);
        Transform(const Matrix& matrix);
        Transform(const Matrix& rot, const Vector& trans);
        Transform(const Vector& trans);
        // #TODO Make a global NO_INITIALIZATION enum to ensure this is strict
        explicit Transform(bool); // enable construction of a Transform without initialization
        Transform(const PersistTransform& src);

        /* ---------- accessors */

        Transform get_transpose() const;
        Transform get_inverse() const;
        Transform get_general_inverse(f32& w) const; // assumes last row of 4x4 is 0 0 0 1
        const Vector& get_position() const;
        const Matrix& get_orientation() const;

        void set_identity(void);
        void set_position(const f32 x, const f32 y, const f32 z);
        void set_position(const Vector& pos);
        void set_orientation(const f32 pitch_degrees, const f32 roll_degrees, const f32 yaw_degrees); // expects degrees
        void set_orientation(const Matrix& mat);
        void set_orientation(const Quaternion& q);

        /* ---------- member functions */

        void rotate_about_i(f32 angle); // pitch
        void rotate_about_j(f32 angle); // yaw
        void rotate_about_k(f32 angle); // roll

        void move_position(const f32 dx, const f32 dy, const f32 dz);
        void move_position(const Vector& delta);

        Vector rotate(const Vector& v) const;
        Vector rotate_translate(const Vector& v) const;
        Vector inverse_rotate(const Vector& v) const;
        Vector inverse_rotate_translate(const Vector& v) const;
        Transform multiply(const Transform& t) const;
        void compose_rotation(const unsigned axis, const f32 angle); // expects degrees
        bool equal(const Transform& t, const f32 tolerance) const;

        Transform& operator=(const Matrix& matrix);
        const Transform& operator*=(const Transform& t);

#ifdef _INC_MEMORY
        bool operator==(const Transform& t) const;
        bool operator!=(const Transform& t) const;
#endif

        // NOTE: The following two operators are NOT equivalent, as matrix multiplication is not commutative.
        //
        // mat * vec performs pre-multiplication with a column vector, and
        // vec * mat performs post-multiplication with a row vector.
        //
        // mat * vec is equivalent to mul(mat, vec),
        // while vec * mat is equivalent to transpose_mul(mat, vec).
        // These operators are provided for completeness.

        friend Vector operator*(const Transform& t, const Vector& v);
        friend Vector operator*(const Vector& v, const Transform& t);
        friend Transform operator*(const Transform& t1, const Transform& t2);
        friend Transform operator+(const Transform& t1, const Transform& t2);
        friend Transform operator-(const Transform& t1, const Transform& t2);
};

#endif // __TRANSFORM_H__
