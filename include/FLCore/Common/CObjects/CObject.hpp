#pragma once

#include "EngineObject.hpp"

struct CBase;
namespace Archetype
{
    struct Root;
}
namespace PhySys
{
    class PhyCollisionStateManager;
    struct CreateParms;
}
struct CObject : public EngineObject
{
    public:
        IMPORT virtual void __stdcall destroy_instance(long);                   // 8
        IMPORT virtual ~CObject();                                              // 56
        IMPORT virtual void open(Archetype::Root*);                             // 76
        IMPORT virtual int update(float, unsigned int);                         // 80
        IMPORT virtual Vector get_velocity() const;                             // 84
        IMPORT virtual Vector get_angular_velocity() const;                     // 88
        IMPORT virtual void disable_controllers();                              // 92
        IMPORT virtual void enable_controllers();                               // 96
        IMPORT virtual float get_physical_radius_r(Vector&) const;              // 100
        IMPORT virtual Vector get_center_of_mass() const;                       // 104
        IMPORT virtual float get_mass() const;                                  // 108
        IMPORT virtual bool get_surface_extents(Vector&, Vector&) const;        // 112
        IMPORT virtual void unmake_physical();                                  // 116
        IMPORT virtual void remake_physical(const PhySys::CreateParms&, float); // 120
        IMPORT virtual void beam_object(const Vector&, const Matrix&, bool);    // 124

        enum Class
        {
            COBJECT_MASK = 0x1,
            CSIMPLE_MASK = 0x2 | COBJECT_MASK,
            CPROJECTILE_MASK = 0x4 | CSIMPLE_MASK,
            CEQOBJ_MASK = 0x100 | CSIMPLE_MASK,

            // CObject children
            CEQUIPMENT_OBJECT = 0x2000 | COBJECT_MASK,
            CDYNAMICASTEROID_OBJECT = 0x4000 | COBJECT_MASK,

            // CSimple children
            CLOOT_OBJECT = 0x800 | CSIMPLE_MASK,
            CASTEROID_OBJECT = 0x1000 | CSIMPLE_MASK,

            // CProjectile children
            CMINE_OBJECT = 0x8 | CPROJECTILE_MASK,
            CCOUNTERMEASURE_OBJECT = 0x10 | CPROJECTILE_MASK,
            CBEAM_OBJECT = 0x60 | CPROJECTILE_MASK,
            CGUIDED_OBJECT = 0xA0 | CPROJECTILE_MASK,

            // CEqObj children
            CSOLAR_OBJECT = 0x200 | CEQOBJ_MASK,
            CSHIP_OBJECT = 0x400 | CEQOBJ_MASK,
        };

        IMPORT static CObject* Alloc(Class);
        IMPORT static CObject* Find(const unsigned int&, Class);
        IMPORT static CObject* Find(long, Class);
        IMPORT static CObject* FindFirst(Class);
        IMPORT static CObject* FindNext();
        IMPORT static int Count(Class);
        IMPORT static void ReleaseAll();
        IMPORT static const unsigned int NoActions;
        IMPORT static const unsigned int NoBehavior;
        IMPORT static const unsigned int NoCountermeasureAi;
        IMPORT static const unsigned int NoDynamics;
        IMPORT static const unsigned int NoScanner;
        IMPORT static const unsigned int UpdateDefault;
        IMPORT static const unsigned int UpdateDumb;

        IMPORT static void* operator new(unsigned int);
        IMPORT static void operator delete(void*);

        IMPORT CObject(const CObject&);
        IMPORT CObject(Class);
        IMPORT unsigned int AddRef();
        IMPORT unsigned int Release();
        IMPORT void add_impulse(const Vector&, const Vector&);
        IMPORT void add_impulse(const Vector&);
        IMPORT void advise(CBase*, bool);
        IMPORT void enable_collisions_r(bool);
        IMPORT bool flag_part_as_shield(unsigned int);
        IMPORT Archetype::Root* get_archetype() const;
        IMPORT Vector get_moment_of_inertia() const;
        IMPORT float hierarchy_radius(Vector&) const;
        IMPORT float hierarchy_radius() const;
        IMPORT unsigned int inst_to_part(long) const;
        IMPORT bool is_shield_part(unsigned int) const;
        IMPORT long part_to_inst(unsigned int) const;

        Class objectClass; // 19
        uint system;       // 20
        uint dunnoCObject; // 21, relates to all PhySys calls, PhySys calls only occur if this value is nonzero
        struct SurfaceExtents
        {
                uint dunno[2];
                Vector min, max;
        };
        SurfaceExtents* surf; // 22

        uint dunnoCObject2;                                // 23 Parts related
        uint dunnoCObject3;                                // 24
        bool dunnoCObject4;                                // 25
        uint dunnoCObjectShield1;                          // 26 maybe just Parts related
        uint dunnoCObjectShield2;                          // 27
        uint dunnoCObject5;                                // 28
        uint dunnoCObject6;                                // 29
        bool dunnoCObject7;                                // 30
        void* unkListCObj;                                 // 31 twodirectional list containing a single value
        uint unkListSize;                                  // 32
        PhySys::PhyCollisionStateManager* colStateManager; // 33
        Archetype::Root* archetype;                        // 34
        uint dunnoCObject8;                                // 35
        void* unkListCObj2;                                // 36 used in CObject::advise
        uint unkList2Size;                                 // 37
        uint referenceCounter;                             // 38
};