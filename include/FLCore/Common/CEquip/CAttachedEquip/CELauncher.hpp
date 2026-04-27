#pragma once
#include "../../../FLCoreDefs.hpp"
#include "../CAttachedEquip.hpp"
#include "../../Archetype/Root/Equipment/AttachedEquipment/Launcher.hpp"
#include "../../Archetype/Root/Equipment/Projectile.hpp"

struct Barrel
{
        long index;
        unsigned dunno[12];
};

class CELauncher : public CAttachedEquip
{
    public:
        IMPORT virtual ~CELauncher();
        IMPORT virtual bool IsDisabled() const;
        IMPORT virtual bool Update(f32, u32);
        IMPORT virtual void GetStatus(EquipStatus&) const;
        IMPORT virtual bool Connect(const char*);
        IMPORT virtual void Disconnect();

        IMPORT virtual FireResult Fire(const Vector&);                                                   //144
        IMPORT virtual void ConsumeFireResources();                                                      //148
        IMPORT virtual void ComputeLaunchInfo(st6::vector<struct ProjLaunchInfo>&, const Vector&) const; //152
        IMPORT virtual f32 GetPowerDrawPerFire() const;                                                //156
        IMPORT virtual int GetAmmoCount() const;                                                         //160
        IMPORT virtual bool AmmoNeedsMet() const;                                                        //164
        IMPORT virtual void ComputeLaunchInfo_OneBarrel(ProjLaunchInfo&, int, const Vector&) const;      //168
        IMPORT virtual FireResult CanFire(const Vector&) const;                                          //172
        IMPORT virtual bool PowerNeedsMet() const;                                                       //176
        IMPORT virtual void DrawPower(int);                                                              //180
        IMPORT virtual void DrawAmmoFromCargo(int);                                                      //184
        IMPORT virtual bool RefireDelayElapsed() const;                                                  //188

        IMPORT CELauncher(const CELauncher&);
        IMPORT CELauncher(u32, CEqObj*, u16, const Archetype::Launcher*, bool);
        IMPORT void ComputeProjectilePosAndVelocity_OneBarrel(Vector&, Vector&, int, const Vector&) const;
        IMPORT Vector GetAvgBarrelDirWS() const;
        IMPORT Vector GetAvgBarrelPosWS() const;
        IMPORT Vector GetBarrelDirWS(u32) const;
        IMPORT const struct Barrel* GetBarrelInfo(u32) const;
        IMPORT Vector GetBarrelPosWS(u32) const;
        IMPORT u32 GetProjectilesPerFire() const;
        IMPORT const Archetype::Launcher* LauncherArch() const;
        IMPORT const Archetype::Projectile* ProjectileArch() const;
        IMPORT static CELauncher* cast(CEquip*);
        IMPORT static const CELauncher* cast(const CEquip*);

        f32 GetEffectiveRange() const { return projArch->lifeTime * LauncherArch()->muzzleVelocity; }

        Archetype::Projectile* projArch; // 19
        f32 refireDelayElapsed;        // 20
        Barrel barrels[8];               // 21
};

class EqObj;
struct SrvGun
{
        void* vtable;
        CELauncher* launcher;
        EqObj* owner;
};
