#pragma once
#include "FLCore/FLCoreDefs.hpp"

class IMPORT CEShieldGenerator : public CAttachedEquip
{
    public:
    virtual ~CEShieldGenerator();
    virtual bool IsFunctioning() const;
    virtual bool Update(float, unsigned int);
    virtual void Destroy();

    static CEShieldGenerator* cast(CEquip*);
    static const CEShieldGenerator* cast(const CEquip*);

    CEShieldGenerator(const CEShieldGenerator&);
    CEShieldGenerator(CEqObj*, unsigned short, const Archetype::ShieldGenerator*, bool);
    const Archetype::ShieldGenerator* ShieldGenArch() const;
    bool IsLinked() const;
    void LinkShield(CEShield*);
    void UnLinkShield();
};