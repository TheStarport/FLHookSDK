#pragma once
#include "../../../FLCoreDefs.hpp"

class CECloakingDevice : public CExternalEquip
{
    public:
    IMPORT virtual ~CECloakingDevice();
    IMPORT virtual bool Update(f32, u32);
    IMPORT virtual bool Activate(bool);

    IMPORT static CECloakingDevice* cast(CEquip*);
    IMPORT static const CECloakingDevice* cast(const CEquip*);

    IMPORT CECloakingDevice(const CECloakingDevice&);
    IMPORT CECloakingDevice(CEqObj*, u16, const Archetype::CloakingDevice*, bool);
    IMPORT const Archetype::CloakingDevice* CloakArch() const;
    IMPORT f32 cloak_percent() const;
};