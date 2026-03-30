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
        unsigned short id;
        CacheString name;
        unsigned type;
        unsigned hitPts;
        bool separable;
        bool destroyParent;
        bool rootHealthProxy;
        float parentImpulse;
        float mass;
        bool hasRotationInertia;
        Vector rotationInertia;
        unsigned separationExplosionArch;
        unsigned debrisTypeArch;
        float explosionResistance;
        DamageObjInfoList parentDmgObjInfoList;
        DamageObjInfoList groupDmgObjsInfoList;
        FuseIgnitionList FuseIgnitionList;
        EquipmentClass linkedEquipType;
        float linkedEquipDamage;
    };
}