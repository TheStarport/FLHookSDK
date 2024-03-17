#pragma once
#include "../../../FLCoreDefs.hpp"

namespace Archetype
{
    struct EqObj : Root
    {
        IMPORT EqObj(const EqObj&);
        IMPORT EqObj(IClObj*);
        IMPORT virtual ~EqObj();
        IMPORT const EqObj& operator=(const EqObj&);
        IMPORT bool dock_terminal_valid(int) const;
        IMPORT const struct CollisionGroup* get_group_by_id(unsigned short) const;
        IMPORT const CollisionGroup* get_group_by_name(const CacheString&) const;
        IMPORT bool get_undamaged_collision_group_list(st6::list<CollisionGroupDesc>&) const;
        IMPORT bool traverse_groups(const CollisionGroup*&) const;

        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 23 */ CollisionGroup* collisionGroup;
        /* 24 */ ushort equipmentIdCounter;
        /* 25 */ uint dunno2;
        /* 26 */ uint dunno3;
        /* 27 */ uint dunno4; // something to do with shield link
        /* 28 */ uint dunno5;
        /* 29 */ uint dunno6;
        /* 30 */ uint dunno7; // fuses?
        /* 31 */ uint dunno9; // fuses?
        /* 32 */ bool isNomad;
        bool dockingCamera;
        /* 33-36 */ st6::vector<DockHardpointInfo> dockInfo;
    };
}
