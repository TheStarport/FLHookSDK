#pragma once
#include "../../../../FLCoreDefs.hpp"

class CECounterMeasureDropper : public CELauncher
{
    public:
    IMPORT virtual ~CECounterMeasureDropper();
    IMPORT virtual bool Update(float, unsigned int);

    IMPORT static CECounterMeasureDropper* cast(CEquip*);
    IMPORT static const CECounterMeasureDropper* cast(const CEquip*);

    IMPORT CECounterMeasureDropper(const CECounterMeasureDropper&);
    IMPORT CECounterMeasureDropper(CEqObj*, unsigned short, const Archetype::CounterMeasureDropper*, bool);
    IMPORT const Archetype::CounterMeasure* CounterMeasureArch();
    IMPORT const Archetype::CounterMeasureDropper* CounterMeasureDropperArch();
};