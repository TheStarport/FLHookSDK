#pragma once

#include "../../../PhySys/Controller.hpp"

class CStrafeEngine;
class CNudgeEngine;
class CSteering;
class CPlayerGroup;
struct CShip : public CEqObj, public PhySys::Controller
{
    public:
        struct IMPORT CreateParms
        {
                CreateParms();
                CreateParms& operator=(const CreateParms&);

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        IMPORT static const float JETTISON_CLEARANCE_TIME;

        IMPORT virtual ~CShip();

        IMPORT virtual void do_simulation_controller(IVP_Event_Sim*, IVP_U_Vector<IVP_Core>*);

        IMPORT virtual int update(float, unsigned int);
        IMPORT virtual void disable_controllers();
        IMPORT virtual void enable_controllers();
        IMPORT virtual unsigned int get_name() const;
        IMPORT virtual void init_physics(const Vector&, const Vector&);
        IMPORT virtual void flush_animations();
        IMPORT virtual CEquip* alloc_equip(unsigned short, Archetype::Equipment*, bool);
        IMPORT virtual void init(const CreateParms&); // 268

        IMPORT CShip(const CShip&);
        IMPORT CShip();
        IMPORT const Archetype::Ship* shiparch() const;
        IMPORT void VerifyTarget();
        IMPORT enum FORMATION_RTYPE add_follow_follower(IObjRW*);
        IMPORT FORMATION_RTYPE add_formation_follower(IObjRW*);
        IMPORT void airlock_in(const Vector&, const Matrix&);
        IMPORT bool any_thrusters_on() const;
        IMPORT bool check_formation_follower_status(float);
        IMPORT float close_bay();
        IMPORT bool generate_follow_offset(const IObjInspect*, Transform&) const;
        IMPORT int get_ammo_capacity_remaining(unsigned int) const;
        IMPORT int get_ammo_capacity_remaining(const Archetype::Equipment*) const;
        IMPORT float get_angular_distance_travelled(float, float, float) const;
        IMPORT float get_angular_distance_travelled(float, float, float, float) const;
        IMPORT Vector get_angular_drag() const;
        IMPORT float get_angular_speed_XY(float, float) const;
        IMPORT float get_angular_speed_Z(float) const;
        IMPORT const Vector& get_axis_throttle() const;
        IMPORT BayState get_bay_state() const;
        IMPORT float get_cargo_hold_remaining() const;
        IMPORT float get_distance_travelled(float, float, float, IObject::ThrustEquipType) const;
        IMPORT bool get_farthest_active_gun_range(float&) const;
        IMPORT IObjRW* get_follow_leader();
        IMPORT const Vector& get_follow_offset();
        IMPORT int get_formation_follower_count();
        IMPORT int get_formation_followers(IObjRW** const, unsigned int);
        IMPORT unsigned int get_group_name() const;
        IMPORT const struct ShipGunStats& get_gun_stats() const;
        IMPORT float get_initial_speed_to_coast_distance(float, bool) const;
        IMPORT float get_linear_drag() const;
        IMPORT float get_max_bank_angle() const;
        IMPORT float get_max_thrust_power() const;
        IMPORT Vector get_nudge_vec() const;
        IMPORT const unsigned short* get_pilot_name() const;
        IMPORT float get_projected_axis_throttle_XY(float) const;
        IMPORT float get_projected_axis_throttle_Z(float) const;
        IMPORT float get_projected_throttle(float, IObject::ThrustEquipType) const;
        IMPORT long get_renderable_subtarget() const;
        IMPORT int get_repair_kit_capacity_remaining() const;
        IMPORT int get_shield_battery_capacity_remaining() const;
        IMPORT int get_space_for_cargo_type(const Archetype::Equipment*) const;
        IMPORT float get_speed(float, IObject::ThrustEquipType) const;
        IMPORT int get_status(char*, int) const;
        IMPORT StrafeDir get_strafe_dir() const;
        IMPORT unsigned short get_sub_target() const;
        IMPORT IObjRW* get_target() const;
        IMPORT int get_targeted_enemy_count();
        IMPORT bool get_tgt_lead_fire_pos(Vector&) const;
        IMPORT bool get_tgt_lead_fire_pos(const IObjInspect*, Vector&) const;
        IMPORT float get_throttle() const;
        IMPORT float get_thrust_power() const;
        IMPORT float get_thrust_power_ratio() const;
        IMPORT float get_time_to_accelerate(float, float, float, IObject::ThrustEquipType) const;
        IMPORT float get_time_to_accelerate_angularly(float, float, float) const;
        IMPORT float get_time_to_accelerate_angularly(float, float, float, float) const;
        IMPORT unsigned int get_tradelane_entrance_ring();
        IMPORT unsigned int get_tradelane_exit_ring();
        IMPORT float get_tradelane_speed();
        IMPORT int go_tradelane(const IObjInspect*, const IObjInspect*, IObjRW*, bool, float);
        IMPORT bool is_cruise_active() const;
        IMPORT bool is_enemy(IObjInspect*);
        IMPORT bool is_jumping() const;
        IMPORT bool is_launching() const;
        IMPORT bool is_player() const;
        IMPORT bool is_using_tradelane() const;
        IMPORT void jump_in(IObjRW*, const Vector&, const Matrix&, float);
        IMPORT void launch(IObjRW*, CEqObj*, int);
        IMPORT bool leaving_system_update(unsigned int&);
        IMPORT IObjRW* next_enemy();
        IMPORT IObjRW* next_target(bool);
        IMPORT void notify_set_target(CShip*, bool);
        IMPORT float open_bay();
        IMPORT IObjRW* previous_enemy();
        IMPORT FORMATION_RTYPE remove_follow_follower(IObjRW*);
        IMPORT FORMATION_RTYPE remove_formation_follower(IObjRW*);
        IMPORT void request_exit_tradelane();
        IMPORT void set_angular_drag_factor(float);
        IMPORT void set_axis_throttle(const Vector&);
        IMPORT void set_follow_leader(IObjRW*);
        IMPORT void set_follow_offset(const Vector&);
        IMPORT void set_gun_stats_dirty();
        IMPORT void set_nudge_vec(const Vector&);
        IMPORT void set_strafe_dir(StrafeDir);
        IMPORT void set_sub_target(unsigned short);
        IMPORT void set_target(IObjRW*);
        IMPORT void set_throttle(float);
        IMPORT void set_thrust_power(float);
        IMPORT void set_tradelane_speed(float);
        IMPORT void stop_tradelane();
        IMPORT void use_tradelane(bool);
        IMPORT void collect_angular_force_components(unsigned int, float, float&, float&) const;
        IMPORT void collect_force_components(float, IObject::ThrustEquipType, float&, float&) const;
        IMPORT float get_distance_travelled(float, float, float, float, float) const;
        IMPORT float get_initial_speed_to_coast_distance(float, float, float) const;
        IMPORT float get_time_to_accelerate(float, float, float, float, float) const;
        IMPORT void recalculate_formation_speed();

        DWORD dunno5[2];                          // 106
        uint physicsPtr;                          // 108
        CPlayerGroup* playerGroup;                // 109
        DWORD dunno6;                             // 110
        IObjRW* followLeader2;                    // 111
        uint dunno16;                             // 112
        Vector followOffset2;                     // 113
        st6::vector<IObjRW*> followerVector;      // 116
        IObjRW* followLeader;                     // 120
        DWORD followLeaderID_unk;                 // 121
        Vector followOffset;                      // 122
        DWORD dunno8[3];                          // 125
        st6::vector<IObjRW*> targetedEnemyVector; // 128
        DWORD dunno11[3];                         // 132
        uint groupId;                             // 135
        IObjRW* target;                           // 136
        DWORD targetId_unk;                       // 137
        ushort subTargetId;                       // 138
        DWORD BayAnim;                            // 139
        CSteering* cSteering;                     // 140
        DWORD dunno13[6];                         // 141
        Vector axisThrottle;                      // 147
        CNudgeEngine* nudgeEngine;                // 150
        DWORD dunno10[6];                         // 151
        Vector nudgeVector;                       // 157
        CStrafeEngine* strafeEngine;              // 160
        DWORD dunno12[5];                         // 161
        StrafeDir strafeDir;                      // 166
        float throttle;                           // 167
        float thrustPower;                        // 168
        float maxThrustPower;                     // 169
        uint dunno14;                             // 170
        BayState bayState;                        // 171
        ActionDB* ActionDB;                       // 172
        uint dunnoCShip1;                         // 173
        float tradeLaneSpeed;                     // 174
        bool inTradeLane;                         // 175
        bool gunRelatedBool;                      // has active guns?
        float angularDragFactor;                  // 176
        uint gunStatsDirty;                       // 177
        uint activeGunCount1;                     // 178
        float rectHeight;                         // 179 no clue
        float maxActiveGunRange1;                 // 180
        uint activeGunCount2;                     // 181
        float maxActiveGunRange2;                 // 182 1-missiles 2-guns?
};