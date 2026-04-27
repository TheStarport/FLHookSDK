#pragma once
#include "../../FLCoreDefs.hpp"

class CELightEquip : CEquip
{
    public:
    IMPORT virtual ~CELightEquip();
    IMPORT virtual void NotifyArchGroupDestroyed(u16);

    IMPORT static CELightEquip* cast(CEquip*);
    IMPORT static const CELightEquip* cast(const CEquip*);

    IMPORT CELightEquip(const CELightEquip&);
    IMPORT CELightEquip(CEqObj*, u16, const Archetype::Light*, bool);
    IMPORT const Archetype::Light* LightArch() const;
};