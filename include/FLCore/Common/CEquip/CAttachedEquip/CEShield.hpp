#pragma once
#include "../../../FLCoreDefs.hpp"

#include "../../Strings.hpp"
#include "../CAttachedEquip.hpp"

namespace Archetype
{
    struct Shield;
    struct ShieldGenerator;
} // namespace Archetype

class CEShield : public CAttachedEquip
{
  public:
    IMPORT ~CEShield() override;
    IMPORT bool IsFunctioning() const override;
    IMPORT bool Update(f32, u32) override;
    IMPORT bool GetEquipDesc(EquipDesc&) const override;
    IMPORT bool Activate(bool) override;
    IMPORT void Destroy() override;
    IMPORT f32 GetMaxHitPoints() const override;
    IMPORT f32 GetHitPoints() const override;
    IMPORT void SetHitPoints(f32) override;
    IMPORT bool Connect(const char*) override;
    IMPORT void Disconnect() override;

    IMPORT static CEShield* cast(CEquip*);
    IMPORT static const CEShield* cast(const CEquip*);

    IMPORT CEShield(const CEShield&);
    IMPORT CEShield(CEqObj*, u16, const Archetype::Shield*, bool);
    IMPORT const Archetype::ShieldGenerator* ShieldGenArch() const;
    IMPORT const Archetype::Shield* ShieldArch() const;
    IMPORT void AttachIntruderChecker();
    IMPORT void DestroyIntruderChecker();
    IMPORT f32 GetOfflineRebuildTime() const;
    IMPORT f32 GetOfflineThreshold() const;
    IMPORT f32 GetWeaponModifier(const ID_String&) const;
    IMPORT void ShieldBatteryBoost(f32);
    IMPORT bool Activate_Internal(bool);
    IMPORT void AddGen(class CEShieldGenerator*);
    IMPORT bool CanActivate() const;
    IMPORT void RemGen(CEShieldGenerator*);

    bool internalActivationState;
    f32 currShieldHitPoints;
    unsigned seeminglyUnused;
    f64 rebuildTimestamp;
    st6::vector<CEShieldGenerator*> linkedShieldGen;
    Archetype::ShieldGenerator* highestToughnessShieldGenArch;
    f32 offlineThreshold;
    f32 rebuildTime;
    f32 maxShieldHitPoints;
    void* IntruderCheckerPhySys1;
    void* IntruderCheckerPhySys2;
};

struct IObjClientEqObj;
struct CliShield
{
    void* vtable;
    CEShield* shield;
    IObjClientEqObj* owner;
};
