#pragma once
#include "../../FLCoreDefs.hpp"
#include "CollisionEvent.hpp"

#undef GetCurrentTime

namespace PhySys
{
    struct RayHit;
    struct CreateParms;

    enum IVP_BOOL
    {
    };

    IMPORT f32 ANOM_LIMITS_MAX_ANGULAR_VELOCITY_PER_PSI;
    IMPORT f32 ANOM_LIMITS_MAX_VELOCITY;
    IMPORT void AddImpulseAtPoint(CObject*, const Vector&, const Vector&);
    IMPORT void AddToAngularVelocityOS(CObject*, const Vector&);
    IMPORT void AddToVelocity(CObject*, const Vector&);
    IMPORT void AngularImpulse(CObject*, const Vector&, f32);
    IMPORT void AngularImpulseOS(CObject*, const Vector&, f32);
    IMPORT bool AnyActive();
    IMPORT void Attach(CObject*, CObject*);
    IMPORT int AttachPhantom(CObject*, void*);
    IMPORT f32 BULLET_LENGTH_FUDGE;
    IMPORT void BeamR(CObject*, const Vector&, const Matrix&, bool);
    IMPORT void BuildIVP_Real(CObject*, const CreateParms&);
    IMPORT void BuildIVP_Sphere(CObject*, f32, const CreateParms&);
    IMPORT int CreatePhantom(const struct PhantomParms&, const PhyArch::Part&, void*&);
    IMPORT int CreatePhantom(const PhantomParms&, const Vector&, void*&);
    IMPORT int CreatePhantom(const PhantomParms&, f32, void*&);
    IMPORT Vector DEFAULT_ANGULAR_DAMPING;
    IMPORT f32 DEFAULT_LINEAR_DAMPING;
    IMPORT void DeactivatePhysics(CObject*);
    IMPORT void DeactivatePhysicsR(CObject*);
    IMPORT void DestroyPhantom(void*);
    IMPORT void Detach(CObject*, const struct DetachParms&);
    IMPORT int DetachPhantom(void*);
    IMPORT int FindRayCollisions(unsigned system, const Vector& origin, const Vector& end, RayHit* rh, int rh_count);
    IMPORT int FindRayIntersect(CObject*, const Vector&, const Vector&, RayHit*, int);
    IMPORT int FindSphereCollisions(unsigned system, const Vector&, f32, CObject**, int);
    IMPORT f32 GOLEM_ANGULAR_DAMP_FACTOR;
    IMPORT Vector GOLEM_CHILD_ANGULAR_DAMP;
    IMPORT f32 GOLEM_CHILD_LINEAR_DAMP;
    IMPORT f32 GOLEM_CHILD_MASS;
    IMPORT f32 GOLEM_DAMP_FACTOR;
    IMPORT f32 GOLEM_DELTA_ORIENTATION;
    IMPORT f32 GOLEM_FORCE_FACTOR;
    IMPORT f32 GOLEM_MAX_DELTA_POSITION;
    IMPORT f32 GOLEM_MAX_TORQUE;
    IMPORT Vector GOLEM_MAX_TRANSLATION_FORCE;
    IMPORT f32 GOLEM_TORQUE_FACTOR;
    IMPORT void GenerateCollisions(struct CBeam*);
    IMPORT Vector GetAngularVelocityOS(const CObject*);
    IMPORT Vector GetCenterOMass(const CObject*);
    IMPORT bool GetClosestPhantomIntruderPos(void*, u32, u32, struct CSimple*&, Vector&);
    IMPORT const char* GetCollisionGroup(const CObject*);
    IMPORT bool GetCollisionState(const CObject*);
    IMPORT bool GetCollisionStatePhantom(void* const);
    IMPORT void GetCollisions(u32, const CollisionEvent*&, const CollisionEvent*&);
    IMPORT class IVP_Time GetCurrentTime(u32);
    IMPORT void GetDamping(const CObject*, f32&, Vector&);
    IMPORT f32 GetMass(const CObject*);
    IMPORT Vector GetMomentOInertia(const CObject*);
    IMPORT f32 GetRadiusR(const CObject*, bool, Vector&);
    IMPORT Vector GetVelocity(const CObject*);
    IMPORT void LinearImpulse(CObject*, const Vector&, f32);
    IMPORT f64 MATERIAL_ELASTICITY;
    IMPORT f64 MATERIAL_FRICTION;
    IMPORT int MAX_SPAWNED_MINDIST_COUNT;
    IMPORT f64 MIN_TIME_BETWEEN_COLLISIONS;
    IMPORT u32 MovingObjectCount(u32);
    IMPORT f32 PHYSICAL_SIM_RATE;
    IMPORT void RCBegin(CSimple*, const Vector&, const Vector&, const Quaternion&, const Vector&);
    IMPORT void RCEnd(CSimple*);
    IMPORT void RCSet(CSimple*, const Vector&, const Quaternion&, f64);
    IMPORT f32 RC_MAX_DELTA_ORIENTATION;
    IMPORT f32 RC_MAX_DELTA_POSITION;
    IMPORT f32 RMGR_LOOK_AHEAD_MAX_DISTANCE_INTRA;
    IMPORT f32 RMGR_LOOK_AHEAD_MAX_DISTANCE_WORLD;
    IMPORT f32 RMGR_LOOK_AHEAD_MAX_RADIUS_INTRA;
    IMPORT f32 RMGR_LOOK_AHEAD_MAX_RADIUS_WORLD;
    IMPORT f32 RMGR_LOOK_AHEAD_MIN_DISTANCE_INTRA;
    IMPORT f32 RMGR_LOOK_AHEAD_MIN_DISTANCE_WORLD;
    IMPORT f32 RMGR_LOOK_AHEAD_MIN_SECONDS_INTRA;
    IMPORT f32 RMGR_LOOK_AHEAD_MIN_SECONDS_WORLD;
    IMPORT f32 RMGR_LOOK_AHEAD_TIME_INTRA;
    IMPORT f32 RMGR_LOOK_AHEAD_TIME_WORLD;
    IMPORT void ReMakePhysicalR(CObject*, const CreateParms&, f32);
    IMPORT void SetCollisionGroup(CObject*, const char* const);
    IMPORT void SetCollisionState(CObject*, bool);
    IMPORT void SetCollisionStatePhantom(void*, bool);
    IMPORT void SetDamping(CObject*, f32, const Vector&);
    IMPORT void SetMass(CObject*, f32);
    IMPORT void SetMomentOInertia(CObject*, const Vector&);
    IMPORT void Shutdown(u32);
    IMPORT void Startup(u32);
    IMPORT void UnMakePhysicalR(CObject*);
    IMPORT void Update(u32, f32);
    IMPORT void Wakeup(CObject*);
    IMPORT IVP_BOOL (*m_pCollisionFilter)(class IVP_Real_Object*, class IVP_Real_Object*);
} // namespace PhySys
