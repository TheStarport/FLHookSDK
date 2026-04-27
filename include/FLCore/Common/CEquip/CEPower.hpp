#pragma once
#include "../../FLCoreDefs.hpp"

namespace Archetype
{
    struct Power;
}

class CEPower : public CEquip
{
    public:
        IMPORT virtual ~CEPower();
        IMPORT virtual bool Update(f32, u32);

        IMPORT static CEPower* cast(CEquip*);
        IMPORT static const CEPower* cast(const CEquip*);

        IMPORT CEPower(const CEPower&);
        IMPORT CEPower(CEqObj*, u16, const Archetype::Power*, bool);

        IMPORT f32 GetCapacity() const;
        IMPORT f32 GetChargeRate() const;
        IMPORT f32 GetThrustCapacity() const;
        IMPORT f32 GetThrustChargeRate() const;
};
