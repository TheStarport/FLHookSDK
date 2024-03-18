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
        unsigned char data[OBJECT_DATA_SIZE];
    };

    IMPORT virtual ~CLoot();
    IMPORT virtual int update(float, unsigned int);
    IMPORT virtual unsigned int get_name() const;
    IMPORT virtual void set_hit_pts(float);
    IMPORT virtual void init_physics(const Vector&, const Vector&);
    IMPORT virtual void init(const CreateParms&);

    IMPORT Archetype::Equipment* container_arch() const;
    IMPORT Archetype::Equipment* contents_arch() const;

    IMPORT CLoot(const CLoot&);
    IMPORT CLoot(Class);
    IMPORT bool can_ai_tractor() const;
    IMPORT float get_contents_hit_pts() const;
    IMPORT unsigned int get_owner() const;
    IMPORT unsigned int get_units() const;
    IMPORT float get_volume() const;
    IMPORT bool is_loot_temporary() const;
    IMPORT void set_contents_hit_pts(float);
    IMPORT void set_units(unsigned int);

    uint ownerId;                       // 57
    uint name;                          // 58 data type unknown, fetched with get_name()
    Archetype::Equipment* contentsArch; // 59
    uint unitCount;                     // 60
    float contentsHitPts;               // 61
    float lootOwnerSafeTime;            // 62
    bool canAITractor;                  // 63
    bool isTemporary;
    uint dunnoCLoot; // 64 doesn't seem to be actually used
};