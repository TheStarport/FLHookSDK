#pragma once
#include "../../FLCoreDefs.hpp"

#include "CEquip.hpp"

namespace Archetype
{
    struct Light;
}

class CELightEquip : CEquip
{
  public:
    IMPORT ~CELightEquip() override;
    IMPORT void NotifyArchGroupDestroyed(u16) override;

    IMPORT static CELightEquip* cast(CEquip*);
    IMPORT static const CELightEquip* cast(const CEquip*);

    IMPORT CELightEquip(const CELightEquip&);
    IMPORT CELightEquip(CEqObj*, u16, const Archetype::Light*, bool);
    IMPORT const Archetype::Light* LightArch() const;
};
