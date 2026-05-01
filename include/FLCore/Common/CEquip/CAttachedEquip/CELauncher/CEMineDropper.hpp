#pragma once
#include <FLCore/FLCoreDefs.hpp>

class CEMineDropper : public CELauncher
{
  public:
    IMPORT ~CEMineDropper() override;
    IMPORT FireResult CanFire(const Vector&) const override;

    IMPORT static CEMineDropper* cast(CEquip*);
    IMPORT static const CEMineDropper* cast(const CEquip*);

    IMPORT CEMineDropper(const CEMineDropper&);
    IMPORT CEMineDropper(CEqObj*, u16, const Archetype::MineDropper*, bool);
    IMPORT const Archetype::Mine* MineArch();
    IMPORT const Archetype::MineDropper* MineDropperArch();
};
