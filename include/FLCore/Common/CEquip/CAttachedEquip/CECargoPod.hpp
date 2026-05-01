#pragma once
#include "../../../FLCoreDefs.hpp"

class CECargo;
class IMPORT CECargoPod : public CAttachedEquip
{
  public:
    ~CECargoPod() override;
    bool IsLootable() const override;
    void Destroy() override;

    static CECargoPod* cast(CEquip*);
    static const CECargoPod* cast(const CEquip*);

    CECargoPod(const CECargoPod&);
    CECargoPod(CEqObj*, u16, const Archetype::CargoPod*, bool);
    void EmptyPod();
    void FillPod(CECargo*);
    const CECargo* GetContents() const;
};
