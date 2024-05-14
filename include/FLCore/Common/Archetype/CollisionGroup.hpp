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
        ushort id;
        CacheString name;
        uint type;
        uint hitPts;
        bool separable;
        bool destroyParent;
        bool rootHealthProxy;
        float parentImpulse;
        float mass;
        bool hasRotationInertia;
        Vector rotationInertia;
        uint separationExplosionArch;
        uint debrisTypeArch;
        float explosionResistance;
        DamageObjInfoList parentDmgObjInfoList;
        DamageObjInfoList groupDmgObjsInfoList;
        FuseIgnitionList FuseIgnitionList;
        EquipmentClass linkedEquipType;
        float linkedEquipDamage;
    };
}