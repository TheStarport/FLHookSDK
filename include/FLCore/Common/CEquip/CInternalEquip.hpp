#pragma once
#include "../../FLCoreDefs.hpp"

#include <FLCore/Common/CEquip/CEquip.hpp>

class CInternalEquip : public CEquip
{
  public:
    IMPORT ~CInternalEquip() override;
    IMPORT bool GetEquipDesc(EquipDesc&) const override;

    IMPORT static CInternalEquip* cast(CEquip*);
    IMPORT static const CInternalEquip* cast(const CEquip*);

    IMPORT CInternalEquip(const CInternalEquip&);
    IMPORT CInternalEquip(u32, CEqObj*, u16, const Archetype::Equipment*, bool);
};
