#pragma once
#include "FLCore/FLCoreDefs.hpp"

class CAttachedEquip : public CExternalEquip
{
    public:
    IMPORT virtual ~CAttachedEquip();
    IMPORT virtual bool Update(float, unsigned int);
    IMPORT virtual float GetHitPoints() const;
    IMPORT virtual void SetHitPoints(float);
    IMPORT virtual bool IsConnected() const;
    IMPORT virtual bool Connect(const char*);
    IMPORT virtual bool GetVelocity(Vector&) const;
    IMPORT virtual bool GetCenterOMass(Vector&) const;
    IMPORT virtual void Disconnect();
    IMPORT virtual int GetToughness() const;                          // 120
    IMPORT virtual bool GetRadius(float&) const;                      // 124
    IMPORT virtual bool IsInstOnEquip(long) const;                    // 128
    IMPORT virtual long GetRootIndex() const;                         // 132
    IMPORT virtual void SetFate(DamageEntry::SubObjFate);             // 136
    IMPORT virtual void ComputeBoundingSphere(float&, Vector&) const; // 140

    IMPORT static CAttachedEquip* cast(CEquip*);
    IMPORT static const CAttachedEquip* cast(const CEquip*);

    IMPORT CAttachedEquip(const CAttachedEquip&);
    IMPORT CAttachedEquip(unsigned int, CEqObj*, unsigned short, const Archetype::Equipment*, bool);
    IMPORT const Archetype::AttachedEquipment* AttachedEquipArch() const;
    IMPORT CObject* GetPhysicsOwner() const;
    IMPORT CObject* RetrieveDebrisObject();

    public:
    /* 10 */ void* physicsPtr; // either CPhysAttachment::`vftable' or CNonPhysAttachment::`vftable'
    /* 11 */ CObject debrisObject;
    /* 12 */ float hitPts;
    /* 13 */ DamageEntry::SubObjFate fate;
    /* 14 */ bool isBoundingSphereInitialized;
    /* 15 */ float boundingSphereRadius;
    /* 16-19 */ Vector boundingSphere;
};