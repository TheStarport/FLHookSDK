#pragma once
#include "../../../FLCoreDefs.hpp"

#include <FLCore/Common/CEquip/CAttachedEquip.hpp>

class CEShield;
namespace Archetype
{
    struct ShieldGenerator;
}

class IMPORT CEShieldGenerator : public CAttachedEquip
{
  public:
    ~CEShieldGenerator() override;
    bool IsFunctioning() const override;
    bool Update(f32, u32) override;
    void Destroy() override;

    static CEShieldGenerator* cast(CEquip*);
    static const CEShieldGenerator* cast(const CEquip*);

    CEShieldGenerator(const CEShieldGenerator&);
    CEShieldGenerator(CEqObj*, u16, const Archetype::ShieldGenerator*, bool);
    const Archetype::ShieldGenerator* ShieldGenArch() const;
    bool IsLinked() const;
    void LinkShield(CEShield*);
    void UnLinkShield();

    CEShield* shield;
    u32 unk2;
    u32 unk3;
    f32 time;
    u32 unk5;
};
