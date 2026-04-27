#pragma once

#include "../../FLCoreDefs.hpp"
#include "DamageObjInfo.hpp"
#include "Root/Equipment.hpp"

namespace Archetype
{
    struct CollisionGroup
    {
        IMPORT CollisionGroup(const CollisionGroup&);
        IMPORT CollisionGroup();
        IMPORT ~CollisionGroup();
        IMPORT CollisionGroup& operator=(const CollisionGroup&);

        CollisionGroup* next;
        u16 id;
        CacheString name;
        unsigned type;
        unsigned hitPts;
        bool separable;
        bool destroyParent;
        bool rootHealthProxy;
        f32 parentImpulse;
        f32 mass;
        bool hasRotationInertia;
        Vector rotationInertia;
        unsigned separationExplosionArch;
        unsigned debrisTypeArch;
        f32 explosionResistance;
        DamageObjInfoList parentDmgObjInfoList;
        DamageObjInfoList groupDmgObjsInfoList;
        FuseIgnitionList FuseIgnitionList;
        EquipmentClass linkedEquipType;
        f32 linkedEquipDamage;
    };
}