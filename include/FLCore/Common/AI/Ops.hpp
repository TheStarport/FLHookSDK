#pragma once
#include "../../FLCoreDefs.hpp"
#include "Personality.hpp"
#include "AIEnums.hpp"

namespace pub
{
    namespace AI
    {

        struct ContentCallback;
        class BaseOp
        {
            public:
                IMPORT BaseOp(OpType);
                IMPORT BaseOp(const BaseOp&);

                IMPORT virtual bool validate();

                OpType op_type;
                int fireWeapons; // Probably a bool, anything non-zero turns it on
        };

        class DirectiveCancelOp : public BaseOp
        {
            public:
                IMPORT DirectiveCancelOp(const DirectiveCancelOp&);
                IMPORT DirectiveCancelOp();
                IMPORT virtual bool validate();
        };

        class DirectiveDelayOp : public BaseOp
        {
            public:
                IMPORT DirectiveDelayOp(const DirectiveDelayOp&);
                IMPORT DirectiveDelayOp();
                IMPORT virtual bool validate();

                f32 DelayTime;
        };

        class DirectiveDockOp : public BaseOp
        {
            public:
                IMPORT DirectiveDockOp(const DirectiveDockOp&);
                IMPORT DirectiveDockOp();
                IMPORT virtual bool validate();

                unsigned DockSpaceObj;
                unsigned x10;   // 0
                u16 x12; // 0
                u16 x14; // 0xbb, 0x83 ??
                int x18;    // -1
                unsigned x1C;   // 0
                f32 x20;  // 200
                f32 x24;  // 500
                unsigned x28;   // 0
        };

        class DirectiveDrasticEvadeOp : public BaseOp
        {
            public:
                IMPORT DirectiveDrasticEvadeOp(const DirectiveDrasticEvadeOp&);
                IMPORT DirectiveDrasticEvadeOp();
                IMPORT virtual bool validate();

            public:
                u8 data[OBJECT_DATA_SIZE];
        };

        class DirectiveEvadeOp : public BaseOp
        {
            public:
                IMPORT DirectiveEvadeOp(const DirectiveEvadeOp&);
                IMPORT DirectiveEvadeOp();
                IMPORT virtual bool validate();

                unsigned EvadeSpaceObj;
                u8 data[OBJECT_DATA_SIZE];
        };

        class DirectiveFaceOp : public BaseOp
        {
            public:
                IMPORT DirectiveFaceOp(const DirectiveFaceOp&);
                IMPORT DirectiveFaceOp();
                IMPORT virtual bool validate();

            public:
                u8 data[OBJECT_DATA_SIZE];
        };

        class DirectiveFollowOp : public BaseOp
        {
            public:
                IMPORT DirectiveFollowOp(const DirectiveFollowOp&);
                IMPORT DirectiveFollowOp();
                IMPORT virtual bool validate();

                unsigned followSpaceObj;
                f32 maxDistance;
                Vector offset;
                f32 dunno2; // 400
        };

        class DirectiveFormationOp : public BaseOp
        {
            public:
                IMPORT DirectiveFormationOp(const DirectiveFormationOp&);
                IMPORT DirectiveFormationOp();
                IMPORT virtual bool validate();

            public:
                u8 data[OBJECT_DATA_SIZE];
        };

        class DirectiveGotoOp : public BaseOp
        {
            public:
                IMPORT DirectiveGotoOp(const DirectiveGotoOp&);
                IMPORT DirectiveGotoOp();
                IMPORT virtual bool validate();

                int gotoType; // 1 = Vec, 0 = Ship, 2 = spline, 3 = undefined
                // The target position if GotoType is 1.
                Vector pos;
                // If GotoType is 0 then move to this spaceobj. Do not set a pos if you
                // set this.
                unsigned targetId;
                // The 4 points to fly to if GotoType is 2
                Vector spline[4];
                // This specifies how close the NPC will attempt to get to the position
                f32 range;
                // This specifies the thrust in the range from 0-100. Use -1 for maximum.
                f32 thrust;
                // This specifies if the ship should move (*not* always set to true)
                bool shipMoves;
                // This specifies if the ship should move (always set to true)
                bool shipMoves2;
                // Set the follow to control if the ship will cruise or not. Do not set
                // both to true.
                bool goToCruise;
                bool goToNoCruise;
                int x5C;
                f32 x60; // 200
                f32 x64; // 500
                int x68;
                f32 x6C;
        };

        class DirectiveGuideOp : public BaseOp
        {
            public:
                IMPORT DirectiveGuideOp(const DirectiveGuideOp&);
                IMPORT DirectiveGuideOp();
                IMPORT virtual bool validate();

            public:
                u8 data[OBJECT_DATA_SIZE];
        };

        class DirectiveIdleOp : public BaseOp
        {
            public:
                IMPORT DirectiveIdleOp(const DirectiveIdleOp&);
                IMPORT DirectiveIdleOp();
                IMPORT virtual bool validate();
        };

        class DirectiveInstantTradelaneOp : public BaseOp
        {
            public:
                IMPORT DirectiveInstantTradelaneOp(const DirectiveInstantTradelaneOp&);
                IMPORT DirectiveInstantTradelaneOp();
                IMPORT virtual bool validate();

                unsigned tradelaneRingFrom;
                unsigned tradelaneRingTo;
                f32 dunno; // 3750
        };

        class DirectiveLaunchOp : public BaseOp
        {
            public:
                IMPORT DirectiveLaunchOp(const DirectiveLaunchOp&);
                IMPORT DirectiveLaunchOp();
                IMPORT virtual bool validate();

                unsigned launchFromObject;
                unsigned x10; // 2, cannot be -1, defaults to -1
                unsigned x14; // 1, cannot be 0, defaults to 0
        };

        class DirectiveRamOp : public BaseOp
        {
            public:
                IMPORT DirectiveRamOp(const DirectiveRamOp&);
                IMPORT DirectiveRamOp();
                IMPORT virtual bool validate();

            public:
                u8 data[OBJECT_DATA_SIZE];
        };

        class DirectiveStrafeOp : public BaseOp
        {
            public:
                IMPORT DirectiveStrafeOp(const DirectiveStrafeOp&);
                IMPORT DirectiveStrafeOp();
                IMPORT virtual bool validate();

            public:
                u8 data[OBJECT_DATA_SIZE];
        };

        class DirectiveTractorBeamOp : public BaseOp
        {
            public:
                IMPORT DirectiveTractorBeamOp(const DirectiveTractorBeamOp&);
                IMPORT DirectiveTractorBeamOp();
                IMPORT virtual bool validate();

            public:
                u8 data[OBJECT_DATA_SIZE];
        };

        class DirectiveTrailOp : public BaseOp
        {
            public:
                IMPORT DirectiveTrailOp(const DirectiveTrailOp&);
                IMPORT DirectiveTrailOp();
                IMPORT virtual bool validate();

                unsigned x0C;  // 10
                f32 x10; // 500
                unsigned x14;  // 0
                unsigned x18;  // 0
        };

        class DirectiveWaitForPlayerManeuverOp : public BaseOp
        {
            public:
                IMPORT DirectiveWaitForPlayerManeuverOp(const DirectiveWaitForPlayerManeuverOp&);
                IMPORT DirectiveWaitForPlayerManeuverOp();
                IMPORT virtual bool validate();

            public:
                u8 data[OBJECT_DATA_SIZE];
        };

        class  DirectiveWaitForShip
        {
            public:
                IMPORT DirectiveWaitForShip(const DirectiveWaitForShip&);
                IMPORT DirectiveWaitForShip();
                IMPORT virtual bool validate();

            public:
                u8 data[OBJECT_DATA_SIZE];
        };

        struct GSplinePath
        {
                IMPORT GSplinePath();
                IMPORT GSplinePath& operator=(const GSplinePath&);

            public:
                u8 data[OBJECT_DATA_SIZE];
        };

        struct SetFlagParams
        {
                IMPORT SetFlagParams(const SetFlagParams&);
                IMPORT SetFlagParams();
                IMPORT virtual bool validate();

                unsigned x0C;  // 0
                f32 x10; // ??
                f32 x14; // ??
        };

        struct SetPersonalityParams : public BaseOp
        {
                IMPORT SetPersonalityParams();
                IMPORT SetPersonalityParams(const SetPersonalityParams&);

                IMPORT virtual bool validate();

                int stateGraph;
                ContentCallback* contentCallback;
                DirectiveCallback* directiveCallback;
                bool stateId; // true - state_graph_id, false - state_graph
                Personality personality;
        };

        // Note: op_type of SetZoneBehaviorParams is 1, indicating that the enum has a different meaning for pub::AI::SubmitState
        // Hex numbers behind dunno variables or in a comment indicate hex offset
        struct SetZoneBehaviorParams : public BaseOp
        {
                IMPORT SetZoneBehaviorParams(const SetZoneBehaviorParams&);
                IMPORT SetZoneBehaviorParams();
                IMPORT virtual bool validate();

                unsigned iZoneType;     // 0 = position, 1 = cuboid 2 = spaceobj
                unsigned iDunno_0x10;   // 0=?? 1=?? 2=delete user zone
                Vector vPosition;   // only used for iZoneType 0
                unsigned iSpaceObj;     // only used for iZoneType 2
                Vector vBoxCorner1; // only used for iZoneType 1
                Vector vBoxCorner2; // only used for iZoneType 1
                f32 fRadius;      // not used for iZoneType 1
        };
    }
}