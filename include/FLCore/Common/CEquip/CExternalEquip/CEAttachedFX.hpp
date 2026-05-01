#pragma once
#include "../../../FLCoreDefs.hpp"

class CEAttachedFX : public CExternalEquip
{
  public:
    IMPORT ~CEAttachedFX() override;
    IMPORT void NotifyArchGroupDestroyed(u16) override;

    IMPORT static CEAttachedFX* cast(CEquip*);
    IMPORT static const CEAttachedFX* cast(const CEquip*);

    IMPORT CEAttachedFX(const CEAttachedFX&);
    IMPORT CEAttachedFX(CEqObj*, u16, const Archetype::AttachedFXEquip*, bool);
    IMPORT const Archetype::AttachedFXEquip* FXArch() const;
};
