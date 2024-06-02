#pragma once

#include "../../CSimple.hpp"
#include "FLCore/Common/CArchGroup.hpp"
#include "FLCore/Common/CEquip/CEquipManager.hpp"
#include "FLCore/Common/Damage.hpp"
#include "FLCore/Common/EquipDesc.hpp"
#include "FLCore/Common/MiscStructs.hpp"
#include "FLCore/Common/Unknown.hpp"

namespace Archetype
{
    struct EqObj;
    struct Equipment;
} // namespace Archetype
namespace PhySys
{
    struct CreateParms;
}

enum ObjActivateResult
{
};

struct CEqObj : CSimple
{
        struct IMPORT CreateParms
        {
                CreateParms();
                CreateParms& operator=(const CreateParms&);

                unsigned char data[OBJECT_DATA_SIZE];
        };

        IMPORT virtual ~CEqObj();                                                         // 56
        IMPORT virtual int update(float, unsigned int);                                   // 80
        IMPORT virtual void disable_controllers();                                        // 92
        IMPORT virtual void enable_controllers();                                         // 96
        IMPORT virtual void unmake_physical();                                            // 116
        IMPORT virtual void remake_physical(const PhySys::CreateParms&, float);           // 120
        IMPORT virtual unsigned int get_name() const;                                     // 136
        IMPORT virtual bool is_targetable() const;                                        // 140
        IMPORT virtual void connect(IObjDB*);                                             // 144
        IMPORT virtual void disconnect(IObjDB*);                                          // 148
        IMPORT virtual void init(const CreateParms&);                                     // 160
        IMPORT virtual void load_equip_and_cargo(const struct EquipDescVector&, bool);    // 164
        IMPORT virtual void clear_equip_and_cargo();                                      // 168
        IMPORT virtual void get_equip_desc_list(EquipDescVector&) const;                  // 172
        IMPORT virtual bool add_item(const EquipDesc&);                                   // 176
        IMPORT virtual ObjActivateResult activate(bool, unsigned int);                    // 180
        IMPORT virtual bool get_activate_state(st6::vector<bool, st6::allocator<bool>>&); // 184
        IMPORT virtual void disconnect(INotify*);                                         // 188
        IMPORT virtual void disconnect(IObjRW*);                                          // 192
        IMPORT virtual void connect(INotify*);                                            // 196
        IMPORT virtual void notify(INotify::Event, void*);                                // 200
        IMPORT virtual void flush_animations();                                           // 204
        IMPORT virtual float get_total_hit_pts() const;                                   // 208
        IMPORT virtual float get_total_max_hit_pts() const;                               // 212
        IMPORT virtual float get_total_relative_health() const;                           // 216
        IMPORT virtual bool get_sub_obj_velocity(unsigned short, Vector&) const;          // 220
        IMPORT virtual bool get_sub_obj_center_of_mass(unsigned short, Vector&) const;    // 224
        IMPORT virtual bool get_sub_obj_hit_pts(unsigned short, float&) const;            // 228
        IMPORT virtual bool set_sub_obj_hit_pts(unsigned short, float);                   // 232
        IMPORT virtual bool get_sub_obj_max_hit_pts(unsigned short, float&) const;        // 236
        IMPORT virtual bool get_sub_obj_relative_health(unsigned short, float&) const;    // 240
        IMPORT virtual unsigned short inst_to_subobj_id(long) const;                      // 244
        IMPORT virtual long sub_obj_id_to_inst(unsigned short) const;                     // 248
        IMPORT virtual void destroy_sub_objs(const DamageList&, bool);                    // 252
        IMPORT virtual int enumerate_sub_objs() const;                                    // 256
        IMPORT virtual CEquip* alloc_equip(unsigned short, Archetype::Equipment*, bool);  // 260
        IMPORT virtual void link_shields();                                               // 264

        struct IMPORT DockAnimInfo
        {
                DockAnimInfo();
                DockAnimInfo& operator=(const DockAnimInfo&);

                unsigned char data[OBJECT_DATA_SIZE];
        };

        IMPORT CEqObj(const CEqObj&);
        IMPORT CEqObj(Class);
        IMPORT void attaching_damaged_obj(const CacheString&);
        IMPORT float attitude_towards(const CEqObj*) const;
        IMPORT void attitude_towards_symmetrical(float&, const CEqObj*, float&) const;
        IMPORT void clear_arch_groups();
        IMPORT IBehaviorManager* create_behavior_interface(IObjRW*, int);
        IMPORT Archetype::EqObj* eqobjarch() const;
        IMPORT unsigned int get_base() const;
        IMPORT unsigned int get_base_name() const;
        IMPORT IBehaviorManager* get_behavior_interface();
        IMPORT float get_cloak_percentage() const;
        IMPORT void get_collision_group_description(st6::list<CollisionGroupDesc>&) const;
        IMPORT const unsigned int& get_dock_target() const;
        IMPORT bool get_explosion_dmg_bounding_sphere(float&, Vector&) const;
        IMPORT float get_max_power() const;
        IMPORT float get_power() const;
        IMPORT float get_power_ratio() const;
        IMPORT int get_vibe() const;
        IMPORT bool is_base() const;
        IMPORT int is_cloaked() const;
        IMPORT bool is_control_excluded(unsigned int) const;
        IMPORT bool is_damaged_obj_attached(const CacheString&) const;
        IMPORT bool is_dock() const;
        IMPORT bool launch_pos(Vector&, Matrix&, int) const;
        IMPORT void load_arch_groups(const st6::list<CollisionGroupDesc>&);
        IMPORT void set_control_exclusion(unsigned int);
        IMPORT void set_power(float);
        IMPORT bool sync_cargo(const EquipDescList&);
        IMPORT bool add_cargo_item(const EquipDesc&);
        IMPORT bool add_equipped_item(const EquipDesc&);
        IMPORT void compute_explosion_dmg_bounding_sphere(float&, Vector&) const;
        IMPORT void init_docking_points(unsigned int);
        IMPORT void update_docking_animations(float);

        CEquipManager equip_manager;                       // 57
        uint repVibe;                                      // 65
        Costume commCostume;                               // 66
        uint voiceId;                                      // 79
        float cloakPercentage;                             // 80
        CArchGroupManager archGroupManager;                // 81
        bool isDead;                                       // 87
        uint dockTargetId;                                 // 88
        IObjInspectImpl* dockTargetIObj;                   // 89
        uint iDunnoEqObj23;                                // 90
        bool boundingExplosionBool;                        // 91
        float boundingExplosionFloat;                      // 92
        Vector boundingExplosionVector;                    // 93
        st6::vector<DockAnimInfo> dockingAnimationsVector; // 96 could be st6::vector<IAnimation2>
        uint controlExcludedDunno;                         // 100
        IBehaviorManager* behaviorManager;                 // 101
        float power;                                       // 102
        float maxPower;                                    // 103
        uint iDunnoEqObj;                                  // 104 0xffffffff for all solars except those docking on lands you on a base, then it's 6?

    private:
        void destroy_equipment(const DamageList&, bool);
};
