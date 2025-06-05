#pragma once
#include "../FLCoreDefs.hpp"
#include "Archetype/CollisionGroup.hpp"
#include "Archetype/DamageObjInfo.hpp"
#include "Damage.hpp"
#include "Strings.hpp"

struct CObject;
namespace Archetype
{
    class FuseIgnitionList;
}
class CArchGroup
{
    public:
        IMPORT CArchGroup(const Archetype::CollisionGroup&, struct CEqObj* const);
        IMPORT ~CArchGroup();
        IMPORT const ID_String& DebrisTypeName() const;
        IMPORT bool DestroysParent() const;
        IMPORT float ExplosionGroupImpulse() const;
        IMPORT float ExplosionParentImpulse() const;
        IMPORT float ExplosionResistance() const;
        IMPORT const ID_String& ExplosionTypeName() const;
        IMPORT const Archetype::FuseIgnitionList& FuseIgnitions() const;
        IMPORT bool GetCenterOfMass(Vector&) const;
        IMPORT void GetCollisionGroupDesc(struct CollisionGroupDesc&) const;
        IMPORT unsigned int GetCollisionGroupType() const;
        IMPORT DamageEntry::SubObjFate GetFate() const;
        IMPORT float GetHitPoints() const;
        IMPORT unsigned short GetID() const;
        IMPORT float GetMaxHitPoints() const;
        IMPORT bool GetRadius(float&) const;
        IMPORT float GetRelativeHealth() const;
        IMPORT long GetRootIndex() const;
        IMPORT bool GetVelocity(Vector&) const;
        IMPORT const Archetype::DamageObjInfoList& GroupDamageObjs() const;
        IMPORT int InstDepthInGroup(long) const;
        IMPORT bool IsDead() const;
        IMPORT bool IsDestroyed() const;
        IMPORT bool IsInstInGroup(long) const;
        IMPORT bool IsRootHealthProxy() const;
        IMPORT void Kill(DamageEntry::SubObjFate);
        IMPORT float LinkedEquipmentDamage() const;
        IMPORT unsigned int LinkedEquipmentType() const;
        IMPORT const CacheString& Name() const;
        IMPORT const Archetype::DamageObjInfoList& ParentDamageObjs() const;
        IMPORT CObject* RetreiveDestroyedObj();
        IMPORT bool Separable() const;
        IMPORT void SetHitPoints(float);
        IMPORT void SetRelativeHealth(float);

    protected:
        IMPORT void AttachDamageObjs(CObject*, const Archetype::DamageObjInfoList&) const;
        IMPORT void Destroy();
        IMPORT void FreeDamageObjs();
        IMPORT void GetBoundingSphere(float&, Vector&) const;
        IMPORT void LoadDamageObjs();

    public:
        /* 0  */ CEqObj* owner;
        /* 1  */ Archetype::CollisionGroup* colGrp;
        /* 2  */ int rootIndex;
        /* 3  */ float hitPts;
        /* 4  */ uint dunno;
        /* 5  */ uint state;
        /* 6  */ DamageEntry::SubObjFate fate;
        /* 7  */ CObject* destroyedObj;
        /* 8  */ bool boundingSphereInitialized;
        /* 9  */ float boundingSphereRadius;
        /* 10 */ Vector boundingSphere;
};

class CArchGroupManager
{
    public:
        IMPORT CArchGroupManager(const CArchGroupManager&);
        IMPORT CArchGroupManager();
        IMPORT ~CArchGroupManager();
        IMPORT CArchGroupManager& operator=(const CArchGroupManager&);
        IMPORT bool AddNewArchGroup(CArchGroup*);
        IMPORT int Clear();
        IMPORT bool DeleteArchGroup(unsigned short);
        IMPORT bool DestroyDeadGroups();
        IMPORT bool DestroyGroups(const DamageList&, bool);
        IMPORT CArchGroup* FindByID(unsigned short);
        IMPORT const CArchGroup* FindByID(unsigned short) const;
        IMPORT CArchGroup* FindByName(const CacheString&);
        IMPORT const CArchGroup* FindByName(const CacheString&) const;
        IMPORT bool Init(CEqObj*);
        IMPORT unsigned short InstToSubObjID(long) const;
        IMPORT bool IsOnMap(unsigned short, bool) const;
        IMPORT int NumLiving() const;
        IMPORT int Size() const;
        IMPORT CArchGroup* Traverse(class CArchGrpTraverser&);
        IMPORT const CArchGroup* Traverse(CArchGrpTraverser&) const;

    protected:
        IMPORT void DestroyDeadGroup(CArchGroup&);
        IMPORT void DestroyLowerGroups(const CArchGroup&);
        IMPORT static const int MAX_GROUP_DEPTH;

    public:
        uint dunno0;  // 0
        bool dunno4;  // 4
        uint dunno8;  // 8
        uint dunno12; // 12
        uint dunno16; // 16
        char size;    // 20
        bool dunno21; // 21
};

class CArchGrpTraverser
{
    public:
        IMPORT CArchGrpTraverser();
        IMPORT CArchGrpTraverser& operator=(const CArchGrpTraverser&);
        IMPORT void Restart();

        unsigned char data[OBJECT_DATA_SIZE];
};

struct CollisionGroupDesc
{
        IMPORT CollisionGroupDesc& operator=(const CollisionGroupDesc&);
        IMPORT bool operator==(const CollisionGroupDesc&) const;
        IMPORT bool operator!=(const CollisionGroupDesc&) const;
        IMPORT bool operator<(const CollisionGroupDesc&) const;
        IMPORT bool operator>(const CollisionGroupDesc&) const;

        unsigned short id;
        float health;
};
