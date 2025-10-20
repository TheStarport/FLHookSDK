#pragma once
#include "../../../FLCoreDefs.hpp"
#include "../CAttachedEquip.hpp"
#include "../../Archetype/Root/Equipment/AttachedEquipment/Launcher.hpp"
#include "../../Archetype/Root/Equipment/Projectile.hpp"

struct Barrel
{
        uint dunno[13];
};

class CELauncher : public CAttachedEquip
{
    public:
        IMPORT virtual ~CELauncher();
        IMPORT virtual bool IsDisabled() const;
        IMPORT virtual bool Update(float, unsigned int);
        IMPORT virtual void GetStatus(EquipStatus&) const;
        IMPORT virtual bool Connect(const char*);
        IMPORT virtual void Disconnect();

        IMPORT virtual FireResult Fire(const Vector&);                                                   //144
        IMPORT virtual void ConsumeFireResources();                                                      //148
        IMPORT virtual void ComputeLaunchInfo(st6::vector<struct ProjLaunchInfo>&, const Vector&) const; //152
        IMPORT virtual float GetPowerDrawPerFire() const;                                                //156
        IMPORT virtual int GetAmmoCount() const;                                                         //160
        IMPORT virtual bool AmmoNeedsMet() const;                                                        //164
        IMPORT virtual void ComputeLaunchInfo_OneBarrel(ProjLaunchInfo&, int, const Vector&) const;      //168
        IMPORT virtual FireResult CanFire(const Vector&) const;                                          //172
        IMPORT virtual bool PowerNeedsMet() const;                                                       //176
        IMPORT virtual void DrawPower(int);                                                              //180
        IMPORT virtual void DrawAmmoFromCargo(int);                                                      //184
        IMPORT virtual bool RefireDelayElapsed() const;                                                  //188

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

        Archetype::Projectile* projArch; // 19
        float refireDelayElapsed;        // 20
        Barrel barrels[8];               // 21
};

struct SrvGun
{
        void* vtable;
        CELauncher* launcher;
};
