#pragma once

#include "CObject.hpp"
#include <FLCore/Common/Enums.hpp>

class IObjDB;
class StarSystem;
namespace Universe
{
    struct IZone;
}

struct CSimple : CObject
{
        struct IMPORT CreateParms
        {
                CreateParms();
                CreateParms& operator=(const CreateParms&);

                unsigned id;
                StarSystem* starSystem;
                unsigned ownerPlayer;
                f32 hitpts;
                unsigned dunno[20];
        };

        IMPORT virtual ~CSimple();                                           // 56
        IMPORT virtual void open(Archetype::Root*);                          // 76
        IMPORT virtual f32 get_physical_radius_r(Vector&) const;           // 100
        IMPORT virtual void unmake_physical();                               // 116
        IMPORT virtual void beam_object(const Vector&, const Matrix&, bool); // 124
        IMPORT virtual void init(const CreateParms&);                        // 128
        IMPORT virtual void cache_physical_props();                          // 132
        IMPORT virtual u32 get_name() const;                        // 136
        IMPORT virtual bool is_targetable() const;                           // 140
        IMPORT virtual void connect(IObjDB*);                                // 144
        IMPORT virtual void disconnect(IObjDB*);                             // 148
        IMPORT virtual void set_hit_pts(f32);                              // 152
        IMPORT virtual void init_physics(const Vector&, const Vector&);      // 156

        IMPORT CSimple(const CSimple&);
        IMPORT CSimple(Class);
        IMPORT u32 GetOwnerPlayer() const;
        IMPORT void SetOwnerPlayer(u32);
        IMPORT f32 get_hit_pts() const;
        IMPORT const u32& get_id() const;
        IMPORT f32 get_max_hit_pts() const;
        IMPORT IObjDB* get_object_database() const;
        IMPORT f32 get_relative_health() const;
        IMPORT f32 get_scanner_interference() const;
        IMPORT u32 get_type() const;
        IMPORT void update_zones(f32, u32);

        unsigned dunnoCSimple;                  // 39
        unsigned dunnoTargetable;               // 40
        Universe::IZone* currentDamageZone; // 41
        f32 zoneDmgMultiplier;            // 42
        StarSystem* starSystem;             // 43
        unsigned id;                            // 44
        unsigned ownerPlayer;                   // 45
        f32 hitPoints;                    // 46
        unsigned dunnoCSimple4[0x5];            // 47
        Vector radiusCenter;                // 52
        f32 radiusCentered;               // 55
        ObjectType type;                    // 56
};
