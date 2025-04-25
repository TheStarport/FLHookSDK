#pragma once

#include "CInternalEquip.hpp"

class CEArmor : public CInternalEquip
{
    public:
    IMPORT virtual ~CEArmor();

    IMPORT static CEArmor* cast(CEquip*);
    IMPORT static const CEArmor* cast(const CEquip*);

    IMPORT CEArmor(const CEArmor&);
    IMPORT CEArmor(CEqObj*, unsigned short, const Archetype::Armor*, bool);
    IMPORT const Archetype::Armor* ArmorArch() const;
};