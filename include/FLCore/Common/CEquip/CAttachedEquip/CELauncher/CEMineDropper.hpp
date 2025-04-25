#pragma once
#include "FLCore/FLCoreDefs.hpp"

class CEMineDropper : public CELauncher
{
    public:
    IMPORT virtual ~CEMineDropper();
    IMPORT virtual FireResult CanFire(const Vector&) const;

    IMPORT static CEMineDropper* cast(CEquip*);
    IMPORT static const CEMineDropper* cast(const CEquip*);

    IMPORT CEMineDropper(const CEMineDropper&);
    IMPORT CEMineDropper(CEqObj*, unsigned short, const Archetype::MineDropper*, bool);
    IMPORT const Archetype::Mine* MineArch();
    IMPORT const Archetype::MineDropper* MineDropperArch();
};