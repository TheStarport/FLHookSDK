#pragma once
#include "FLCore/FLCoreDefs.hpp"

struct EngineObject
{
    public:
        IMPORT virtual void __stdcall initialize_instance(long);                        // 0
        IMPORT virtual void __stdcall create_instance(long);                            // 4
        IMPORT virtual void __stdcall destroy_instance(long);                           // 8
        IMPORT virtual void __stdcall set_position(long, const Vector&);                // 12
        IMPORT virtual const Vector& __stdcall get_position(long) const;                // 16
        IMPORT virtual void __stdcall set_orientation(long, const Matrix&);             // 20
        IMPORT virtual const Matrix& __stdcall get_orientation(long) const;             // 24
        IMPORT virtual void __stdcall set_transform(long, const class Transform&);      // 28
        IMPORT virtual const Transform& __stdcall get_transform(long) const;            // 32
        IMPORT virtual void __stdcall get_centered_radius(long, float*, Vector*) const; // 36
        IMPORT virtual void __stdcall set_centered_radius(long, float, const Vector&);  // 40
        IMPORT virtual void __stdcall set_instance_flags(long, unsigned long);          // 44
        IMPORT virtual unsigned long __stdcall get_instance_flags(long) const;          // 48
        IMPORT virtual bool __stdcall joint_changed(long);                              // 52
        IMPORT virtual ~EngineObject();                                                 // 56
        IMPORT virtual const Vector& __stdcall get_velocity(long) const;                // 60
        IMPORT virtual void __stdcall set_velocity(long, const Vector&);                // 64
        IMPORT virtual const Vector& __stdcall get_angular_velocity(long) const;        // 68
        IMPORT virtual void __stdcall set_angular_velocity(long, const Vector&);        // 72

        IMPORT EngineObject(const EngineObject&);
        IMPORT EngineObject();
        IMPORT EngineObject& operator=(const EngineObject&);
        IMPORT const Matrix& get_orientation() const;
        IMPORT const Vector& get_position() const;
        IMPORT const float get_radius() const;
        IMPORT const Transform& get_transform() const;
        IMPORT void set_centered_radius(float, const Vector&);
        IMPORT void set_orientation(const Matrix&);
        IMPORT void set_position(const Vector&);
        IMPORT void set_transform(const Transform&);
        IMPORT void update_tree() const;

        void* index;         // 1 fetched in CBase::get_index()
        Matrix orientation;  // 2
        Vector position;     // 11
        float radius;        // 14
        Vector centerOfMass; // 15
        uint instanceFlags;  // 18
};
