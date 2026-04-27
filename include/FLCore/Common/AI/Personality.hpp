#pragma once
#include "../../FLCoreDefs.hpp"

namespace pub
{
    namespace AI
    {
        class Personality
        {
            public:
            struct EvadeDodgeUseStruct
            {
                    IMPORT EvadeDodgeUseStruct();
                    IMPORT EvadeDodgeUseStruct& operator=(const EvadeDodgeUseStruct&);

                    f32 evade_activate_range;                       // 500
                    f32 evade_dodge_style_weight[4];                // WAGGLE, WAGGLE_RANDOM, SLIDE, CORKSCREW, all 0
                    f32 evade_dodge_cone_angle;                     // 45
                    f32 evade_dodge_cone_angle_variance_percent;    // 0
                    f32 evade_dodge_waggle_axis_cone_angle;         // 0
                    f32 evade_dodge_roll_angle;                     // 0
                    f32 evade_dodge_interval_time;                  // 1
                    f32 evade_dodge_interval_time_variance_percent; // 0
                    f32 evade_dodge_distance;                       // 100
                    f32 evade_dodge_time;                           // 10
                    f32 evade_dodge_slide_throttle;                 // 0.6
                    f32 evade_dodge_turn_throttle;                  // 0.6
                    f32 evade_dodge_corkscrew_turn_throttle;        // 0.15
                    f32 evade_dodge_corkscrew_roll_throttle;        // 1
                    bool evade_dodge_corkscrew_roll_flip_direction;   // false
                    f32 evade_dodge_direction_weight[4];            // LEFT, RIGHT, UP, DOWN, all 0
            };

            struct EvadeBreakUseStruct
            {
                    IMPORT EvadeBreakUseStruct();
                    IMPORT EvadeBreakUseStruct& operator=(const EvadeBreakUseStruct&);

                    f32 evade_break_time;                               // 3
                    f32 evade_break_interval_time;                      // 100000
                    f32 evade_break_afterburner_delay;                  // 0
                    f32 evade_break_afterburner_delay_variance_percent; // 0
                    f32 evade_break_direction_weight[4];                // LEFT, RIGHT, UP, DOWN, all 0
                    f32 evade_break_roll_throttle;                      // 0
                    f32 evade_break_turn_throttle;                      // 1
                    f32 evade_break_style_weight[3];                    // SIDEWAYS, OUTRUN, REVERSE, all 0
                    f32 evade_break_attempt_reverse_time;               // 4
                    f32 evade_break_reverse_distance;                   // 150
            };

            struct BuzzHeadTowardUseStruct
            {
                    IMPORT BuzzHeadTowardUseStruct();
                    IMPORT BuzzHeadTowardUseStruct& operator=(const BuzzHeadTowardUseStruct&);

                    f32 buzz_max_time_to_head_away;                        // 4
                    f32 buzz_head_toward_style_weight[3];                  // STRAIGHT_TO, SLIDE, WAGGLE, all 0
                    f32 buzz_min_distance_to_head_toward;                  // 400
                    f32 buzz_min_distance_to_head_toward_variance_percent; // 1
                    f32 buzz_head_toward_engine_throttle;                  // 1
                    f32 buzz_head_toward_turn_throttle;                    // 1
                    f32 buzz_head_toward_roll_throttle;                    // 0
                    bool buzz_head_toward_roll_flip_direction;               // false
                    f32 buzz_dodge_direction_weight[4];                    // LEFT, RIGHT, UP, DOWN, all 0
                    f32 buzz_dodge_turn_throttle;                          // 1
                    f32 buzz_dodge_cone_angle;                             // 45
                    f32 buzz_dodge_cone_angle_variance_percent;            // 0
                    f32 buzz_dodge_waggle_axis_cone_angle;                 // 0
                    f32 buzz_dodge_roll_angle;                             // 0
                    f32 buzz_dodge_interval_time;                          // 2
                    f32 buzz_dodge_interval_time_variance_percent;         // 0
                    f32 buzz_slide_throttle;                               // 1
                    f32 buzz_slide_interval_time;                          // 2
                    f32 buzz_slide_interval_time_variance_percent;         // 0.4
            };

            struct BuzzPassByUseStruct
            {
                    IMPORT BuzzPassByUseStruct();
                    IMPORT BuzzPassByUseStruct& operator=(const BuzzPassByUseStruct&);

                    f32 buzz_pass_by_style_weight[3];    // STRAIGHT_BY, BREAK_AWAY, ENGINE_KILL, all 0
                    f32 buzz_distance_to_pass_by;        // 100
                    f32 buzz_pass_by_time;               // 3
                    bool buzz_drop_bomb_on_pass_by;        // false
                    f32 buzz_break_direction_weight[4];  // LEFT, RIGHT, UP, DOWN, all 0
                    f32 buzz_break_direction_cone_angle; // 0
                    f32 buzz_break_turn_throttle;        // 1
                    f32 buzz_pass_by_roll_throttle;      // 0
            };

            struct TrailUseStruct
            {
                    IMPORT TrailUseStruct();
                    IMPORT TrailUseStruct& operator=(const TrailUseStruct&);

                    f32 trail_lock_cone_angle;     // 30
                    f32 trail_break_time;          // 2.5
                    f32 trail_min_no_lock_time;    // 4
                    f32 trail_break_roll_throttle; // 0
                    bool trail_break_afterburner;    // false
                    f32 trail_max_turn_throttle;   // 1
                    f32 trail_distance;            // 150
            };

            struct StrafeUseStruct
            {
                    IMPORT StrafeUseStruct();
                    IMPORT StrafeUseStruct& operator=(const StrafeUseStruct&);

                    f32 strafe_run_away_distance; // 300
                    f32 strafe_attack_throttle;   // 1
                    f32 strafe_turn_throttle;     // 1
            };

            struct EngineKillUseStruct
            {
                    IMPORT EngineKillUseStruct();
                    IMPORT EngineKillUseStruct& operator=(const EngineKillUseStruct&);

                    f32 engine_kill_search_time;         // 6
                    f32 engine_kill_face_time;           // 3
                    f32 engine_kill_use_afterburner;     // 0
                    f32 engine_kill_afterburner_time;    // 0.5
                    f32 engine_kill_max_target_distance; // 700
            };

            struct RepairUseStruct
            {
                    IMPORT RepairUseStruct();
                    IMPORT RepairUseStruct& operator=(const RepairUseStruct&);

                    f32 use_shield_repair_pre_delay;         // 2
                    f32 use_shield_repair_at_damage_percent; // 0.5
                    f32 use_shield_repair_post_delay;        // 3
                    f32 use_hull_repair_pre_delay;           // 1
                    f32 use_hull_repair_at_damage_percent;   // 0.5
                    f32 use_hull_repair_post_delay;          // 1
            };

            struct GunUseStruct
            {
                    IMPORT GunUseStruct();
                    IMPORT GunUseStruct& operator=(const GunUseStruct&);

                    int fire_style;                                    // MULTIPLE = 0 (default), SINGLE = 1
                    f32 gun_fire_interval_time;                      // 0
                    f32 gun_fire_interval_variance_percent;          // 0.5
                    f32 gun_fire_burst_interval_time;                // 1.5
                    f32 gun_fire_burst_interval_variance_percent;    // 0.1
                    f32 gun_fire_no_burst_interval_time;             // 0.1
                    f32 gun_fire_accuracy_cone_angle;                // 0
                    f32 gun_fire_accuracy_power;                     // 1
                    f32 gun_fire_accuracy_power_npc;                 // 6
                    f32 gun_range_threshold;                         // 1
                    f32 gun_range_threshold_variance_percent;        // 0.2
                    f32 gun_target_point_switch_time;                // 1.5
                    f32 auto_turret_interval_time;                   // 0
                    f32 auto_turret_burst_interval_time;             // 1
                    f32 auto_turret_no_burst_interval_time;          // 0
                    f32 auto_turret_burst_interval_variance_percent; // 0.1
            };

            struct MineUseStruct
            {
                    IMPORT MineUseStruct();
                    IMPORT MineUseStruct& operator=(const MineUseStruct&);

                    f32 mine_launch_interval;   // 0
                    f32 mine_launch_cone_angle; // 22.5
                    f32 mine_launch_range;      // 400
            };

            struct MissileUseStruct
            {
                    IMPORT MissileUseStruct();
                    IMPORT MissileUseStruct& operator=(const MissileUseStruct&);

                    f32 missile_launch_range;                     // -1
                    bool missile_launch_allow_out_of_range;         // false
                    f32 missile_launch_interval_time;             // 5
                    f32 missile_launch_interval_variance_percent; // 0.4
                    f32 missile_launch_cone_angle;                // 22.5
                    f32 anti_cruise_missile_min_distance;         // 300
                    f32 anti_cruise_missile_max_distance;         // 2500
                    f32 anti_cruise_missile_pre_fire_delay;       // 2
                    f32 anti_cruise_missile_interval_time;        // 5
            };

            struct DamageReactionStruct
            {
                    IMPORT DamageReactionStruct();
                    IMPORT DamageReactionStruct& operator=(const DamageReactionStruct&);

                    f32 evade_break_damage_trigger_percent;      // 1
                    f32 evade_dodge_more_damage_trigger_percent; // 0.2
                    f32 drop_mines_damage_trigger_percent;       // 1
                    f32 drop_mines_damage_trigger_time;          // 1
                    f32 engine_kill_face_damage_trigger_percent; // 1
                    f32 engine_kill_face_damage_trigger_time;    // 2
                    f32 roll_damage_trigger_percent;             // 1
                    f32 roll_damage_trigger_time;                // 1
                    f32 afterburner_damage_trigger_percent;      // 1
                    f32 afterburner_damage_trigger_time;         // 1.5
                    f32 brake_reverse_damage_trigger_percent;    // 1
                    f32 fire_missiles_damage_trigger_percent;    // 1
                    f32 fire_missiles_damage_trigger_time;       // 0.5
                    f32 fire_guns_damage_trigger_percent;        // 1
                    f32 fire_guns_damage_trigger_time;           // 1
                    int _03C;                                      // not initialised
                    int _040;                                      // not initialised
            };

            struct MissileReactionStruct
            {
                    IMPORT MissileReactionStruct();
                    IMPORT MissileReactionStruct& operator=(const MissileReactionStruct&);

                    f32 evade_break_missile_reaction_time;     // 0
                    f32 evade_slide_missile_reaction_time;     // 0
                    f32 evade_afterburn_missile_reaction_time; // 0
                    f32 evade_missile_distance;                // 250
            };

            struct CountermeasureUseStruct
            {
                    IMPORT CountermeasureUseStruct();
                    IMPORT CountermeasureUseStruct& operator=(const CountermeasureUseStruct&);

                    f32 countermeasure_active_time;   // 1
                    f32 countermeasure_unactive_time; // 0
            };

            struct FormationUseStruct
            {
                    IMPORT FormationUseStruct();
                    IMPORT FormationUseStruct& operator=(const FormationUseStruct&);

                    f32 force_attack_formation_active_time;           // 1
                    f32 force_attack_formation_unactive_time;         // 0
                    f32 break_formation_damage_trigger_percent;       // 1
                    f32 break_formation_damage_trigger_time;          // 4
                    f32 break_apart_formation_damage_trigger_percent; // 1
                    f32 break_apart_formation_damage_trigger_time;    // 4
                    f32 break_formation_missile_reaction_time;        // 0
                    f32 break_apart_formation_missile_reaction_time;  // 4
                    bool break_apart_formation_on_buzz_head_toward;     // false
                    f32 break_formation_on_buzz_head_toward_time;     // 4
                    bool regroup_formation_on_buzz_head_toward;         // false
                    bool break_apart_formation_on_buzz_pass_by;         // false
                    f32 break_formation_on_buzz_pass_by_time;         // 4
                    bool regroup_formation_on_buzz_pass_by;             // false
                    bool break_apart_formation_on_evade_dodge;          // false
                    f32 break_formation_on_evade_dodge_time;          // 4
                    bool regroup_formation_on_evade_dodge;              // false
                    bool break_apart_formation_on_evade_break;          // false
                    f32 break_formation_on_evade_break_time;          // 4
                    bool regroup_formation_on_evade_break;              // false
                    int formation_exit_mode;
                    // 0 = BREAK_AWAY_FROM_CENTER
                    // 1 = BREAK_AWAY_FROM_CENTER_AFTERBURNER
                    // 2 = BRAKE_REVERSE
                    // 3 = OUTRUN
                    // 5 = NOTHING (default)
                    f32 formation_exit_top_turn_break_away_throttle; // 1
                    f32 formation_exit_roll_outrun_throttle;         // 0
                    f32 formation_exit_max_time;                     // 0
                    bool leader_makes_me_tougher;                      // false
            };

            struct JobStruct
            {
                    IMPORT JobStruct();
                    IMPORT JobStruct& operator=(const JobStruct&);

                    int _000;                        // 0
                    int scene_toughness_threshold;   // 2
                                                     // 0 = EASIEST
                                                     // 1 = EASY
                                                     // 2 = EQUAL
                                                     // 3 = HARD
                                                     // 4 = HARDEST
                    int target_toughness_preference; // 2
                                                     // 0 = EASIEST
                                                     // 1 = EASY
                                                     // 2 = EQUAL
                                                     // 3 = HARD
                                                     // 4 = HARDEST
                    f32 combat_drift_distance;     // ? 10000 (ignored)
                    struct Tattack_order
                    {
                            int type;                     // 11
                            f32 distance;               // 5000
                            int flag;                     // 15
                    } attack_order[13];                   // attack_preference
                                                          // index 0 = FIGHTER
                                                          //		 1 = FREIGHTER
                                                          //		 2 = TRANSPORT
                                                          //		 3 = GUNBOAT
                                                          //		 4 = CRUISER
                                                          //		 5 = CAPITAL
                                                          //		 6 = TRADELANE
                                                          //		 7 = JUMPGATE
                                                          //		 8 = WEAPONS_PLATFORM
                                                          //		 9 = DESTROYABLE_DEPOT
                                                          //		10 = SOLAR
                                                          //		11 = ANYTHING
                                                          //		12 = end of list
                                                          // flag  1 = GUNS
                                                          //		 2 = GUIDED
                                                          //		 4 = UNGUIDED	// bug - also matches GUIDED
                                                          //		 8 = TORPEDO
                    int attack_subtarget_order[8];        // 6
                                                          // 0 = GUNS
                                                          // 1 = TURRETS
                                                          // 2 = LAUNCHERS
                                                          // 3 = TOWERS
                                                          // 4 = ENGINES
                                                          // 5 = HULL
                                                          // 6 = ANYTHING
                                                          // 7 = end of list
                    bool wait_for_leader_target;          // not initialised
                    f32 maximum_leader_target_distance; // 5000
                    int field_targeting;                  // 3
                                                          // 0 = NEVER
                                                          // 1 = LOW_DENSITY
                                                          // 2 = HIGH_DENSITY
                                                          // 3 = ALWAYS
                    int loot_preference;                  // 0
                                                          // 0 = LT_NONE
                                                          // 1 = LT_COMMODITIES
                                                          // 2 = LT_EQUIPMENT
                                                          // 4 = LT_POTIONS
                                                          // 7 = LT_ALL (bitmask)
                    int loot_flee_threshold;              // 2
                                                          // 0 = EASIEST
                                                          // 1 = EASY
                                                          // 2 = EQUAL
                                                          // 3 = HARD
                                                          // 4 = HARDEST
                    int _0E0;                             // 0
                    int _0E4_120[16];                     // not initialised
                    int flee_scene_threat_style;          // 3
                                                          // 0 = EASIEST
                                                          // 1 = EASY
                                                          // 2 = EQUAL
                                                          // 3 = HARD
                                                          // 4 = HARDEST
                    f32 flee_when_hull_damaged_percent; // 0
                    bool flee_when_leader_flees_style;    // true
                    bool flee_no_weapons_style;           // true
                    bool allow_player_targeting;          // true
                    f32 _130;                           // -1
                    bool force_attack_formation;          // false
                    bool force_attack_formation_used;     // false (true when above is set)
            };

            enum class TOUGHNESS_TYPE {};

            IMPORT Personality();
            IMPORT Personality& operator=(const Personality&);
            IMPORT static const f32 SCAN_CHANCE_DEFAULT;
            IMPORT f32 get_range_threshold_value();
            IMPORT f32 get_toughness_ratio(TOUGHNESS_TYPE);

            public:
            EvadeDodgeUseStruct EvadeDodgeUse;
            EvadeBreakUseStruct EvadeBreakUse;
            BuzzHeadTowardUseStruct BuzzHeadTowardUse;
            BuzzPassByUseStruct BuzzPassByUse;
            TrailUseStruct TrailUse;
            StrafeUseStruct StrafeUse;
            EngineKillUseStruct EngineKillUse;
            RepairUseStruct RepairUse;
            GunUseStruct GunUse;
            MineUseStruct MineUse;
            MissileUseStruct MissileUse;
            DamageReactionStruct DamageReaction;
            MissileReactionStruct MissileReaction;
            CountermeasureUseStruct CountermeasureUse;
            FormationUseStruct FormationUse;
            JobStruct Job;
        };
    }
}