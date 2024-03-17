#pragma once
#include "FLCore/FLCoreDefs.hpp"

class CECargo : public CInternalEquip
{
    public:
    IMPORT virtual ~CECargo();
    IMPORT virtual bool IsDestroyed() const;
    IMPORT virtual bool GetEquipDesc(EquipDesc&) const;
    IMPORT virtual void Destroy();
    IMPORT virtual float GetHitPoints() const;
    IMPORT virtual void SetHitPoints(float);
    IMPORT virtual unsigned int GetType() const;                       // 88
    IMPORT virtual void Init(float, unsigned int, const CacheString&); // 92

    IMPORT static CECargo* cast(CEquip*);
    IMPORT static const CECargo* cast(const CEquip*);

    IMPORT CECargo(const CECargo&);
    IMPORT CECargo(CEqObj*, unsigned short, const Archetype::Equipment*, bool);
    IMPORT void AddToStack(unsigned int, float);
    IMPORT const class CECargoPod* GetContainer() const;
    IMPORT unsigned int GetCount() const;
    IMPORT float GetDecayDamagePerSecond() const;
    IMPORT void RemoveFromStack(unsigned int);
    IMPORT void SetCount(unsigned int);

    CECargoPod* cargoPod;
    float hitPts;
    uint count;
};