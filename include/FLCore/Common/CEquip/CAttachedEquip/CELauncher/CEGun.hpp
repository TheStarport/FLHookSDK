#pragma once
#include "../../../../FLCoreDefs.hpp"

struct CSimple;
class CEGun : public CELauncher
{
    public:
        IMPORT virtual ~CEGun();
        IMPORT virtual bool Update(float, unsigned int);
        IMPORT virtual bool Activate(bool);
        IMPORT virtual bool Connect(const char*);
        IMPORT virtual void Disconnect();
        IMPORT virtual FireResult Fire(const Vector&);
        IMPORT virtual void ConsumeFireResources();
        IMPORT virtual void ComputeLaunchInfo_OneBarrel(ProjLaunchInfo&, int, const Vector&) const;
        IMPORT virtual FireResult CanFire(const Vector&) const;

        IMPORT static const float TARGET_POINT_VALID_TIME;
        IMPORT static CEGun* cast(CEquip*);
        IMPORT static const CEGun* cast(const CEquip*);
        IMPORT static bool ComputeTimeToTgt(const Vector&, const Vector&, float, float&);

        IMPORT CEGun(const CEGun&);
        IMPORT CEGun(CEqObj*, unsigned short, const Archetype::Gun*, bool);
        IMPORT const Archetype::Gun* GunArch() const;
        IMPORT const Archetype::Munition* MunitionArch() const;
        IMPORT bool CanPointAt(const Vector&, float) const;
        IMPORT bool CanSeeTargetObject(float) const;
        IMPORT bool CanSeeTargetPoint(const Vector&, float) const;
        IMPORT bool ComputeTgtLeadPosition(Vector&) const;
        IMPORT float GetMunitionRange() const;
        IMPORT float GetSecondsTillLock() const;
        IMPORT void GetTarget(CSimple*&, unsigned short&) const;
        IMPORT Vector GetTurretOrigin() const;
        IMPORT bool IsJointInMotion() const;
        IMPORT bool SetTarget(CSimple*, unsigned short);
        IMPORT void SetTargetPoint(const Vector&);
        IMPORT bool is_guided() const;
        IMPORT void ComputeTurretFrame();
        IMPORT void DecomposeJointMotion(const Vector&, float&, float&) const;
        IMPORT bool IsMovable() const;
        IMPORT void LocateJoints();
        IMPORT void LoseJoints();

    protected:
        bool GetTargetObjectPos(Vector&) const;
};
