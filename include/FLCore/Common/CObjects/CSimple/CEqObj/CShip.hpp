#pragma once

#include "../../../PhySys/Controller.hpp"

#include "CEqObj.hpp"
#include "../../../PhySys/Controller/CNudgeEngine.hpp"
#include "../../../PhySys/Controller/CStrafeEngine.hpp"

class CStrafeEngine;
class CNudgeEngine;
class CSteering;
class CPlayerGroup;
struct IObjInspect;

enum class FORMATION_RTYPE
{
};

struct CShip : public CEqObj, public PhySys::Controller
{
    public:
        struct IMPORT CreateParms
        {
                CreateParms();
                CreateParms& operator=(const CreateParms&);

            public:
                u8 data[OBJECT_DATA_SIZE];
        };

        IMPORT static const f32 JETTISON_CLEARANCE_TIME;

        IMPORT virtual ~CShip();

        IMPORT virtual void do_simulation_controller(IVP_Event_Sim*, IVP_U_Vector<IVP_Core>*);

        IMPORT virtual int update(f32, u32);
        IMPORT virtual void disable_controllers();
        IMPORT virtual void enable_controllers();
        IMPORT virtual u32 get_name() const;
        IMPORT virtual void init_physics(const Vector&, const Vector&);
        IMPORT virtual void flush_animations();
        IMPORT virtual CEquip* alloc_equip(u16, Archetype::Equipment*, bool);
        IMPORT virtual void init(const CreateParms&); // 268

        IMPORT CShip(const CShip&);
        IMPORT CShip();
        IMPORT const Archetype::Ship* shiparch() const;
        IMPORT void VerifyTarget();
        IMPORT FORMATION_RTYPE add_follow_follower(IObjRW*);
        IMPORT FORMATION_RTYPE add_formation_follower(IObjRW*);
        IMPORT void airlock_in(const Vector&, const Matrix&);
        IMPORT bool any_thrusters_on() const;
        IMPORT bool check_formation_follower_status(f32);
        IMPORT f32 close_bay();
        IMPORT bool generate_follow_offset(const IObjInspect*, Transform&) const;
        IMPORT int get_ammo_capacity_remaining(u32) const;
        IMPORT int get_ammo_capacity_remaining(const Archetype::Equipment*) const;
        IMPORT f32 get_angular_distance_travelled(f32, f32, f32) const;
        IMPORT f32 get_angular_distance_travelled(f32, f32, f32, f32) const;
        IMPORT Vector get_angular_drag() const;
        IMPORT f32 get_angular_speed_XY(f32, f32) const;
        IMPORT f32 get_angular_speed_Z(f32) const;
        IMPORT const Vector& get_axis_throttle() const;
        IMPORT BayState get_bay_state() const;
        IMPORT f32 get_cargo_hold_remaining() const;
        IMPORT f32 get_distance_travelled(f32, f32, f32, IObject::ThrustEquipType) const;
        IMPORT bool get_farthest_active_gun_range(f32&) const;
        IMPORT IObjRW* get_follow_leader();
        IMPORT const Vector& get_follow_offset();
        IMPORT int get_formation_follower_count();
        IMPORT int get_formation_followers(IObjRW** const, u32);
        IMPORT u32 get_group_name() const;
        IMPORT const struct ShipGunStats& get_gun_stats() const;
        IMPORT f32 get_initial_speed_to_coast_distance(f32, bool) const;
        IMPORT f32 get_linear_drag() const;
        IMPORT f32 get_max_bank_angle() const;
        IMPORT f32 get_max_thrust_power() const;
        IMPORT Vector get_nudge_vec() const;
        IMPORT const u16* get_pilot_name() const;
        IMPORT f32 get_projected_axis_throttle_XY(f32) const;
        IMPORT f32 get_projected_axis_throttle_Z(f32) const;
        IMPORT f32 get_projected_throttle(f32, IObject::ThrustEquipType) const;
        IMPORT long get_renderable_subtarget() const;
        IMPORT int get_repair_kit_capacity_remaining() const;
        IMPORT int get_shield_battery_capacity_remaining() const;
        IMPORT int get_space_for_cargo_type(const Archetype::Equipment*) const;
        IMPORT f32 get_speed(f32, IObject::ThrustEquipType) const;
        IMPORT int get_status(char*, int) const;
        IMPORT StrafeDir get_strafe_dir() const;
        IMPORT u16 get_sub_target() const;
        IMPORT IObjRW* get_target() const;
        IMPORT int get_targeted_enemy_count();
        IMPORT bool get_tgt_lead_fire_pos(Vector&) const;
        IMPORT bool get_tgt_lead_fire_pos(const IObjInspect*, Vector&) const;
        IMPORT f32 get_throttle() const;
        IMPORT f32 get_thrust_power() const;
        IMPORT f32 get_thrust_power_ratio() const;
        IMPORT f32 get_time_to_accelerate(f32, f32, f32, IObject::ThrustEquipType) const;
        IMPORT f32 get_time_to_accelerate_angularly(f32, f32, f32) const;
        IMPORT f32 get_time_to_accelerate_angularly(f32, f32, f32, f32) const;
        IMPORT u32 get_tradelane_entrance_ring();
        IMPORT u32 get_tradelane_exit_ring();
        IMPORT f32 get_tradelane_speed();
        IMPORT int go_tradelane(const IObjInspect*, const IObjInspect*, IObjRW*, bool, f32);
        IMPORT bool is_cruise_active() const;
        IMPORT bool is_enemy(IObjInspect*);
        IMPORT bool is_jumping() const;
        IMPORT bool is_launching() const;
        IMPORT bool is_player() const;
        IMPORT bool is_using_tradelane() const;
        IMPORT void jump_in(IObjRW*, const Vector&, const Matrix&, f32);
        IMPORT void launch(IObjRW*, CEqObj*, int);
        IMPORT bool leaving_system_update(u32&);
        IMPORT IObjRW* next_enemy();
        IMPORT IObjRW* next_target(bool);
        IMPORT void notify_set_target(CShip*, bool);
        IMPORT f32 open_bay();
        IMPORT IObjRW* previous_enemy();
        IMPORT FORMATION_RTYPE remove_follow_follower(IObjRW*);
        IMPORT FORMATION_RTYPE remove_formation_follower(IObjRW*);
        IMPORT void request_exit_tradelane();
        IMPORT void set_angular_drag_factor(f32);
        IMPORT void set_axis_throttle(const Vector&);
        IMPORT void set_follow_leader(IObjRW*);
        IMPORT void set_follow_offset(const Vector&);
        IMPORT void set_gun_stats_dirty();
        IMPORT void set_nudge_vec(const Vector&);
        IMPORT void set_strafe_dir(StrafeDir);
        IMPORT void set_sub_target(u16);
        IMPORT void set_target(IObjRW*);
        IMPORT void set_throttle(f32);
        IMPORT void set_thrust_power(f32);
        IMPORT void set_tradelane_speed(f32);
        IMPORT void stop_tradelane();
        IMPORT void use_tradelane(bool);
        IMPORT void collect_angular_force_components(u32, f32, f32&, f32&) const;
        IMPORT void collect_force_components(f32, IObject::ThrustEquipType, f32&, f32&) const;
        IMPORT f32 get_distance_travelled(f32, f32, f32, f32, f32) const;
        IMPORT f32 get_initial_speed_to_coast_distance(f32, f32, f32) const;
        IMPORT f32 get_time_to_accelerate(f32, f32, f32, f32, f32) const;
        IMPORT void recalculate_formation_speed();

        ulong dunno5[2];                          // 106
        unsigned physicsPtr;                          // 108
        CPlayerGroup* playerGroup;                // 109
        ulong dunno6;                             // 110
        IObjRW* followLeader2;                    // 111
        unsigned dunno16;                             // 112
        Vector followOffset2;                     // 113
        st6::vector<IObjRW*> followerVector;      // 116
        IObjRW* followLeader;                     // 120
        ulong followLeaderID_unk;                 // 121
        Vector followOffset;                      // 122
        ulong dunno8[3];                          // 125
        st6::vector<IObjRW*> targetedEnemyVector; // 128
        ulong dunno11[3];                         // 132
        unsigned groupId;                             // 135
        IObjRW* target;                           // 136
        ulong targetId_unk;                       // 137
        u16 subTargetId;                       // 138
        ulong BayAnim;                            // 139
        CSteering* cSteering;                     // 140
        ulong dunno13[6];                         // 141
        Vector axisThrottle;                      // 147
        CNudgeEngine nudgeEngine;                // 150
        CStrafeEngine strafeEngine;               // 160
        f32 throttle;                           // 167
        f32 thrustPower;                        // 168
        f32 maxThrustPower;                     // 169
        unsigned dunno14;                             // 170
        BayState bayState;                        // 171
        ActionDB* ActionDB;                       // 172
        unsigned dunnoCShip1;                         // 173
        f32 tradeLaneSpeed;                     // 174
        bool inTradeLane;                         // 175
        bool gunRelatedBool;                      // has active guns?
        f32 angularDragFactor;                  // 176
        bool gunStatsDirty;                       // 177
        ShipGunStats shipGunStats;                // 178
};
