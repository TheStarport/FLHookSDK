#pragma once
#include "../../FLCoreDefs.hpp"

#include <FLCore/Common/CEquip/CEquip.hpp>

class CInternalEquip : public CEquip
{
    public:
    IMPORT virtual ~CInternalEquip();
    IMPORT virtual bool GetEquipDesc(EquipDesc&) const;

    IMPORT static CInternalEquip* cast(CEquip*);
    IMPORT static const CInternalEquip* cast(const CEquip*);

    IMPORT CInternalEquip(const CInternalEquip&);
    IMPORT CInternalEquip(u32, CEqObj*, u16, const Archetype::Equipment*, bool);
};