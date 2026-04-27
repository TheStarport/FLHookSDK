#pragma once
#include "../../../FLCoreDefs.hpp"

#include <FLCore/Common/CEquip/CInternalEquip.hpp>

class CECargo : public CInternalEquip
{
    public:
    IMPORT virtual ~CECargo();
    IMPORT virtual bool IsDestroyed() const;
    IMPORT virtual bool GetEquipDesc(EquipDesc&) const;
    IMPORT virtual void Destroy();
    IMPORT virtual f32 GetHitPoints() const;
    IMPORT virtual void SetHitPoints(f32);
    IMPORT virtual u32 GetType() const;                       // 88
    IMPORT virtual void Init(f32, u32, const CacheString&); // 92

    IMPORT static CECargo* cast(CEquip*);
    IMPORT static const CECargo* cast(const CEquip*);

    IMPORT CECargo(const CECargo&);
    IMPORT CECargo(CEqObj*, u16, const Archetype::Equipment*, bool);
    IMPORT void AddToStack(u32, f32);
    IMPORT const class CECargoPod* GetContainer() const;
    IMPORT u32 GetCount() const;
    IMPORT f32 GetDecayDamagePerSecond() const;
    IMPORT void RemoveFromStack(u32);
    IMPORT void SetCount(u32);

    CECargoPod* cargoPod;
    f32 hitPts;
    unsigned count;
};