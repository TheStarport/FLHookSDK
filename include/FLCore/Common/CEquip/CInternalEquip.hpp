#pragma once
#include "../../FLCoreDefs.hpp"

class CInternalEquip : public CEquip
{
    public:
    IMPORT virtual ~CInternalEquip();
    IMPORT virtual bool GetEquipDesc(EquipDesc&) const;

    IMPORT static CInternalEquip* cast(CEquip*);
    IMPORT static const CInternalEquip* cast(const CEquip*);

    IMPORT CInternalEquip(const CInternalEquip&);
    IMPORT CInternalEquip(unsigned int, CEqObj*, unsigned short, const Archetype::Equipment*, bool);
};