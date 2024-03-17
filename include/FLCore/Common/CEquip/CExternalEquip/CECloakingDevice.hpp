#pragma once
#include "FLCore/FLCoreDefs.hpp"

class CECloakingDevice : public CExternalEquip
{
    public:
    IMPORT virtual ~CECloakingDevice();
    IMPORT virtual bool Update(float, unsigned int);
    IMPORT virtual bool Activate(bool);

    IMPORT static CECloakingDevice* cast(CEquip*);
    IMPORT static const CECloakingDevice* cast(const CEquip*);

    IMPORT CECloakingDevice(const CECloakingDevice&);
    IMPORT CECloakingDevice(CEqObj*, unsigned short, const Archetype::CloakingDevice*, bool);
    IMPORT const Archetype::CloakingDevice* CloakArch() const;
    IMPORT float cloak_percent() const;
};