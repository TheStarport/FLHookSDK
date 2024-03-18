#pragma once
#include "../../../FLCoreDefs.hpp"

class IMPORT CECargoPod : public CAttachedEquip
{
    public:
    virtual ~CECargoPod();
    virtual bool IsLootable() const;
    virtual void Destroy();

    static CECargoPod* cast(CEquip*);
    static const CECargoPod* cast(const CEquip*);

    CECargoPod(const CECargoPod&);
    CECargoPod(CEqObj*, unsigned short, const Archetype::CargoPod*, bool);
    void EmptyPod();
    void FillPod(CECargo*);
    const CECargo* GetContents() const;
};