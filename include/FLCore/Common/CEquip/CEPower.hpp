#pragma once
#include "FLCore/FLCoreDefs.hpp"

class CEPower : public CEquip
{
    public:
    IMPORT virtual ~CEPower();
    IMPORT virtual bool Update(float, unsigned int);

    IMPORT static CEPower* cast(CEquip*);
    IMPORT static const CEPower* cast(const CEquip*);

    IMPORT CEPower(const CEPower&);
    IMPORT CEPower(CEqObj*, unsigned short, const Archetype::Power*, bool);

    IMPORT float GetCapacity() const;
    IMPORT float GetChargeRate() const;
    IMPORT float GetThrustCapacity() const;
    IMPORT float GetThrustChargeRate() const;
};