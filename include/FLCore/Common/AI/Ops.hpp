#pragma once
#include "../../FLCoreDefs.hpp"
#include "Personality.hpp"

namespace pub
{
    namespace AI
    {

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

                float DelayTime;
        };

        class DirectiveDockOp : public BaseOp
        {
            public:
                IMPORT DirectiveDockOp(const DirectiveDockOp&);
                IMPORT DirectiveDockOp();
                IMPORT virtual bool validate();

                uint DockSpaceObj;
                uint x10;   // 0
                ushort x12; // 0
                ushort x14; // 0xbb, 0x83 ??
                int x18;    // -1
                uint x1C;   // 0
                float x20;  // 200
                float x24;  // 500
                uint x28;   // 0
        };

        class DirectiveDrasticEvadeOp : public BaseOp
        {
            public:
                IMPORT DirectiveDrasticEvadeOp(const DirectiveDrasticEvadeOp&);
                IMPORT DirectiveDrasticEvadeOp();
                IMPORT virtual bool validate();

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        class DirectiveEvadeOp : public BaseOp
        {
            public:
                IMPORT DirectiveEvadeOp(const DirectiveEvadeOp&);
                IMPORT DirectiveEvadeOp();
                IMPORT virtual bool validate();

                uint EvadeSpaceObj;
                unsigned char data[OBJECT_DATA_SIZE];
        };

        class DirectiveFaceOp : public BaseOp
        {
            public:
                IMPORT DirectiveFaceOp(const DirectiveFaceOp&);
                IMPORT DirectiveFaceOp();
                IMPORT virtual bool validate();

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        class DirectiveFollowOp : public BaseOp
        {
            public:
                IMPORT DirectiveFollowOp(const DirectiveFollowOp&);
                IMPORT DirectiveFollowOp();
                IMPORT virtual bool validate();

                uint followSpaceObj;
                float maxDistance;
                Vector offset;
                float dunno2; // 400
        };

        class DirectiveFormationOp : public BaseOp
        {
            public:
                IMPORT DirectiveFormationOp(const DirectiveFormationOp&);
                IMPORT DirectiveFormationOp();
                IMPORT virtual bool validate();

            public:
                unsigned char data[OBJECT_DATA_SIZE];
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
                uint targetId;
                // The 4 points to fly to if GotoType is 2
                Vector spline[4];
                // This specifies how close the NPC will attempt to get to the position
                float range;
                // This specifies the thrust in the range from 0-100. Use -1 for maximum.
                float thrust;
                // This specifies if the ship should move (*not* always set to true)
                bool shipMoves;
                // This specifies if the ship should move (always set to true)
                bool shipMoves2;
                // Set the follow to control if the ship will cruise or not. Do not set
                // both to true.
                bool goToCruise;
                bool goToNoCruise;
                int x5C;
                float x60; // 200
                float x64; // 500
                int x68;
                float x6C;
        };

        class DirectiveGuideOp : public BaseOp
        {
            public:
                IMPORT DirectiveGuideOp(const DirectiveGuideOp&);
                IMPORT DirectiveGuideOp();
                IMPORT virtual bool validate();

            public:
                unsigned char data[OBJECT_DATA_SIZE];
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

                uint tradelaneRingFrom;
                uint tradelaneRingTo;
                float dunno; // 3750
        };

        class DirectiveLaunchOp : public BaseOp
        {
            public:
                IMPORT DirectiveLaunchOp(const DirectiveLaunchOp&);
                IMPORT DirectiveLaunchOp();
                IMPORT virtual bool validate();

                uint launchFromObject;
                uint x10; // 2, cannot be -1, defaults to -1
                uint x14; // 1, cannot be 0, defaults to 0
        };

        class DirectiveRamOp : public BaseOp
        {
            public:
                IMPORT DirectiveRamOp(const DirectiveRamOp&);
                IMPORT DirectiveRamOp();
                IMPORT virtual bool validate();

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        class DirectiveStrafeOp : public BaseOp
        {
            public:
                IMPORT DirectiveStrafeOp(const DirectiveStrafeOp&);
                IMPORT DirectiveStrafeOp();
                IMPORT virtual bool validate();

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        class DirectiveTractorBeamOp : public BaseOp
        {
            public:
                IMPORT DirectiveTractorBeamOp(const DirectiveTractorBeamOp&);
                IMPORT DirectiveTractorBeamOp();
                IMPORT virtual bool validate();

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        class DirectiveTrailOp : public BaseOp
        {
            public:
                IMPORT DirectiveTrailOp(const DirectiveTrailOp&);
                IMPORT DirectiveTrailOp();
                IMPORT virtual bool validate();

                uint x0C;  // 10
                float x10; // 500
                uint x14;  // 0
                uint x18;  // 0
        };

        class DirectiveWaitForPlayerManeuverOp : public BaseOp
        {
            public:
                IMPORT DirectiveWaitForPlayerManeuverOp(const DirectiveWaitForPlayerManeuverOp&);
                IMPORT DirectiveWaitForPlayerManeuverOp();
                IMPORT virtual bool validate();

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        class  DirectiveWaitForShip
        {
            public:
                IMPORT DirectiveWaitForShip(const DirectiveWaitForShip&);
                IMPORT DirectiveWaitForShip();
                IMPORT virtual bool validate();

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        struct GSplinePath
        {
                IMPORT GSplinePath();
                IMPORT GSplinePath& operator=(const GSplinePath&);

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        struct SetFlagParams
        {
                IMPORT SetFlagParams(const SetFlagParams&);
                IMPORT SetFlagParams();
                IMPORT virtual bool validate();

                uint x0C;  // 0
                float x10; // ??
                float x14; // ??
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
                IMPORT SetZoneBehaviorParams(void);
                IMPORT virtual bool validate(void);

                uint iZoneType;     // 0 = position, 1 = cuboid 2 = spaceobj
                uint iDunno_0x10;   // 0=?? 1=?? 2=delete user zone
                Vector vPosition;   // only used for iZoneType 0
                uint iSpaceObj;     // only used for iZoneType 2
                Vector vBoxCorner1; // only used for iZoneType 1
                Vector vBoxCorner2; // only used for iZoneType 1
                float fRadius;      // not used for iZoneType 1
        };
    }
}