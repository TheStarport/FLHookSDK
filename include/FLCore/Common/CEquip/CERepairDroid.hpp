#pragma once
#include "../../FLCoreDefs.hpp"

class CERepairDroid : public CEquip
{
    public:
    IMPORT virtual ~CERepairDroid();
    IMPORT virtual f32 GetHitPoints() const;
    IMPORT virtual void SetHitPoints(f32);

    IMPORT static CERepairDroid* cast(CEquip*);
    IMPORT static const CERepairDroid* cast(const CEquip*);

    IMPORT CERepairDroid(const CERepairDroid&);
    IMPORT CERepairDroid(CEqObj*, u16, const Archetype::RepairDroid*, bool);
    IMPORT const Archetype::RepairDroid* RepairDroidArch() const;

    public:
    Archetype::RepairDroid* archetype;
};