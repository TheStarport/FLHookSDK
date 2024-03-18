#pragma once
#include "../../FLCoreDefs.hpp"

class CEInternalFX : public CEquip
{
    public:
    IMPORT virtual ~CEInternalFX();
    IMPORT virtual void Destroy();

    IMPORT static CEInternalFX* cast(CEquip*);
    IMPORT static const CEInternalFX* cast(const CEquip*);

    IMPORT CEInternalFX(const CEInternalFX&);
    IMPORT CEInternalFX(CEqObj*, unsigned short, const Archetype::InternalFXEquip*, bool);
    IMPORT const Archetype::InternalFXEquip* InternalFXArch() const;
};