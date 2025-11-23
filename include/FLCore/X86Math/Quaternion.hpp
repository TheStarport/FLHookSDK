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
                SINGLE d[4];

                // 4-vector with named elements.
                struct
                {
                        SINGLE w, x, y, z;
                };

#if !defined(ANONYMOUS_ILLEGAL)
                // Scalar + 3-vector.
                struct
                {
                        SINGLE s;
                        Vector v;
                };
#endif
        };

        Quaternion();
        explicit Quaternion(const Matrix& m);         // Converts rotation matrix to quaternion.
        Quaternion(const Vector& axis, SINGLE angle); // Creates quaternion representing a rotation by the given angle about the given axis.
        // Creates a quaternion with scalar part ZERO, vector part v. NOTE that this
        // is NOT in general equivalent to creating a quaternion with axis == v and
        // angle == 0.
        explicit Quaternion(const Vector& vec);
        Quaternion(SINGLE _w, SINGLE _x, SINGLE _y, SINGLE _z);
        Quaternion(const PersistQuaternion& src);

        Quaternion get_conjugate() const;
        Quaternion get_inverse() const;
        Quaternion get_log() const;
        Quaternion get_exp() const;   // Use on pure quaternions (s == 0)
        SINGLE get_magnitude() const; // For debugging purposes only. Quaternions representing rotations should always have magnitude 1.

        void set_identity();

        SINGLE norm() const;
        void normalize();
        Quaternion scale(SINGLE scalar);
        Quaternion scale_by_reciprocal(SINGLE scalar);
        Quaternion operator*=(SINGLE scalar);
        Quaternion operator/=(SINGLE scalar);
        Vector transform(const Vector& vec) const;
        void compute_axis_angle(Vector& axis, float& angle); // Compute axis & angle representation of quaternion.

        FLSDK_IMPORT friend Quaternion operator+(const Quaternion& q1, const Quaternion& q2);
        FLSDK_IMPORT friend Quaternion operator-(const Quaternion& q1, const Quaternion& q2);
        FLSDK_IMPORT friend Quaternion operator*(const Quaternion& q1, const Quaternion& q2);
        FLSDK_IMPORT friend Quaternion operator*(const Quaternion& q, SINGLE scalar);
        FLSDK_IMPORT friend Quaternion operator/(const Quaternion& q, SINGLE scalar);
};

#endif // __QUATERNION_H__
