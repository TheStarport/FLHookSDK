#pragma once
#include "../../../FLCoreDefs.hpp"

class CEAttachedFX : public CExternalEquip
{
    public:
    IMPORT virtual ~CEAttachedFX();
    IMPORT virtual void NotifyArchGroupDestroyed(u16);

    IMPORT static CEAttachedFX* cast(CEquip*);
    IMPORT static const CEAttachedFX* cast(const CEquip*);

    IMPORT CEAttachedFX(const CEAttachedFX&);
    IMPORT CEAttachedFX(CEqObj*, u16, const Archetype::AttachedFXEquip*, bool);
    IMPORT const Archetype::AttachedFXEquip* FXArch() const;
};