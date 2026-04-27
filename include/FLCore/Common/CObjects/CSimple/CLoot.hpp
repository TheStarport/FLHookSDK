#pragma once

#include "../../../FLCoreDefs.hpp"

struct CLoot : public CSimple
{
    public:
        struct IMPORT CreateParms
        {
                CreateParms();
                CreateParms& operator=(const CreateParms&);

            public:
                u8 data[OBJECT_DATA_SIZE];
        };

        IMPORT virtual ~CLoot();
        IMPORT virtual int update(f32, u32);
        IMPORT virtual u32 get_name() const;
        IMPORT virtual void set_hit_pts(f32);
        IMPORT virtual void init_physics(const Vector&, const Vector&);
        IMPORT virtual void init(const CreateParms&);

        IMPORT Archetype::Equipment* container_arch() const;
        IMPORT Archetype::Equipment* contents_arch() const;

        IMPORT CLoot(const CLoot&);
        IMPORT CLoot(Class);
        IMPORT bool can_ai_tractor() const;
        IMPORT f32 get_contents_hit_pts() const;
        IMPORT u32 get_owner() const;
        IMPORT u32 get_units() const;
        IMPORT f32 get_volume() const;
        IMPORT bool is_loot_temporary() const;
        IMPORT void set_contents_hit_pts(f32);
        IMPORT void set_units(u32);

        unsigned ownerId;                       // 57
        unsigned name;                          // 58 infocard number
        Archetype::Equipment* contentsArch; // 59
        unsigned unitCount;                     // 60
        f32 contentsHitPts;               // 61
        f32 lootOwnerSafeTime;            // 62
        bool canAITractor;                  // 63
        bool isTemporary;
        unsigned dunnoCLoot; // 64 doesn't seem to be actually used
};
