#pragma once
#include "../../FLCoreDefs.hpp"

class CEInternalFX : public CEquip
{
  public:
    IMPORT ~CEInternalFX() override;
    IMPORT void Destroy() override;

    IMPORT static CEInternalFX* cast(CEquip*);
    IMPORT static const CEInternalFX* cast(const CEquip*);

    IMPORT CEInternalFX(const CEInternalFX&);
    IMPORT CEInternalFX(CEqObj*, u16, const Archetype::InternalFXEquip*, bool);
    IMPORT const Archetype::InternalFXEquip* InternalFXArch() const;
};
