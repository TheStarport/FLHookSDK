#pragma once

#include "../../FLCoreDefs.hpp"


struct IObjInspect
{
    struct CargoEnumerator
    {};
    struct SubtargetEnumerator
    {};
};

struct IObjInspectImpl
{
    public:
        IMPORT virtual const Vector& get_position() const;                                                                     // 0
        IMPORT virtual Vector get_velocity() const;                                                                            // 4
        IMPORT virtual Vector get_angular_velocity() const;                                                                    // 8
        IMPORT virtual const Matrix& get_orientation() const;                                                                  // 12
        IMPORT virtual const Transform& get_transform() const;                                                                 // 16
        IMPORT virtual Vector get_center_of_mass() const;                                                                      // 20
        IMPORT virtual int get_sub_obj_center_of_mass(unsigned short, Vector&) const;                                          // 24
        IMPORT virtual long get_index() const;                                                                                 // 28
        IMPORT virtual const unsigned int get_id() const;                                                                      // 32
        IMPORT virtual int get_good_id(unsigned int&) const;                                                                   // 36
        IMPORT virtual int get_archetype_extents(Vector&, Vector&) const;                                                      // 40
        IMPORT virtual int get_physical_radius(float&, Vector&) const;                                                         // 44
        IMPORT virtual float get_mass() const;                                                                                 // 48
        IMPORT virtual bool is_targetable() const;                                                                             // 52
        IMPORT virtual bool is_dying() const;                                                                                  // 56
        IMPORT virtual int get_status(float&) const;                                                                           // 60
        IMPORT virtual int get_status(float&, float&) const;                                                                   // 64
        IMPORT virtual int get_shield_status(float&, bool&) const;                                                             // 68
        IMPORT virtual int get_shield_status(float&, float&, bool&) const;                                                     // 72
        IMPORT virtual int get_throttle(float&) const;                                                                         // 76
        IMPORT virtual int get_axis_throttle(Vector&) const;                                                                   // 80
        IMPORT virtual int get_nudge_vec(Vector&) const;                                                                       // 84
        IMPORT virtual int get_strafe_dir(StrafeDir&) const;                                                                   // 88
        IMPORT virtual int is_cruise_active(bool&) const;                                                                      // 92
        IMPORT virtual int is_cruise_active(bool&, bool&) const;                                                               // 96
        IMPORT virtual int are_thrusters_active(bool&) const;                                                                  // 100
        IMPORT virtual int get_attitude_towards(float&, const IObjInspect*) const;                                             // 104
        IMPORT virtual int get_attitude_towards_symmetrical(float&, const IObjInspect*, float&) const;                         // 108
        IMPORT virtual int get_reputation(float&, const unsigned int&) const;                                                  // 112
        IMPORT virtual int get_target(IObjRW*&) const;                                                                         // 116
        IMPORT virtual int get_subtarget(unsigned short&) const;                                                               // 120
        IMPORT virtual int get_subtarget_center_of_mass(Vector&) const;                                                        // 124
        IMPORT virtual int get_rank(unsigned int&) const;                                                                      // 128
        IMPORT virtual int get_affiliation(unsigned int&) const;                                                               // 132
        IMPORT virtual int get_type(unsigned int&) const;                                                                      // 136
        IMPORT virtual int get_base(unsigned int&) const;                                                                      // 140
        IMPORT virtual int get_dock_target(unsigned int&) const;                                                               // 144
        IMPORT virtual int get_power(float&) const;                                                                            // 148
        IMPORT virtual int get_zone_props(unsigned long&) const;                                                               // 152
        IMPORT virtual float get_scanner_interference() const;                                                                 // 156
        IMPORT virtual int get_hold_left(float&) const;                                                                        // 160
        IMPORT virtual int enumerate_cargo(IObjInspect::CargoEnumerator*) const;                                               // 164
        IMPORT virtual int get_data(const void*&) const;                                                                       // 168
        IMPORT virtual int get_formation_offset(Vector&) const;                                                                // 172
        IMPORT virtual int get_formation_leader(IObjRW*&) const;                                                               // 176
        IMPORT virtual int get_follow_offset(Vector&) const;                                                                   // 180
        IMPORT virtual int get_follow_leader(IObjRW*&) const;                                                                  // 184
        IMPORT virtual bool is_player() const;                                                                                 // 188
        IMPORT virtual int get_hardpoint(const char*, Vector*, Matrix*) const;                                                 // 192
        IMPORT virtual bool has_dock_hardpoints() const;                                                                       // 196
        IMPORT virtual int get_dock_hardpoints(int, enum TERMINAL_TYPE*, Transform*, Transform*, Transform*, float*) const;    // 200
        IMPORT virtual float get_time_to_accelerate(float, float, float, IObject::ThrustEquipType) const;                      // 204
        IMPORT virtual float get_distance_travelled(float, float, float, IObject::ThrustEquipType) const;                      // 208
        IMPORT virtual float get_projected_throttle(float, IObject::ThrustEquipType) const;                                    // 212
        IMPORT virtual float get_speed(float, IObject::ThrustEquipType) const;                                                 // 216
        IMPORT virtual float get_initial_speed_to_coast_distance(float, bool) const;                                           // 220
        IMPORT virtual float get_time_to_accelerate_angularly(float, float, float) const;                                      // 224
        IMPORT virtual float get_time_to_accelerate_angularly(float, float, float, float) const;                               // 228
        IMPORT virtual float get_angular_distance_travelled(float, float, float) const;                                        // 232
        IMPORT virtual float get_angular_distance_travelled(float, float, float, float) const;                                 // 236
        IMPORT virtual float get_angular_speed_XY(float, float) const;                                                         // 240
        IMPORT virtual float get_angular_speed_Z(float) const;                                                                 // 244
        IMPORT virtual float get_projected_axis_throttle_XY(float) const;                                                      // 248
        IMPORT virtual float get_projected_axis_throttle_Z(float) const;                                                       // 252
        IMPORT virtual float get_max_bank_angle() const;                                                                       // 256
        IMPORT virtual int get_scanlist(const struct ScanList*&, unsigned int, bool) const;                                    // 260
        IMPORT virtual int get_tgt_lead_fire_pos(const unsigned short&, Vector&) const;                                        // 264
        IMPORT virtual int is_pointing_at(bool&, const unsigned short&, float) const;                                          // 268
        IMPORT virtual int can_point_at(bool&, const unsigned short&, const Vector&, float) const;                             // 272
        IMPORT virtual int find_equipment(unsigned short* const, unsigned int, unsigned int) const;                            // 276
        IMPORT virtual int get_equipment_status(struct EquipStatus&, const unsigned short&) const;                             // 280
        IMPORT virtual int get_equipment_val(struct EquipmentVal&, const unsigned short&, enum EquipmentValType, float) const; // 284
        IMPORT virtual int scan_cargo(IObjRW*, EquipDescVector&) const;                                                        // 288
        IMPORT virtual int enumerate_subtargets(IObjInspect::SubtargetEnumerator*) const;                                      // 292
        IMPORT virtual int get_lane_direction(const Transform&, bool*) const;                                                  // 296
        IMPORT virtual int get_ring_side(const Transform&, bool*) const;                                                       // 300
        IMPORT virtual int traverse_rings(unsigned int&, bool) const;                                                          // 304
        IMPORT virtual int is_using_tradelane(bool*) const;                                                                    // 308
        IMPORT virtual int get_lane_start(const IObjInspect*, const IObjInspect*&, Vector&, Vector&) const;                    // 312
        IMPORT virtual bool generate_follow_offset(const IObjInspect*, Transform&) const;                                      // 316
        IMPORT virtual int get_atmosphere_range(float&) const;                                                                 // 320
        IMPORT virtual int get_toughness() const;                                                                              // 324
        IMPORT virtual int get_behavior_id() const;                                                                            // 328
        IMPORT virtual int get_formation_followers(IObjRW** const, unsigned int) const;                                        // 332
        IMPORT virtual CObject* cobject() const;                                                                               // 336
};

struct IObjAffect
{
    virtual int set_throttle(float);                           // 0
    virtual int set_axis_throttle(const Vector&);              // 4
    virtual int set_nudge_vec(const Vector&);                  // 8
    virtual int set_strafe_dir(StrafeDir);                     // 12
    virtual int basewatcher_setpointer(IObjInspect*);          // 16
    virtual int basewatcher_removepointer(IObjInspect*);       // 20
    virtual FORMATION_RTYPE add_formation_follower(IObjRW*);   // 24
    virtual FORMATION_RTYPE remove_formation_follower(IObjRW*);// 28
    virtual int get_formation_follower_count();                // 32
    virtual int set_follow_leader(IObjRW*);                    // 36
    virtual int set_follow_offset(const Vector&);              // 40
    virtual FORMATION_RTYPE add_follow_follower(IObjRW*);      // 44
    virtual FORMATION_RTYPE remove_follow_follower(IObjRW*);   // 48
    virtual int fire_weapons(ushort startIndex, ushort endIndex, void* unk, void* unk2); // 52
    virtual int jettison_cargo(ushort sID, ushort amount, void* unused, void* unused2); // 56
    virtual int sub_6CE6D80(ushort sId, int, int);              // 60 something about Tractoring?
    virtual int sub_6CE6BA0(ushort sId, int, int);              // 64 something about Tractoring?
    virtual int set_gun_target(ushort gunSId, uint target, ushort targetSId, int flag); // 68
    virtual int set_target(IObjRW* target, ushort sId, int dunno); // 72
    virtual int sub_6CE70B0(ushort sId, int dunno, int flag);  // 76 something about strafing/thrusting
    virtual int sub_6D02410();                                 // 80 engine related, engage cruise?
    virtual int sub_6D02500();                                 // 84 activates thrusters?
    virtual int use_item(ushort sId, uint amount, int unused); // 88 sub_6CE7210
    virtual int request_event(uint eventType, uint requestTarget, uint param1, uint param2, uint dunno); // 92
    virtual int request_cancel(uint eventType, uint param1, uint param2); // 96
    virtual int sub_6D028C0();                                 // 100 go tradelane?
    virtual int sub_6D02880();                                 // 104 switch from one pair of tradelane to another midflight?
    virtual int sub_6CEF350();                                 // 108 null
    virtual int sub_6D02000();                                 // 112 unknown
    virtual int sub_6D02070(uint spaceObjId);                  // 116 sendmessage 0x26

    Watchable* watchable;
};

struct IObjDestructor
{
    virtual struct IObjInspectImpl* DestroyIObj(bool deallocate);
};













