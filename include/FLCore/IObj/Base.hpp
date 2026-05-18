#pragma once
#include "../FLCoreDefs.hpp"

#include "../Common/CObjects/CSimple/CEqObj/CSolar.hpp"
#include "../Common/Enums.hpp"

struct ActionDB;
struct Watchable;
struct EquipStatus;
struct ScanList;
enum class FORMATION_RTYPE;
enum class TERMINAL_TYPE;
struct IObjRW;
struct IObjInspect
{
    struct CargoEnumerator
    {};
    struct SubtargetEnumerator
    {};
};

enum EquipmentValType
{
};

struct IObjInspectImpl
{
  public:
    IMPORT virtual const Vector& get_position() const;                                         // 0
    IMPORT virtual Vector get_velocity() const;                                                // 4
    IMPORT virtual Vector get_angular_velocity() const;                                        // 8
    IMPORT virtual const Matrix& get_orientation() const;                                      // 12
    IMPORT virtual const Transform& get_transform() const;                                     // 16
    IMPORT virtual Vector get_center_of_mass() const;                                          // 20
    IMPORT virtual int get_sub_obj_center_of_mass(u16, Vector&) const;                         // 24
    IMPORT virtual long get_index() const;                                                     // 28
    IMPORT virtual const u32 get_id() const;                                                   // 32
    IMPORT virtual int get_good_id(u32&) const;                                                // 36
    IMPORT virtual int get_archetype_extents(Vector&, Vector&) const;                          // 40
    IMPORT virtual int get_physical_radius(f32&, Vector&) const;                               // 44
    IMPORT virtual f32 get_mass() const;                                                       // 48
    IMPORT virtual bool is_targetable() const;                                                 // 52
    IMPORT virtual bool is_dying() const;                                                      // 56
    IMPORT virtual int get_status(f32&) const;                                                 // 60
    IMPORT virtual int get_status(f32&, f32&) const;                                           // 64
    IMPORT virtual int get_shield_status(f32&, bool&) const;                                   // 68
    IMPORT virtual int get_shield_status(f32&, f32&, bool&) const;                             // 72
    IMPORT virtual int get_throttle(f32&) const;                                               // 76
    IMPORT virtual int get_axis_throttle(Vector&) const;                                       // 80
    IMPORT virtual int get_nudge_vec(Vector&) const;                                           // 84
    IMPORT virtual int get_strafe_dir(StrafeDir&) const;                                       // 88
    IMPORT virtual int is_cruise_active(bool&) const;                                          // 92
    IMPORT virtual int is_cruise_active(bool&, bool&) const;                                   // 96
    IMPORT virtual int are_thrusters_active(bool&) const;                                      // 100
    IMPORT virtual int get_attitude_towards(f32&, const IObjInspect*) const;                   // 104
    IMPORT virtual int get_attitude_towards_symmetrical(f32&, const IObjInspect*, f32&) const; // 108
    IMPORT virtual int get_reputation(f32&, const u32&) const;                                 // 112
    IMPORT virtual int get_target(IObjRW*&) const;                                             // 116
    IMPORT virtual int get_subtarget(u16&) const;                                              // 120
    IMPORT virtual int get_subtarget_center_of_mass(Vector&) const;                            // 124
    IMPORT virtual int get_rank(u32&) const;                                                   // 128
    IMPORT virtual int get_affiliation(u32&) const;                                            // 132
    IMPORT virtual int get_type(u32&) const;                                                   // 136
    IMPORT virtual int get_base(u32&) const;                                                   // 140
    IMPORT virtual int get_dock_target(u32&) const;                                            // 144
    IMPORT virtual int get_power(f32&) const;                                                  // 148
    IMPORT virtual int get_zone_props(ulong&) const;                                           // 152
    IMPORT virtual f32 get_scanner_interference() const;                                       // 156
    IMPORT virtual int get_hold_left(f32&) const;                                              // 160
    IMPORT virtual int enumerate_cargo(IObjInspect::CargoEnumerator*) const;                   // 164
    IMPORT virtual int get_data(const void*&) const;                                           // 168
    IMPORT virtual int get_formation_offset(Vector&) const;                                    // 172
    IMPORT virtual int get_formation_leader(IObjRW*&) const;                                   // 176
    IMPORT virtual int get_follow_offset(Vector&) const;                                       // 180
    IMPORT virtual int get_follow_leader(IObjRW*&) const;                                      // 184
    IMPORT virtual bool is_player() const;                                                     // 188
    IMPORT virtual int get_hardpoint(const char*, Vector*, Matrix*) const;                     // 192
    IMPORT virtual bool has_dock_hardpoints() const;                                           // 196
    IMPORT virtual int get_dock_hardpoints(int dockIndex, TERMINAL_TYPE* dockType, Transform* dockMount,
                                           Transform* dockPoint1, Transform* dockPoint2,
                                           f32* dockRadius) const;                               // 200
    IMPORT virtual f32 get_time_to_accelerate(f32, f32, f32, IObject::ThrustEquipType) const;    // 204
    IMPORT virtual f32 get_distance_travelled(f32, f32, f32, IObject::ThrustEquipType) const;    // 208
    IMPORT virtual f32 get_projected_throttle(f32, IObject::ThrustEquipType) const;              // 212
    IMPORT virtual f32 get_speed(f32, IObject::ThrustEquipType) const;                           // 216
    IMPORT virtual f32 get_initial_speed_to_coast_distance(f32, bool) const;                     // 220
    IMPORT virtual f32 get_time_to_accelerate_angularly(f32, f32, f32) const;                    // 224
    IMPORT virtual f32 get_time_to_accelerate_angularly(f32, f32, f32, f32) const;               // 228
    IMPORT virtual f32 get_angular_distance_travelled(f32, f32, f32) const;                      // 232
    IMPORT virtual f32 get_angular_distance_travelled(f32, f32, f32, f32) const;                 // 236
    IMPORT virtual f32 get_angular_speed_XY(f32, f32) const;                                     // 240
    IMPORT virtual f32 get_angular_speed_Z(f32) const;                                           // 244
    IMPORT virtual f32 get_projected_axis_throttle_XY(f32) const;                                // 248
    IMPORT virtual f32 get_projected_axis_throttle_Z(f32) const;                                 // 252
    IMPORT virtual f32 get_max_bank_angle() const;                                               // 256
    IMPORT virtual int get_scanlist(const ScanList*&, u32 objectType, bool preserveCache) const; // 260
    IMPORT virtual int get_tgt_lead_fire_pos(const u16&, Vector&) const;                         // 264
    IMPORT virtual int is_pointing_at(bool&, const u16&, f32) const;                             // 268
    IMPORT virtual int can_point_at(bool&, const u16&, const Vector&, f32) const;                // 272
    IMPORT virtual int find_equipment(u16* const, u32, u32) const;                               // 276
    IMPORT virtual int get_equipment_status(EquipStatus&, const u16&) const;                     // 280
    IMPORT virtual int get_equipment_val(struct EquipmentVal&, const u16&, EquipmentValType,
                                         f32) const;                                                    // 284
    IMPORT virtual int scan_cargo(IObjRW*, EquipDescVector&) const;                                     // 288
    IMPORT virtual int enumerate_subtargets(IObjInspect::SubtargetEnumerator*) const;                   // 292
    IMPORT virtual int get_lane_direction(const Transform&, bool*) const;                               // 296
    IMPORT virtual int get_ring_side(const Transform&, bool*) const;                                    // 300
    IMPORT virtual int traverse_rings(u32&, bool) const;                                                // 304
    IMPORT virtual int is_using_tradelane(bool*) const;                                                 // 308
    IMPORT virtual int get_lane_start(const IObjInspect*, const IObjInspect*&, Vector&, Vector&) const; // 312
    IMPORT virtual bool generate_follow_offset(const IObjInspect*, Transform&) const;                   // 316
    IMPORT virtual int get_atmosphere_range(f32&) const;                                                // 320
    IMPORT virtual int get_toughness() const;                                                           // 324
    IMPORT virtual int get_behavior_id() const;                                                         // 328
    IMPORT virtual int get_formation_followers(IObjRW** const, u32) const;                              // 332
    IMPORT virtual CObject* cobject() const;                                                            // 336
};

// This VTable exists on the client, but all the functions are nullops (all return -3)
struct IObjAffect
{
    virtual int set_throttle(f32);                                                            // 0
    virtual int set_axis_throttle(const Vector&);                                             // 4
    virtual int set_nudge_vec(const Vector&);                                                 // 8
    virtual int set_strafe_dir(StrafeDir);                                                    // 12
    virtual int basewatcher_setpointer(IObjInspect*);                                         // 16
    virtual int basewatcher_removepointer(IObjInspect*);                                      // 20
    virtual FORMATION_RTYPE add_formation_follower(IObjRW*);                                  // 24
    virtual FORMATION_RTYPE remove_formation_follower(IObjRW*);                               // 28
    virtual int get_formation_follower_count();                                               // 32
    virtual int set_follow_leader(IObjRW*);                                                   // 36
    virtual int set_follow_offset(const Vector&);                                             // 40
    virtual FORMATION_RTYPE add_follow_follower(IObjRW*);                                     // 44
    virtual FORMATION_RTYPE remove_follow_follower(IObjRW*);                                  // 48
    virtual int fire_weapons(u16 startIndex, u16 endIndex, void* unk, void* unk2);            // 52
    virtual int jettison_cargo(u16 sID, u16 amount, void* unused);                            // 56
    virtual int tractor_all(u16 tractorSId, st6::vector<IObjRW*> tractorArray, int clientId); // 60
    virtual int tractor_single(u16 sId, IObjRW* loot, int clientId);                          // 64
    virtual int set_gun_target(u16 gunSId, unsigned target, u16 targetSId, int flag);         // 68
    virtual int set_target(IObjRW* target, u16 sId, int dunno);                               // 72
    virtual int toggle_item(u16& sId, bool newState, int dunno);                              // 76
    virtual int toggle_cruise(bool cruiseActive, bool disruptCruise, int dunno2);             // 80
    virtual int toggle_thrusters(bool dunno, bool newState);                                  // 84
    virtual int use_item(u16 sId, unsigned amount, int unused); // 88 sub_6CE7210
    virtual int request_event(unsigned eventType, unsigned requestTarget, unsigned param1, unsigned param2,
                              unsigned dunno);                                        // 92
    virtual int request_cancel(unsigned eventType, unsigned param1, unsigned param2); // 96
    virtual int go_tradelane(const IObjInspect* startRing, const IObjInspect* nextRing, IObjRW* jumpingIObj,
                             bool unk1,
                             f32 unk2); // 100
    virtual int stop_tradelane();       // 104 switch from one pair of tradelane to another midflight?
    virtual int sub_6CEF350();          // 108 null
    virtual int sub_6D02000();          // 112 unknown
    virtual int sub_6D02070(unsigned spaceObjId); // 116 sendmessage 0x26

    Watchable* watchable;
};

struct IObjDestructor
{
    virtual IObjInspectImpl* DestroyIObj(bool deallocate);
};

struct IObjRW : IObjInspectImpl, IObjAffect, IObjDestructor
{
    CSimple* csimple() { return reinterpret_cast<CSimple*>(cobject()); };
    static IObjRW* Cast(IObjInspectImpl* iobj)
    {
        if ((iobj->cobject()->objectClass & CObject::CSIMPLE_MASK) == CObject::CSIMPLE_MASK)
        {
            return reinterpret_cast<IObjRW*>(iobj);
        }
        return nullptr;
    }

    bool IsStaticSolar()
    {
        if (!cobj)
        {
            return false;
        }

        if (!(cobj->objectClass & CObject::CSOLAR_OBJECT))
        {
            return false;
        }

        return !reinterpret_cast<CSolar*>(cobj)->isDynamic;
    }

    CObject* cobj;
    IObjRW* next;
};

struct ClientGameObject : IObjRW
{
    // Return (collisionBitMask & 4) == 0; Only collide with certain things?
    virtual bool sub_524E20(); // 340
    // Return (collisionBitMask & 1) Collisions enabled?
    virtual bool sub_524E30();                       // 344
    virtual void enable_collisions(int unkBitField); // 348, sub_539C10
    // Return (collisionBitMask & 2) == 0; Only collide with certain things?
    virtual bool sub_524E40(); // 352
    // Modify collisionBitMask: collisionBitMask ^= (collisionBitMask ^ (2 * a2)) & 2;
    virtual void sub_539C40(int a2);                     // 356
    virtual void create_instance(Archetype::Root* arch); // 360, sub_53F2F0
    virtual bool nullopt0();                             // 364, sub_53F330

    // Does something with explosions, not sure
    virtual void sub_5426E0();                            // 368, sub_5426E0
    virtual void update(f32 delta);                       // 372, sub_53F610
    virtual f32 get_physical_radius_r(Vector&);           // 376, sub_539810
    virtual void sub_539820(int unk, int unk2, int unk3); // 380
    virtual void nullopt();                               // 384
    virtual void sub_539B40(int unk);                     // 388
    // Something to do with object textures, calls material pipeline
    virtual void sub_539980(int unk, int unk2, int unk3, int unk4, int unk5); // 392

    // Sets unk to equal dunnoFloat3, returns dunnoFloat2
    virtual float sub_524E50(float* unk); // 396
    // Set's dunnoFloat1-2-3 to 10.f, 0.f, 0.f
    virtual void sub_524E60();                                      // 400
    virtual void sub_53F690(int unk, int unk2, int unk3, int unk4); // 404
    // If NOT singleplayer, iterate list, call CObject->SetHitPts if sId is ROOT?
    virtual void sub_5474A0(EquipDescList list); // 408

    // Calls set hitpoints 0 on the CObject, passes destroy type to sub_53A820
    virtual void sub_547500(DestroyType destroyType); // 412
    virtual void nullopt2(const Vector&);             // 416
    virtual void nullopt3(uint, uint);                // 420
    virtual void nullopt4(uint, uint);                // 424

    // Will send packet via remoteserver / rpclocal. Returns cobject() on success
    virtual CObject* process_collision(Vector& impactPos, i32 u2, ClientGameObject* collidingObject,
                                       u16 sId); // 428, sub_53F790
    //
    virtual void sub_542870(Vector& pos);                 // 432, sub_542870
    virtual void sub_53A4C0(int unk, int unk2, int unk3); // 436
    virtual void nullopt5(uint);                          // 440
    virtual ObjectType get_object_type();                 // 444, sub_52E130
    virtual Matrix set_rotation_identity();               // 448, sub_5428A0

    u32 dunno1;
    void* unkObj; // referenced in sub_542870, unkObj+4 = st6::list<?>. Also referenced in sub_4FCEF0
    ActionDB* actionDb;
    u32 dunno2[4];
    float dunnoFloat1;
    float dunnoFloat2;
    float dunnoFloat3;
    void* unkThing;
    int collisionBitMask;
};

struct ServerGameObject : IObjRW
{
    virtual ObjectType get_object_type() const; // 340
    virtual bool ObjectDestroyed(
        DestroyType destroyType,
        unsigned killerId);   // NakedShipDestroyed                                      //344 sub_6CE8080
    virtual int Disconnect(); // 348 sub_6CE7C80
    virtual bool get_dunno_0x40();                            // 352 sub_6CEE6D0
    virtual int InstantiateCobject(Archetype::Root* archPtr); // 356 sub_6D01040
    virtual bool SetCObjectById(unsigned cobjId);             // 360 sub_6D010A0
    virtual void Update(f32 timeDelta);                       // 364 sub_6D01450
    virtual void sub_6D01A60();                               // 368 sub_6D01A60
    virtual int sub_6CEE810(void* PhySys_unk);                // 372 physics collsion handling?
    virtual void sub_6CEE980(int dunno);                      // 376 Behavior interface update
    virtual void sub_6CE9250(void* unk, DamageList*);         // 380
    virtual void process_munition_impact(MunitionImpactData* unk, DamageList*); // 384 sub_6CE9350
    virtual void process_all_explosion_damage(ExplosionDamageEvent*,
                                              DamageList*); // calls methods 508-520         //388
    virtual void apply_damage_list(DamageList*);            // 392 sub_6D01A10
    virtual bool get_dunno_0x41();                          // 396
    virtual void sub_6CEEFA0();                             // 400 sub_6CEEFA0
    virtual void sub_6CEF0F0();                             // 404 sub_6CEF0F0
    virtual bool is_player_vulnerable();                    // 408 sub_6CE61A0
    virtual bool is_invulnerable();                         // 412 sub_6CE61B0
    virtual f32 get_max_hp_loss();                          // 416 sub_6CE61C0
    virtual bool process_collision_unk(
        void*); // unknown data type, an object containing a IObjRW as 2nd element?? //420 sub_6CEE9F0
    virtual CArchGroup* sethp_unk(
        DamageList*, f32); // set relative hp to all eq and colgrps to provided f32?  //424 sub_6CEB210
    virtual int set_relative_health(f32 newHp); // 428
    virtual bool damage_hull(
        f32, DamageList*); // NakedDamageHit                                                 //432 sub_6CEA3A0
    virtual void apply_damage_entry(DamageEntry*); // 436 sub_6CEEF70
    virtual bool can_deal_damage(
        DamageList*); // invokes get_dunno_0x39 and 0x38                                   //440 sub_6CEF0B0

    int iDunnos_0x1C; // length of 0x1C
    f64 timer;
    StarSystem* starSystem; // has something to do with fuses
    byte bDunno_0x2C;
    void* pDunno_0x30;   // struct size: 20 bytes
    int iDunno_0x34;     // length of 0x30
    byte isInvulnerable; // not entirely sure on those two
    byte isPlayerVulnerable;
    f32 maxHpLoss;    // when invulnerable, allow HP to drop down to this percentage
    byte bDunno_0x40; // is alive? Used when fetching IObjRW via sub_6D00670
    byte bDunno_0x41;
    byte bAlign_0x42; // probably not used
    byte bAlign_0x43; // probably not used
    byte bDunno_0x44;
    void* pDunno_0x48; // struct size: 20 bytes
    int iDunno_0x4C;   // size of 0x48
    byte bDunno_0x50;
    int iDunnos_0x54;
};
