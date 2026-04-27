#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "../ImportSdk.hpp"

/* ---------- headers */

#include "Matrix.hpp"
#include "PersistMath.hpp"

/* ---------- definitions */

class FLSDK_IMPORT Quaternion
{
    public:
        /* ---------- member variables */

        union {
                // 4-vector array.
                f32 d[4];

                // 4-vector with named elements.
                struct
                {
                        f32 w, x, y, z;
                };

#if !defined(ANONYMOUS_ILLEGAL)
                // Scalar + 3-vector.
                struct
                {
                        f32 s;
                        Vector v;
                };
#endif
        };

        Quaternion();
        explicit Quaternion(const Matrix& m);         // Converts rotation matrix to quaternion.
        Quaternion(const Vector& axis, f32 angle); // Creates quaternion representing a rotation by the given angle about the given axis.
        // Creates a quaternion with scalar part ZERO, vector part v. NOTE that this
        // is NOT in general equivalent to creating a quaternion with axis == v and
        // angle == 0.
        explicit Quaternion(const Vector& vec);
        Quaternion(f32 _w, f32 _x, f32 _y, f32 _z);
        Quaternion(const PersistQuaternion& src);

        Quaternion get_conjugate() const;
        Quaternion get_inverse() const;
        Quaternion get_log() const;
        Quaternion get_exp() const;   // Use on pure quaternions (s == 0)
        f32 get_magnitude() const; // For debugging purposes only. Quaternions representing rotations should always have magnitude 1.

        void set_identity();

        f32 norm() const;
        void normalize();
        Quaternion scale(f32 scalar);
        Quaternion scale_by_reciprocal(f32 scalar);
        Quaternion operator*=(f32 scalar);
        Quaternion operator/=(f32 scalar);
        Vector transform(const Vector& vec) const;
        void compute_axis_angle(Vector& axis, f32& angle); // Compute axis & angle representation of quaternion.

        FLSDK_IMPORT friend Quaternion operator+(const Quaternion& q1, const Quaternion& q2);
        FLSDK_IMPORT friend Quaternion operator-(const Quaternion& q1, const Quaternion& q2);
        FLSDK_IMPORT friend Quaternion operator*(const Quaternion& q1, const Quaternion& q2);
        FLSDK_IMPORT friend Quaternion operator*(const Quaternion& q, f32 scalar);
        FLSDK_IMPORT friend Quaternion operator/(const Quaternion& q, f32 scalar);
};

#endif // __QUATERNION_H__
