#pragma once

#include "CObject.hpp"
#include "FLCore/Common/Enums.hpp"

class IObjDB;

struct CSimple : CObject
{
        struct IMPORT CreateParms
        {
                CreateParms();
                CreateParms& operator=(const CreateParms&);

                uint id;
                struct StarSystem* starSystem;
                uint ownerPlayer;
                float hitpts;
                uint dunno[20];
        };

        IMPORT virtual ~CSimple();                                           // 56
        IMPORT virtual void open(Archetype::Root*);                          // 76
        IMPORT virtual float get_physical_radius_r(Vector&) const;           // 100
        IMPORT virtual void unmake_physical();                               // 116
        IMPORT virtual void beam_object(const Vector&, const Matrix&, bool); // 124
        IMPORT virtual void init(const CreateParms&);                        // 128
        IMPORT virtual void cache_physical_props();                          // 132
        IMPORT virtual unsigned int get_name() const;                        // 136
        IMPORT virtual bool is_targetable() const;                           // 140
        IMPORT virtual void connect(IObjDB*);                                // 144
        IMPORT virtual void disconnect(IObjDB*);                             // 148
        IMPORT virtual void set_hit_pts(float);                              // 152
        IMPORT virtual void init_physics(const Vector&, const Vector&);      // 156

        IMPORT CSimple(const CSimple&);
        IMPORT CSimple(Class);
        IMPORT unsigned int GetOwnerPlayer() const;
        IMPORT void SetOwnerPlayer(unsigned int);
        IMPORT float get_hit_pts() const;
        IMPORT const unsigned int& get_id() const;
        IMPORT float get_max_hit_pts() const;
        IMPORT IObjDB* get_object_database() const;
        IMPORT float get_relative_health() const;
        IMPORT float get_scanner_interference() const;
        IMPORT unsigned int get_type() const;
        IMPORT void update_zones(float, unsigned int);

        uint dunnoCSimple;                  // 39
        uint dunnoTargetable;               // 40
        Universe::IZone* currentDamageZone; // 41
        float zoneDmgMultiplier;            // 42
        StarSystem* starSystem;             // 43
        Id id;                              // 44
        uint ownerPlayer;                   // 45
        float hitPoints;                    // 46
        uint dunnoCSimple4[0x5];            // 47
        Vector radiusCenter;                // 52
        float radiusCentered;               // 55
        ObjectType type;                    // 56
};
