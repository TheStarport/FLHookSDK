#pragma once
#include "../../../../FLCoreDefs.hpp"

class CECounterMeasureDropper : public CELauncher
{
  public:
    IMPORT ~CECounterMeasureDropper() override;
    IMPORT bool Update(f32, u32) override;

    IMPORT static CECounterMeasureDropper* cast(CEquip*);
    IMPORT static const CECounterMeasureDropper* cast(const CEquip*);

    IMPORT CECounterMeasureDropper(const CECounterMeasureDropper&);
    IMPORT CECounterMeasureDropper(CEqObj*, u16, const Archetype::CounterMeasureDropper*, bool);
    IMPORT const Archetype::CounterMeasure* CounterMeasureArch();
    IMPORT const Archetype::CounterMeasureDropper* CounterMeasureDropperArch();
};
