#pragma once
#include "../../../../FLCoreDefs.hpp"

#include "../CELauncher.hpp"

namespace Archetype
{
    struct Gun;
}

struct CSimple;
class CEGun : public CELauncher
{
    public:
        IMPORT virtual ~CEGun();
        IMPORT virtual bool Update(f32, u32);
        IMPORT virtual bool Activate(bool);
        IMPORT virtual bool Connect(const char*);
        IMPORT virtual void Disconnect();
        IMPORT virtual FireResult Fire(const Vector&);
        IMPORT virtual void ConsumeFireResources();
        IMPORT virtual void ComputeLaunchInfo_OneBarrel(ProjLaunchInfo&, int, const Vector&) const;
        IMPORT virtual FireResult CanFire(const Vector&) const;

        IMPORT static const f32 TARGET_POINT_VALID_TIME;
        IMPORT static CEGun* cast(CEquip*);
        IMPORT static const CEGun* cast(const CEquip*);
        IMPORT static bool ComputeTimeToTgt(const Vector&, const Vector&, f32, f32&);

        IMPORT CEGun(const CEGun&);
        IMPORT CEGun(CEqObj*, u16, const Archetype::Gun*, bool);
        IMPORT const Archetype::Gun* GunArch() const;
        IMPORT const Archetype::Munition* MunitionArch() const;
        IMPORT bool CanPointAt(const Vector&, f32) const;
        IMPORT bool CanSeeTargetObject(f32) const;
        IMPORT bool CanSeeTargetPoint(const Vector&, f32) const;
        IMPORT bool ComputeTgtLeadPosition(Vector&) const;
        IMPORT f32 GetMunitionRange() const;
        IMPORT f32 GetSecondsTillLock() const;
        IMPORT void GetTarget(CSimple*&, u16&) const;
        IMPORT Vector GetTurretOrigin() const;
        IMPORT bool IsJointInMotion() const;
        IMPORT bool SetTarget(CSimple*, u16);
        IMPORT void SetTargetPoint(const Vector&);
        IMPORT bool is_guided() const;
        IMPORT void ComputeTurretFrame();
        IMPORT void DecomposeJointMotion(const Vector&, f32&, f32&) const;
        IMPORT bool IsMovable() const;
        IMPORT void LocateJoints();
        IMPORT void LoseJoints();

    protected:
        bool GetTargetObjectPos(Vector&) const;
};
