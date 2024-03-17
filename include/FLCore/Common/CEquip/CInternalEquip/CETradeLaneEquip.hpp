#pragma once
#include "FLCore/FLCoreDefs.hpp"

class CETradeLaneEquip : public CInternalEquip
{
    public:
    IMPORT virtual ~CETradeLaneEquip();

    IMPORT static CETradeLaneEquip* cast(CEquip*);
    IMPORT static const CETradeLaneEquip* cast(const CEquip*);

    IMPORT CETradeLaneEquip(const CETradeLaneEquip&);
    IMPORT CETradeLaneEquip(CEqObj*, unsigned short, const Archetype::TradeLaneEquip*, bool);
    IMPORT const Archetype::TradeLaneEquip* TradeLaneArch() const;

    IMPORT Archetype::TradeLaneEquip* archType;
};