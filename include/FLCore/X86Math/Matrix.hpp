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
        Matrix mul(float s) const;
        Vector mul(const Vector& v) const;
        Matrix mul(const Matrix& m2) const;
        Vector transpose_mul(const Vector& v) const;
        Matrix add(const Matrix& m2) const;
        Matrix subtract(const Matrix& m2) const;
        Matrix dual(const Vector& v) const; // Returns 2nd order skew-symmetric dual tensor of vector.

    public:
        static float pow2(float f); // avoids calling fabs below

        union {
                float d[3][3];
                Vector v[3];
        };

        Matrix();
        Matrix(const Vector& i, const Vector& j, const Vector& k);
        explicit Matrix(const Quaternion& q);
        Matrix(float e00, float e01, float e02, float e10, float e11, float e12, float e20, float e21, float e22);
        explicit Matrix(const PersistMatrix& src);
        Matrix get_transpose() const; // For a rotation matrix, inverse == transpose, but not for general matrices.
        Matrix get_inverse() const;
        Vector get_i() const;
        Vector get_j() const;
        Vector get_k() const;
        void set_i(const Vector& i);
        void set_j(const Vector& j);
        void set_k(const Vector& k);
        void set_orientation(float pitch_degrees, float roll_degrees,
                             float yaw_degrees); // Apply yaw, pitch, roll in order ( angles in degrees )
        void set_x_rotation(float angle);        // pitch
        void set_y_rotation(float angle);        // yaw
        void set_z_rotation(float angle);        // roll

        /* ---------- member functions */

        void rotate_around_i(float angle); // pitch
        void rotate_around_j(float angle); // yaw
        void rotate_around_k(float angle); // roll
        void x_rotate_left(float angle);   // pitch
        void y_rotate_left(float angle);   // yaw
        void z_rotate_left(float angle);   // roll
        void x_rotate_right(float angle);  // pitch
        void y_rotate_right(float angle);  // yaw
        void z_rotate_right(float angle);  // roll

        float det() const; // Returns determinant of matrix.
        const Matrix& set_identity(void);
        void make_orthogonal();
        const Matrix& zero(void);

        const Matrix& scale(float s);
        const Matrix& scale_by_reciprocal(float s);
        const Matrix& mul(const Matrix& m);
        void compose_rotation(unsigned axis, float angle); // expects degrees
        bool equal(const Matrix& m, float tolerance) const;

        [[nodiscard]]
        Vector euler(const bool inDegrees) const;

        const Matrix& operator+=(const Matrix& m);
        const Matrix& operator-=(const Matrix& m);
        const Matrix& operator*=(float s);
        const Matrix& operator/=(float s);
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
        FLSDK_IMPORT friend Matrix operator*(const Matrix& m, float s);
        FLSDK_IMPORT friend Matrix operator*(float s, const Matrix& m);
        FLSDK_IMPORT friend Matrix operator/(const Matrix& m, float s);
};

#endif // __MATRIX_H__
