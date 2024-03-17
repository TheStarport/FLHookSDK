#pragma once
#include "FLCore/FLCoreDefs.hpp"

class CETractor : public CInternalEquip
{
    public:
    IMPORT virtual ~CETractor();
    IMPORT virtual bool Update(float, unsigned int);

    IMPORT static CETractor* cast(CEquip*);
    IMPORT static const CETractor* cast(const CEquip*);

    IMPORT CETractor(const CETractor&);
    IMPORT CETractor(CShip*, unsigned short, const Archetype::Tractor*, bool);
    IMPORT const Archetype::Tractor* TractorArch() const;
    IMPORT enum TractorFailureCode AddTarget(struct CLoot*);
    IMPORT int CountActiveArms() const;
    IMPORT float GetRange() const;
    IMPORT Vector GetSourcePos() const;
    IMPORT const class TractorArm* GetTractorArm(unsigned int) const;
    IMPORT const st6::vector<TractorArm>& GetTractorArms() const;
    IMPORT void RemoveTarget(unsigned int);
    IMPORT TractorFailureCode VerifyTarget(const CLoot*) const;
    IMPORT bool CanSeeTarget(const CLoot*) const;
};