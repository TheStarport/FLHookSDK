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
                IMPORT virtual void combat_state_notification(CSNType, unsigned int, unsigned int);
                IMPORT virtual void follow_event(unsigned int, unsigned int, FollowStatusType, float);
                IMPORT virtual CreationType get_creation_type();
                IMPORT virtual bool information_request(InformationType, int, char*);
                IMPORT virtual void lead_object_event(unsigned int, unsigned int, LeadProgressType, float, const Vector&);
                IMPORT virtual bool request_flee_destination(unsigned int, FleeReason, FleeDestinationType&, Vector&, unsigned int&, float&);
                IMPORT virtual void scan_state_change(bool);
                IMPORT virtual void ship_in_sights_event(unsigned int);
                IMPORT virtual void tether_object_event(unsigned int, unsigned int, TetherStatusType, const Vector&);

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };
    } // namespace AI
} // namespace pub
