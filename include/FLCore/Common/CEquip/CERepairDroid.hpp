#pragma once
#include "../../FLCoreDefs.hpp"

class CERepairDroid : public CEquip
{
    public:
    IMPORT virtual ~CERepairDroid();
    IMPORT virtual float GetHitPoints() const;
    IMPORT virtual void SetHitPoints(float);

    IMPORT static CERepairDroid* cast(CEquip*);
    IMPORT static const CERepairDroid* cast(const CEquip*);

    IMPORT CERepairDroid(const CERepairDroid&);
    IMPORT CERepairDroid(CEqObj*, unsigned short, const Archetype::RepairDroid*, bool);
    IMPORT const Archetype::RepairDroid* RepairDroidArch() const;

    public:
    Archetype::RepairDroid* archetype;
};