#pragma once
#include "../../../FLCoreDefs.hpp"

class CEShield : public CAttachedEquip
{
    public:
    IMPORT virtual ~CEShield();
    IMPORT virtual bool IsFunctioning() const;
    IMPORT virtual bool Update(float, unsigned int);
    IMPORT virtual bool GetEquipDesc(EquipDesc&) const;
    IMPORT virtual bool Activate(bool);
    IMPORT virtual void Destroy();
    IMPORT virtual float GetMaxHitPoints() const;
    IMPORT virtual float GetHitPoints() const;
    IMPORT virtual void SetHitPoints(float);
    IMPORT virtual bool Connect(const char*);
    IMPORT virtual void Disconnect();

    IMPORT static CEShield* cast(CEquip*);
    IMPORT static const CEShield* cast(const CEquip*);

    IMPORT CEShield(const CEShield&);
    IMPORT CEShield(CEqObj*, unsigned short, const Archetype::Shield*, bool);
    IMPORT const Archetype::ShieldGenerator* ShieldGenArch() const;
    IMPORT const Archetype::Shield* ShieldArch() const;
    IMPORT void AttachIntruderChecker();
    IMPORT void DestroyIntruderChecker();
    IMPORT float GetOfflineRebuildTime() const;
    IMPORT float GetOfflineThreshold() const;
    IMPORT float GetWeaponModifier(const ID_String&) const;
    IMPORT void ShieldBatteryBoost(float);
    IMPORT bool Activate_Internal(bool);
    IMPORT void AddGen(class CEShieldGenerator*);
    IMPORT bool CanActivate() const;
    IMPORT void RemGen(CEShieldGenerator*);

	uint dunnoShield;
	float currentShieldHitPoints;
	uint dunnoShield2[3];
	st6::vector<CEShieldGenerator*> linkedShieldGen;
	Archetype::ShieldGenerator* mainShieldGenArch;
	float offlineThreshold;
	float rebuildTime;
	float maxShieldHitPoints;
	void* IntruderCheckerPhySys1;
	void* IntruderCheckerPhySys2;
};