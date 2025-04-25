#pragma once
#include "../../FLCoreDefs.hpp"
#include "CollisionEvent.hpp"

namespace PhySys
{
    struct RayHit;
    struct CreateParms;

    enum IVP_BOOL
    {
    };

    IMPORT float ANOM_LIMITS_MAX_ANGULAR_VELOCITY_PER_PSI;
    IMPORT float ANOM_LIMITS_MAX_VELOCITY;
    IMPORT void AddImpulseAtPoint(CObject*, const Vector&, const Vector&);
    IMPORT void AddToAngularVelocityOS(CObject*, const Vector&);
    IMPORT void AddToVelocity(CObject*, const Vector&);
    IMPORT void AngularImpulse(CObject*, const Vector&, float);
    IMPORT void AngularImpulseOS(CObject*, const Vector&, float);
    IMPORT bool AnyActive();
    IMPORT void Attach(CObject*, CObject*);
    IMPORT int AttachPhantom(CObject*, void*);
    IMPORT float BULLET_LENGTH_FUDGE;
    IMPORT void BeamR(CObject*, const Vector&, const Matrix&, bool);
    IMPORT void BuildIVP_Real(CObject*, const CreateParms&);
    IMPORT void BuildIVP_Sphere(CObject*, float, const CreateParms&);
    IMPORT int CreatePhantom(const struct PhantomParms&, const PhyArch::Part&, void*&);
    IMPORT int CreatePhantom(const PhantomParms&, const Vector&, void*&);
    IMPORT int CreatePhantom(const PhantomParms&, float, void*&);
    IMPORT Vector DEFAULT_ANGULAR_DAMPING;
    IMPORT float DEFAULT_LINEAR_DAMPING;
    IMPORT void DeactivatePhysics(CObject*);
    IMPORT void DeactivatePhysicsR(CObject*);
    IMPORT void DestroyPhantom(void*);
    IMPORT void Detach(CObject*, const struct DetachParms&);
    IMPORT int DetachPhantom(void*);
    IMPORT int FindRayCollisions(unsigned int system, const Vector& origin, const Vector& end, RayHit* rh, int rh_count);
    IMPORT int FindRayIntersect(CObject*, const Vector&, const Vector&, RayHit*, int);
    IMPORT int FindSphereCollisions(unsigned int, const Vector&, float, CObject**, int);
    IMPORT float GOLEM_ANGULAR_DAMP_FACTOR;
    IMPORT Vector GOLEM_CHILD_ANGULAR_DAMP;
    IMPORT float GOLEM_CHILD_LINEAR_DAMP;
    IMPORT float GOLEM_CHILD_MASS;
    IMPORT float GOLEM_DAMP_FACTOR;
    IMPORT float GOLEM_DELTA_ORIENTATION;
    IMPORT float GOLEM_FORCE_FACTOR;
    IMPORT float GOLEM_MAX_DELTA_POSITION;
    IMPORT float GOLEM_MAX_TORQUE;
    IMPORT Vector GOLEM_MAX_TRANSLATION_FORCE;
    IMPORT float GOLEM_TORQUE_FACTOR;
    IMPORT void GenerateCollisions(struct CBeam*);
    IMPORT Vector GetAngularVelocityOS(const CObject*);
    IMPORT Vector GetCenterOMass(const CObject*);
    IMPORT bool GetClosestPhantomIntruderPos(void*, unsigned int, unsigned int, struct CSimple*&, Vector&);
    IMPORT const char* GetCollisionGroup(const CObject*);
    IMPORT bool GetCollisionState(const CObject*);
    IMPORT bool GetCollisionStatePhantom(void* const);
    IMPORT void GetCollisions(unsigned int, const CollisionEvent*&, const CollisionEvent*&);
    IMPORT class IVP_Time GetCurrentTime(unsigned int);
    IMPORT void GetDamping(const CObject*, float&, Vector&);
    IMPORT float GetMass(const CObject*);
    IMPORT Vector GetMomentOInertia(const CObject*);
    IMPORT float GetRadiusR(const CObject*, bool, Vector&);
    IMPORT Vector GetVelocity(const CObject*);
    IMPORT void LinearImpulse(CObject*, const Vector&, float);
    IMPORT double MATERIAL_ELASTICITY;
    IMPORT double MATERIAL_FRICTION;
    IMPORT int MAX_SPAWNED_MINDIST_COUNT;
    IMPORT double MIN_TIME_BETWEEN_COLLISIONS;
    IMPORT unsigned int MovingObjectCount(unsigned int);
    IMPORT float PHYSICAL_SIM_RATE;
    IMPORT void RCBegin(CSimple*, const Vector&, const Vector&, const Quaternion&, const Vector&);
    IMPORT void RCEnd(CSimple*);
    IMPORT void RCSet(CSimple*, const Vector&, const Quaternion&, double);
    IMPORT float RC_MAX_DELTA_ORIENTATION;
    IMPORT float RC_MAX_DELTA_POSITION;
    IMPORT float RMGR_LOOK_AHEAD_MAX_DISTANCE_INTRA;
    IMPORT float RMGR_LOOK_AHEAD_MAX_DISTANCE_WORLD;
    IMPORT float RMGR_LOOK_AHEAD_MAX_RADIUS_INTRA;
    IMPORT float RMGR_LOOK_AHEAD_MAX_RADIUS_WORLD;
    IMPORT float RMGR_LOOK_AHEAD_MIN_DISTANCE_INTRA;
    IMPORT float RMGR_LOOK_AHEAD_MIN_DISTANCE_WORLD;
    IMPORT float RMGR_LOOK_AHEAD_MIN_SECONDS_INTRA;
    IMPORT float RMGR_LOOK_AHEAD_MIN_SECONDS_WORLD;
    IMPORT float RMGR_LOOK_AHEAD_TIME_INTRA;
    IMPORT float RMGR_LOOK_AHEAD_TIME_WORLD;
    IMPORT void ReMakePhysicalR(CObject*, const CreateParms&, float);
    IMPORT void SetCollisionGroup(CObject*, const char* const);
    IMPORT void SetCollisionState(CObject*, bool);
    IMPORT void SetCollisionStatePhantom(void*, bool);
    IMPORT void SetDamping(CObject*, float, const Vector&);
    IMPORT void SetMass(CObject*, float);
    IMPORT void SetMomentOInertia(CObject*, const Vector&);
    IMPORT void Shutdown(unsigned int);
    IMPORT void Startup(unsigned int);
    IMPORT void UnMakePhysicalR(CObject*);
    IMPORT void Update(unsigned int, float);
    IMPORT void Wakeup(CObject*);
    IMPORT IVP_BOOL (*m_pCollisionFilter)(class IVP_Real_Object*, class IVP_Real_Object*);
} // namespace PhySys
