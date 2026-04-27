#pragma once
#include "../../../FLCoreDefs.hpp"

struct CShip;
class CETractor : public CInternalEquip
{
    public:
    IMPORT virtual ~CETractor();
    IMPORT virtual bool Update(f32, u32);

    IMPORT static CETractor* cast(CEquip*);
    IMPORT static const CETractor* cast(const CEquip*);

    IMPORT CETractor(const CETractor&);
    IMPORT CETractor(CShip*, u16, const Archetype::Tractor*, bool);
    IMPORT const Archetype::Tractor* TractorArch() const;
    IMPORT enum TractorFailureCode AddTarget(struct CLoot*);
    IMPORT int CountActiveArms() const;
    IMPORT f32 GetRange() const;
    IMPORT Vector GetSourcePos() const;
    IMPORT const class TractorArm* GetTractorArm(u32) const;
    IMPORT const st6::vector<TractorArm>& GetTractorArms() const;
    IMPORT void RemoveTarget(u32);
    IMPORT TractorFailureCode VerifyTarget(const CLoot*) const;
    IMPORT bool CanSeeTarget(const CLoot*) const;
};