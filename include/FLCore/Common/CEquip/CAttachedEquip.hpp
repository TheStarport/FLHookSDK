#pragma once

#include "CExternalEquip.hpp"
#include "../Damage.hpp"

namespace Archetype
{
    struct Equipment;
    struct AttachedEquipment;
} // namespace Archetype

class CAttachedEquip : public CExternalEquip
{
    public:
        IMPORT virtual ~CAttachedEquip();
        IMPORT virtual bool Update(f32, u32);
        IMPORT virtual f32 GetHitPoints() const;
        IMPORT virtual void SetHitPoints(f32);
        IMPORT virtual bool IsConnected() const;
        IMPORT virtual bool Connect(const char*);
        IMPORT virtual bool GetVelocity(Vector&) const;
        IMPORT virtual bool GetCenterOfMass(Vector&) const;
        IMPORT virtual void Disconnect();
        IMPORT virtual int GetToughness() const;                          // 120
        IMPORT virtual bool GetRadius(f32&) const;                      // 124
        IMPORT virtual bool IsInstOnEquip(long) const;                    // 128
        IMPORT virtual long GetRootIndex() const;                         // 132
        IMPORT virtual void SetFate(DamageEntry::SubObjFate);             // 136
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
