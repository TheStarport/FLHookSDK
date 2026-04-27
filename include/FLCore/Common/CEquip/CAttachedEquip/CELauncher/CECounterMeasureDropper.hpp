#pragma once
#include "../../../../FLCoreDefs.hpp"

class CECounterMeasureDropper : public CELauncher
{
    public:
    IMPORT virtual ~CECounterMeasureDropper();
    IMPORT virtual bool Update(f32, u32);

    IMPORT static CECounterMeasureDropper* cast(CEquip*);
    IMPORT static const CECounterMeasureDropper* cast(const CEquip*);

    IMPORT CECounterMeasureDropper(const CECounterMeasureDropper&);
    IMPORT CECounterMeasureDropper(CEqObj*, u16, const Archetype::CounterMeasureDropper*, bool);
    IMPORT const Archetype::CounterMeasure* CounterMeasureArch();
    IMPORT const Archetype::CounterMeasureDropper* CounterMeasureDropperArch();
};