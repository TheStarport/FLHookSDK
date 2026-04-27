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
        IMPORT f32 ExplosionGroupImpulse() const;
        IMPORT f32 ExplosionParentImpulse() const;
        IMPORT f32 ExplosionResistance() const;
        IMPORT const ID_String& ExplosionTypeName() const;
        IMPORT const Archetype::FuseIgnitionList& FuseIgnitions() const;
        IMPORT bool GetCenterOfMass(Vector&) const;
        IMPORT void GetCollisionGroupDesc(struct CollisionGroupDesc&) const;
        IMPORT u32 GetCollisionGroupType() const;
        IMPORT DamageEntry::SubObjFate GetFate() const;
        IMPORT f32 GetHitPoints() const;
        IMPORT u16 GetID() const;
        IMPORT f32 GetMaxHitPoints() const;
        IMPORT bool GetRadius(f32&) const;
        IMPORT f32 GetRelativeHealth() const;
        IMPORT long GetRootIndex() const;
        IMPORT bool GetVelocity(Vector&) const;
        IMPORT const Archetype::DamageObjInfoList& GroupDamageObjs() const;
        IMPORT int InstDepthInGroup(long) const;
        IMPORT bool IsDead() const;
        IMPORT bool IsDestroyed() const;
        IMPORT bool IsInstInGroup(long) const;
        IMPORT bool IsRootHealthProxy() const;
        IMPORT void Kill(DamageEntry::SubObjFate);
        IMPORT f32 LinkedEquipmentDamage() const;
        IMPORT u32 LinkedEquipmentType() const;
        IMPORT const CacheString& Name() const;
        IMPORT const Archetype::DamageObjInfoList& ParentDamageObjs() const;
        IMPORT CObject* RetreiveDestroyedObj();
        IMPORT bool Separable() const;
        IMPORT void SetHitPoints(f32);
        IMPORT void SetRelativeHealth(f32);

    protected:
        IMPORT void AttachDamageObjs(CObject*, const Archetype::DamageObjInfoList&) const;
        IMPORT void Destroy();
        IMPORT void FreeDamageObjs();
        IMPORT void GetBoundingSphere(f32&, Vector&) const;
        IMPORT void LoadDamageObjs();

    public:
        /* 0  */ CEqObj* owner;
        /* 1  */ Archetype::CollisionGroup* colGrp;
        /* 2  */ long rootIndex;
        /* 3  */ f32 hitPts;
        /* 4  */ unsigned dunno;
        /* 5  */ unsigned state;
        /* 6  */ DamageEntry::SubObjFate fate;
        /* 7  */ CObject* destroyedObj;
        /* 8  */ bool boundingSphereInitialized;
        /* 9  */ f32 boundingSphereRadius;
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
        IMPORT bool DeleteArchGroup(u16);
        IMPORT bool DestroyDeadGroups();
        IMPORT bool DestroyGroups(const DamageList&, bool);
        IMPORT CArchGroup* FindByID(u16);
        IMPORT const CArchGroup* FindByID(u16) const;
        IMPORT CArchGroup* FindByName(const CacheString&);
        IMPORT const CArchGroup* FindByName(const CacheString&) const;
        IMPORT bool Init(CEqObj*);
        IMPORT u16 InstToSubObjID(long) const;
        IMPORT bool IsOnMap(u16, bool) const;
        IMPORT int NumLiving() const;
        IMPORT int Size() const;
        IMPORT CArchGroup* Traverse(class CArchGrpTraverser&);
        IMPORT const CArchGroup* Traverse(CArchGrpTraverser&) const;

    protected:
        IMPORT void DestroyDeadGroup(CArchGroup&);
        IMPORT void DestroyLowerGroups(const CArchGroup&);
        IMPORT static const int MAX_GROUP_DEPTH;

    public:
        unsigned dunno0;  // 0
        bool dunno4;  // 4
        unsigned dunno8;  // 8
        unsigned dunno12; // 12
        unsigned dunno16; // 16
        char size;    // 20
        bool dunno21; // 21
};

class CArchGrpTraverser
{
    public:
        IMPORT CArchGrpTraverser();
        IMPORT CArchGrpTraverser& operator=(const CArchGrpTraverser&);
        IMPORT void Restart();

        u8 data[OBJECT_DATA_SIZE];
};

struct CollisionGroupDesc
{
        IMPORT CollisionGroupDesc& operator=(const CollisionGroupDesc&);
        IMPORT bool operator==(const CollisionGroupDesc&) const;
        IMPORT bool operator!=(const CollisionGroupDesc&) const;
        IMPORT bool operator<(const CollisionGroupDesc&) const;
        IMPORT bool operator>(const CollisionGroupDesc&) const;

        u16 id;
        f32 health;
};
