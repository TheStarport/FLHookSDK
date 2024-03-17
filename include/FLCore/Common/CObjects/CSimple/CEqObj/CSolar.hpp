#pragma once
#include "../../../FLCoreDefs.hpp"

struct CSolar : public CEqObj
{
    public:
        struct IMPORT CreateParms
        {
                CreateParms();
                CreateParms& operator=(const CreateParms&);

            public:
                uint hash;
                float dunno[3]; // (~0, 0, -1) in float consistently
                Vector pos;
                Matrix orientation;
                int dunno1[3];
                Vector spin;
                int dunno2;

                uint base;
                uint hash2; // rep group? (otherwise it's the hash)
                Costume costume;
                int voiceId;
                int dunnoLoadout[4];
                // class st6::list<struct CollisionGroupDesc> collision;
                int dunno3[3];
                uint idString;
                uint visit;
                uint parent;
                uint destructible;
                // 1, 2, 3 = related to loadouts
                // 4 = class st6::list<struct CollisionGroupDesc> &
                // 7 = ID_String of solar (same as Hash)
                // 8 = visit (only last byte used)
                // 9 = id of parent
                // 10 = destructible (only last byte used)
                uint destSystem;
                uint destGate;
                uint prevRing;
                uint nextRing;
                uint tradelaneSpaceName;
                float atmosphereRange;
                uint dockWith;

                int dunnoAnim[3];
                // 1, 2 = something to do with animations
        };

        IMPORT virtual ~CSolar();
        IMPORT virtual void __stdcall set_velocity(long, const Vector&);
        IMPORT virtual void __stdcall set_angular_velocity(long, const Vector&);
        IMPORT virtual int update(float, unsigned int);
        IMPORT virtual Vector get_velocity() const;
        IMPORT virtual Vector get_angular_velocity() const;
        IMPORT virtual float get_mass() const;
        IMPORT virtual void cache_physical_props();
        IMPORT virtual void init_physics(const Vector&, const Vector&);
        IMPORT virtual ObjActivateResult activate(bool, unsigned int);
        IMPORT virtual bool get_activate_state(st6::vector<bool, st6::allocator<bool>>&);
        IMPORT virtual void flush_animations();
        IMPORT virtual CEquip* alloc_equip(unsigned short, Archetype::Equipment*, bool);

        IMPORT CSolar(const CSolar&);
        IMPORT CSolar(Class);
        IMPORT const Archetype::Solar* solararch() const;
        IMPORT const ID_String& GetParentNickname() const;
        IMPORT unsigned char GetVisitValue() const;
        IMPORT static bool ReadObj(INI_Reader&, Archetype::Solar*&, CreateParms&);
        IMPORT void SetVisitValue(unsigned char);
        IMPORT float get_atmosphere_immersion(const Vector&) const;
        IMPORT float get_atmosphere_range() const;
        IMPORT const ID_String& get_dest_gate() const;
        IMPORT unsigned int get_dest_system() const;
        IMPORT const ID_String& get_loadout() const;
        IMPORT unsigned int get_next_trade_ring() const;
        IMPORT unsigned int get_prev_trade_ring() const;
        IMPORT unsigned int get_tradelane_space_name() const;
        IMPORT void init(const CreateParms&);
        IMPORT bool is_destructible() const;
        IMPORT bool is_dynamic() const;
        IMPORT bool is_lane_ring() const;
        IMPORT bool is_planetary() const;
        IMPORT bool is_system_gate() const;
        IMPORT bool is_waypoint() const;
        IMPORT void configure_system_gate(const char*);
        IMPORT void init_continual_anim(const char*);
        IMPORT void update_system_gate(float);

        uint duplicatedSpaceID; // 105
        bool isDestructible;    // 106
        bool isDynamic;
        float atmosphereRange;            // 107
        uint solarLoadout_possiblyUnused; // 108
        uint jumpDestSystem;              // 109
        uint jumpDestObj;                 // 110
        bool animationBool;               // 111
        uint animationId;                 // 112
        uint animationStateEnum;          // 113
        float animDuration;               // 114
        CObject::Class CSolarClass;       // 115
        void* dunnoListPtr;     // 116 Pointer to two-directional list, individual size 0xC, so only 1 value being kept aside from the prev and next pointers
        uint dunnoListLength;   // 117 length of 116
        uint prevTradeLaneRing; // 118
        uint nextTradeLaneRing; // 119
        uint tradeLaneSpaceName_unused; // 120
        uint visitValue;                // 121
        uint parentNickname;            // 122
};