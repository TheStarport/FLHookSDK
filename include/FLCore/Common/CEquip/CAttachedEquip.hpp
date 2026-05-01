#pragma once

#include "CExternalEquip.hpp"
#include "../Damage.hpp"

namespace Archetype
{
    struct Equipment;
    struct AttachedEquipment;
} // namespace Archetype

struct CObject;

class CAttachedEquip : public CExternalEquip
{
  public:
    IMPORT ~CAttachedEquip() override;
    IMPORT bool Update(f32, u32) override;
    IMPORT f32 GetHitPoints() const override;
    IMPORT void SetHitPoints(f32) override;
    IMPORT bool IsConnected() const override;
    IMPORT bool Connect(const char*) override;
    IMPORT bool GetVelocity(Vector&) const override;
    IMPORT bool GetCenterOfMass(Vector&) const override;
    IMPORT void Disconnect() override;
    IMPORT virtual int GetToughness() const;                        // 120
    IMPORT virtual bool GetRadius(f32&) const;                      // 124
    IMPORT virtual bool IsInstOnEquip(long) const;                  // 128
    IMPORT virtual long GetRootIndex() const;                       // 132
    IMPORT virtual void SetFate(DamageEntry::SubObjFate);           // 136
    IMPORT virtual void ComputeBoundingSphere(f32&, Vector&) const; // 140

    IMPORT static CAttachedEquip* cast(CEquip*);
    IMPORT static const CAttachedEquip* cast(const CEquip*);

    IMPORT CAttachedEquip(const CAttachedEquip&);
    IMPORT CAttachedEquip(u32, CEqObj*, u16, const Archetype::Equipment*, bool);
    IMPORT const Archetype::AttachedEquipment* AttachedEquipArch() const;
    IMPORT CObject* GetPhysicsOwner() const;
    IMPORT CObject* RetrieveDebrisObject();

  public:
    /* 10 */ void* physicsPtr; // either CPhysAttachment::`vftable' or CNonPhysAttachment::`vftable'
    /* 11 */ unsigned debrisObject;
    /* 12 */ f32 hitPts;
    /* 13 */ DamageEntry::SubObjFate fate;
    /* 14 */ bool isBoundingSphereInitialized;
    /* 15 */ f32 boundingSphereRadius;
    /* 16-19 */ Vector boundingSphere;
};
