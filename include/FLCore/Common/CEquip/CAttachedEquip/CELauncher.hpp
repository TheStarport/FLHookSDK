#pragma once
#include "../../../FLCoreDefs.hpp"

class CELauncher : public CAttachedEquip
{
    public:

    IMPORT virtual ~CELauncher();
    IMPORT virtual bool IsDisabled() const;
    IMPORT virtual bool Update(float, unsigned int);
    IMPORT virtual void GetStatus(EquipStatus&) const;
    IMPORT virtual bool Connect(const char*);
    IMPORT virtual void Disconnect();
    IMPORT virtual FireResult Fire(const Vector&);
    IMPORT virtual void ConsumeFireResources();
    IMPORT virtual void ComputeLaunchInfo(st6::vector<struct ProjLaunchInfo>&, const Vector&) const;
    IMPORT virtual float GetPowerDrawPerFire() const;
    IMPORT virtual int GetAmmoCount() const;
    IMPORT virtual bool AmmoNeedsMet() const;
    IMPORT virtual void ComputeLaunchInfo_OneBarrel(ProjLaunchInfo&, int, const Vector&) const;
    IMPORT virtual FireResult CanFire(const Vector&) const;
    IMPORT virtual bool PowerNeedsMet() const;
    IMPORT virtual void DrawPower(int);
    IMPORT virtual void DrawAmmoFromCargo(int);
    IMPORT virtual bool RefireDelayElapsed() const;

    IMPORT CELauncher(const CELauncher&);
    IMPORT CELauncher(unsigned int, CEqObj*, unsigned short, const Archetype::Launcher*, bool);
    IMPORT void ComputeProjectilePosAndVelocity_OneBarrel(Vector&, Vector&, int, const Vector&) const;
    IMPORT Vector GetAvgBarrelDirWS() const;
    IMPORT Vector GetAvgBarrelPosWS() const;
    IMPORT Vector GetBarrelDirWS(unsigned int) const;
    IMPORT const struct Barrel* GetBarrelInfo(unsigned int) const;
    IMPORT Vector GetBarrelPosWS(unsigned int) const;
    IMPORT unsigned int GetProjectilesPerFire() const;
    IMPORT const Archetype::Launcher* LauncherArch() const;
    IMPORT const Archetype::Projectile* ProjectileArch() const;
    IMPORT static CELauncher* cast(CEquip*);
    IMPORT static const CELauncher* cast(const CEquip*);

    int dunno[28];
    float OfflineThreshold;
    float OfflineRebuildTime;
    float MaxCapacity;
};