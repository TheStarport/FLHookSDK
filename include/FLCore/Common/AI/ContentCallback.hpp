#pragma once
#include "../../FLCoreDefs.hpp"

namespace pub
{
    namespace AI
    {
        struct ContentCallback
        {
                enum class CSNType
                {
                };
                enum class FollowStatusType
                {
                };
                enum CreationType
                {
                };
                enum class InformationType
                {
                };
                enum class LeadProgressType
                {
                };
                enum class FleeReason
                {
                };
                enum class FleeDestinationType
                {
                };
                enum class TetherStatusType
                {
                };

                IMPORT virtual void combat_drift_event();
                IMPORT virtual void combat_state_notification(CSNType, u32, u32);
                IMPORT virtual void follow_event(u32, u32, FollowStatusType, f32);
                IMPORT virtual CreationType get_creation_type();
                IMPORT virtual bool information_request(InformationType, int, char*);
                IMPORT virtual void lead_object_event(u32, u32, LeadProgressType, f32, const Vector&);
                IMPORT virtual bool request_flee_destination(u32, FleeReason, FleeDestinationType&, Vector&, u32&, f32&);
                IMPORT virtual void scan_state_change(bool);
                IMPORT virtual void ship_in_sights_event(u32);
                IMPORT virtual void tether_object_event(u32, u32, TetherStatusType, const Vector&);

            public:
                u8 data[OBJECT_DATA_SIZE];
        };
    } // namespace AI
} // namespace pub
