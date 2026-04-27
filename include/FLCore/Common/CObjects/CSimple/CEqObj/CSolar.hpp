#pragma once

#include "CEqObj.hpp"

struct CSolar : public CEqObj
{
    public:
        struct IMPORT CreateParms
        {
                CreateParms();
                CreateParms& operator=(const CreateParms&);

            public:
                unsigned hash;
                f32 dunno[3]; // (~0, 0, -1) in f32 consistently
                Vector pos;
                Matrix orientation;
                int dunno1[3];
                Vector spin;
                int dunno2;

                unsigned base;
                unsigned hash2; // rep group? (otherwise it's the hash)
                Costume costume;
                int voiceId;
                int dunnoLoadout[4];
                // class st6::list<struct CollisionGroupDesc> collision;
                int dunno3[3];
                unsigned idString;
                unsigned visit;
                unsigned parent;
                unsigned destructible;
                // 1, 2, 3 = related to loadouts
                // 4 = class st6::list<struct CollisionGroupDesc> &
                // 7 = ID_String of solar (same as Hash)
                // 8 = visit (only last byte used)
                // 9 = id of parent
                // 10 = destructible (only last byte used)
                unsigned destSystem;
                unsigned destGate;
                unsigned prevRing;
                unsigned nextRing;
                unsigned tradelaneSpaceName;
                f32 atmosphereRange;
                unsigned dockWith;

                int dunnoAnim[3];
                // 1, 2 = something to do with animations
        };

        IMPORT virtual ~CSolar();
        IMPORT virtual void __stdcall set_velocity(long, const Vector&);
        IMPORT virtual void __stdcall set_angular_velocity(long, const Vector&);
        IMPORT virtual int update(f32, u32);
        IMPORT virtual Vector get_velocity() const;
        IMPORT virtual Vector get_angular_velocity() const;
        IMPORT virtual f32 get_mass() const;
        IMPORT virtual void cache_physical_props();
        IMPORT virtual void init_physics(const Vector&, const Vector&);
        IMPORT virtual ObjActivateResult activate(bool, u32);
        IMPORT virtual bool get_activate_state(st6::vector<bool, st6::allocator<bool>>&);
        IMPORT virtual void flush_animations();
        IMPORT virtual CEquip* alloc_equip(u16, Archetype::Equipment*, bool);

        IMPORT CSolar(const CSolar&);
        IMPORT CSolar(Class);
        IMPORT const Archetype::Solar* solararch() const;
        IMPORT const ID_String& GetParentNickname() const;
        IMPORT u8 GetVisitValue() const;
        IMPORT static bool ReadObj(INI_Reader&, Archetype::Solar*&, CreateParms&);
        IMPORT void SetVisitValue(u8);
        IMPORT f32 get_atmosphere_immersion(const Vector&) const;
        IMPORT f32 get_atmosphere_range() const;
        IMPORT const ID_String& get_dest_gate() const;
        IMPORT u32 get_dest_system() const;
        IMPORT const ID_String& get_loadout() const;
        IMPORT u32 get_next_trade_ring() const;
        IMPORT u32 get_prev_trade_ring() const;
        IMPORT u32 get_tradelane_space_name() const;
        IMPORT void init(const CreateParms&);
        IMPORT bool is_destructible() const;
        IMPORT bool is_dynamic() const;
        IMPORT bool is_lane_ring() const;
        IMPORT bool is_planetary() const;
        IMPORT bool is_system_gate() const;
        IMPORT bool is_waypoint() const;
        IMPORT void configure_system_gate(const char*);
        IMPORT void init_continual_anim(const char*);
        IMPORT void update_system_gate(f32);

        unsigned duplicatedSpaceID; // 105
        bool isDestructible;    // 106
        bool isDynamic;
        f32 atmosphereRange;            // 107
        unsigned solarLoadout_possiblyUnused; // 108
        unsigned jumpDestSystem;              // 109
        unsigned jumpDestObj;                 // 110
        bool animationBool;               // 111
        unsigned animationId;                 // 112
        unsigned animationStateEnum;          // 113
        f32 animDuration;               // 114
        CObject::Class CSolarClass;       // 115
        void* dunnoListPtr;     // 116 Pointer to two-directional list, individual size 0xC, so only 1 value being kept aside from the prev and next pointers
        unsigned dunnoListLength;   // 117 length of 116
        unsigned prevTradeLaneRing; // 118
        unsigned nextTradeLaneRing; // 119
        unsigned tradeLaneSpaceName_unused; // 120
        unsigned visitValue;                // 121
        unsigned parentNickname;            // 122
};