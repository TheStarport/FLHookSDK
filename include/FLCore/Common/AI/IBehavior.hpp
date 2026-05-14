#pragma once

#include "../../FLCoreDefs.hpp"

#include "../Watchable.hpp"
#include "AIEnums.hpp"
#include "ContentCallback.hpp"
#include "StateGraph.hpp"

enum class StrafeDir;
struct IObjRW;

namespace pub::AI
{
    class Personality;
    struct DirectiveCallback;
} // namespace pub::AI

struct IMPORT IDirectiveInfo
{
    bool init; // ? seems to be 1 after first time auto pilot takes over
    void* vUnknown1;
    pub::AI::OpType op;
};

// Size: 460 bytes
// Constructor e.g. sub_62D2220
// Hex numbers behind dunno variables or in a comment indicate hex offset
class IBehaviorManager
{
  public:
    enum IBehaviorCameraMode
    {
        A,
        B,
        C,
        D,
        E
    };

    enum class CancelRequestType
    {
    };
    enum class EvaluateResult
    {
    };

    struct Behavior
    {
        virtual void dunno0();
        virtual void dunno4();
        virtual void dunno8();
        virtual void dunnoC();
        virtual void dunno10();
        virtual void dunno14();
        virtual void dunno18();
        virtual void dunno1C();
        virtual void dunno20();
        virtual void dunno24();
        virtual bool SetOp(int op);
        virtual void dunno2C();
        virtual void dunno30();
        virtual void SetThrottle(f32 throttle);
        virtual void SetCruise(bool cruiseState);
        virtual void SetEngine(bool engineState);
        virtual void SetThruster(bool thrusterState);
        virtual void SetSlideStrafeBurst(StrafeDir dir);
        virtual void SetBrakeReverse(bool newState);
        virtual bool GetAllowHeadTracking();
        virtual void dunno50();
        virtual void dunno54();
        virtual void dunno58();
        virtual void dunno5C();
        virtual IObjRW* GetDebuggerTarget();
    };

    IMPORT bool allow_head_tracking();
    IMPORT bool cancel_behavior(CancelRequestType);
    IMPORT bool enable_all_maneuvers();
    IMPORT bool enable_maneuver(int, bool);
    IMPORT EvaluateResult external_player_evaluate(int);
    IMPORT bool get_camera_level_status();
    IMPORT f32 get_closest_trailing_ship() const;
    IMPORT const IDirectiveInfo* get_current_directive();
    IMPORT const IObjRW* get_debugger_target() const;
    IMPORT bool get_docking_port(const IObjRW*&, int&);
    IMPORT u32 get_parent_id();
    IMPORT void get_personality(pub::AI::Personality&);
    IMPORT pub::AI::ScanResponse get_scan_response(u32);
    IMPORT const Vector get_ship_up_direction();
    IMPORT const IStateGraph* get_state_graph();
    IMPORT class SystemManager* get_sys();
    IMPORT bool get_user_turning_input_state();
    IMPORT bool lock_maneuvers(bool);
    IMPORT void refresh_state_graph();
    IMPORT void reset_current_behavior_direction();
    IMPORT void set_camera_mode(IBehaviorCameraMode);
    IMPORT void set_content_callback(pub::AI::ContentCallback*);
    IMPORT bool set_current_directive(const IDirectiveInfo&, const pub::AI::BaseOp*);
    IMPORT void set_directive_callback(pub::AI::DirectiveCallback*);
    IMPORT pub::AI::OP_RTYPE set_directive_priority(pub::AI::DirectivePriority);
    IMPORT void set_personality(const pub::AI::Personality&);
    IMPORT void set_ship_up_direction(const Vector&);
    IMPORT void set_state_graph(int, bool);
    IMPORT void set_turn_sensitivity(f32);
    IMPORT void set_user_turning_input_state(bool);
    IMPORT void submit_camera_up(const Vector&);
    IMPORT void update_current_behavior_afterburner(bool);
    IMPORT void update_current_behavior_auto_avoidance(bool);
    IMPORT void update_current_behavior_auto_level(bool);
    IMPORT void update_current_behavior_brake_reverse(bool);
    IMPORT void update_current_behavior_cruise(bool);
    IMPORT void update_current_behavior_direction(const Vector&);
    IMPORT void update_current_behavior_engage_engine(bool);
    IMPORT void update_current_behavior_slide_strafe_burst(StrafeDir);
    IMPORT void update_current_behavior_throttle(f32);
    IMPORT void update_level_camera(bool);

    struct BehaviorSwitchRatios
    {
        f32 percentage;
        pub::AI::OpType type;
    };

    enum class AiEventId
    {
        MunitionImpact = 1
    };

    struct AiEventData
    {
        AiEventId id;
        void* data;
    };

    virtual void process_ai_event(AiEventData* eventData);

  public:
    IStateGraph* stateGraphInternal; // 0x04
    void* pDunno_0x08;
    struct PathfindManager* pathfindManager; // 0xC
    BehaviorSwitchRatios switchRatios[21];
    int iEnabledManeuversFlag;               // 0xB8 - 0 = all enabled
    bool bLockManeuvers;                     // 0xBC
    pub::AI::OpType iCurrentBehaviourIndex;  // 0xC0 - -1 when no behaviour, otherwise index of behaviourArray
    IDirectiveInfo* directiveInfo;           // 0xC4
    int iDirectivePriority;                  // 0xC8
    int iDirectiveOp;                        // 0xCC
    f32 timeSinceLastDirectiveChange;        // 0xD0
    f32 timeSinceLastDirectiveChangeAttempt; // 0xD4
    byte forceDirectiveRefresh;              // 0xD8
    f32 timeAlive;                           // 0xDC
    f32 fDunno56_0xE0;
    f32 fDunno57_0xE4;
    int iDunnos58_0xE8[2];
    BaseWatcher baseWatcher; // 0xF0
    byte bDunno62_0xF8;
    bool bCameraLevelStatusFlag;                       // 0xF9
    pub::AI::DirectiveCallback* directiveCallbacks[5]; // 0xFC
    pub::AI::ContentCallback* contentCallback;         // 0x110
    int iDunnos_0x114[3];
    pub::AI::OpType queuedBehaviourIndex; // 0x120
    int iDunnos_0x124[3];
    bool bDunno_0x130;
    Vector shipUpDirection;   // 0x134
    Vector cameraUpDirection; // 0x140
    int iDunno_0x14C;
    bool bUserTurningInputState;    // 0x150
    IBehaviorCameraMode cameraMode; // 0x154
    byte bDunno_0x158;
    void* pDunno_0x15C;
    int iDunnos_0x160;
    f32 fTurnSensitivity; // 0x164
    byte bDunno_0x168;
    byte bDunno_0x169;
    int iDunno_0x16C;
    byte disableUpdates;
    Behavior* behaviourArray[21]; // 0x174 - index 7 seems to be docking
    byte bDunno_0x1C8;
};
