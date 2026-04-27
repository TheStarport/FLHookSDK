#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "../ImportSdk.hpp"

#include "Vector.hpp"

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

#define PITCH  X_AXIS
#define YAW    Y_AXIS
#define ROLL   Z_AXIS

class Quaternion; // Forward reference.

// 3x3 Matrix class.
class FLSDK_IMPORT Matrix
{
    protected:
        Matrix mul(f32 s) const;
        Vector mul(const Vector& v) const;
        Matrix mul(const Matrix& m2) const;
        Vector transpose_mul(const Vector& v) const;
        Matrix add(const Matrix& m2) const;
        Matrix subtract(const Matrix& m2) const;
        Matrix dual(const Vector& v) const; // Returns 2nd order skew-symmetric dual tensor of vector.

    public:
        static f32 pow2(f32 f); // avoids calling fabs below

        union {
                f32 d[3][3];
                Vector v[3];
        };

        Matrix();
        Matrix(const Vector& i, const Vector& j, const Vector& k);
        explicit Matrix(const Quaternion& q);
        Matrix(f32 e00, f32 e01, f32 e02, f32 e10, f32 e11, f32 e12, f32 e20, f32 e21, f32 e22);
        explicit Matrix(const PersistMatrix& src);
        Matrix get_transpose() const; // For a rotation matrix, inverse == transpose, but not for general matrices.
        Matrix get_inverse() const;
        Vector get_i() const;
        Vector get_j() const;
        Vector get_k() const;
        void set_i(const Vector& i);
        void set_j(const Vector& j);
        void set_k(const Vector& k);
        void set_orientation(f32 pitch_degrees, f32 roll_degrees,
                             f32 yaw_degrees); // Apply yaw, pitch, roll in order ( angles in degrees )
        void set_x_rotation(f32 angle);        // pitch
        void set_y_rotation(f32 angle);        // yaw
        void set_z_rotation(f32 angle);        // roll

        /* ---------- member functions */

        void rotate_around_i(f32 angle); // pitch
        void rotate_around_j(f32 angle); // yaw
        void rotate_around_k(f32 angle); // roll
        void x_rotate_left(f32 angle);   // pitch
        void y_rotate_left(f32 angle);   // yaw
        void z_rotate_left(f32 angle);   // roll
        void x_rotate_right(f32 angle);  // pitch
        void y_rotate_right(f32 angle);  // yaw
        void z_rotate_right(f32 angle);  // roll

        f32 det() const; // Returns determinant of matrix.
        const Matrix& set_identity(void);
        void make_orthogonal();
        const Matrix& zero(void);

        const Matrix& scale(f32 s);
        const Matrix& scale_by_reciprocal(f32 s);
        const Matrix& mul(const Matrix& m);
        void compose_rotation(unsigned axis, f32 angle); // expects degrees
        bool equal(const Matrix& m, f32 tolerance) const;

        [[nodiscard]]
        Vector euler(const bool inDegrees) const;
        [[nodiscard]]
        static Matrix from_direction(Vector vec);

        const Matrix& operator+=(const Matrix& m);
        const Matrix& operator-=(const Matrix& m);
        const Matrix& operator*=(f32 s);
        const Matrix& operator/=(f32 s);
        const Matrix& operator*=(const Matrix& m);

#ifdef _INC_MEMORY // #TODO: Why is this here?
        bool operator==(const Matrix& m) const;
        bool operator!=(const Matrix& m) const;
#endif

        // NOTE: The following two operators are NOT equivalent, as matrix multiplication is not commutative.
        //
        // mat * vec performs pre-multiplication with a column vector, and
        // vec * mat performs post-multiplication with a row vector.
        //
        // mat * vec is equivalent to mul(mat, vec),
        // while vec * mat is equivalent to transpose_mul(mat, vec).
        // These operators are provided for completeness.

        FLSDK_IMPORT friend Vector operator*(const Matrix& m, const Vector& v);
        FLSDK_IMPORT friend Vector operator*(const Vector& v, const Matrix& m);

        FLSDK_IMPORT friend Matrix operator*(const Matrix& m1, const Matrix& m2);
        FLSDK_IMPORT friend Matrix operator+(const Matrix& m1, const Matrix& m2);
        FLSDK_IMPORT friend Matrix operator-(const Matrix& m1, const Matrix& m2);
        FLSDK_IMPORT friend Matrix operator*(const Matrix& m, f32 s);
        FLSDK_IMPORT friend Matrix operator*(f32 s, const Matrix& m);
        FLSDK_IMPORT friend Matrix operator/(const Matrix& m, f32 s);
};

#endif // __MATRIX_H__
