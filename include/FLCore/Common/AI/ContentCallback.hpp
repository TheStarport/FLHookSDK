#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace pub
{
    namespace AI
    {
        struct ContentCallback
        {
            IMPORT virtual void combat_drift_event();
            IMPORT virtual void combat_state_notification(enum CSNType, unsigned int, unsigned int);
            IMPORT virtual void follow_event(unsigned int, unsigned int, enum FollowStatusType, float);
            IMPORT virtual enum CreationType get_creation_type();
            IMPORT virtual bool information_request(enum InformationType, int, char*);
            IMPORT virtual void lead_object_event(unsigned int, unsigned int, enum LeadProgressType, float, const Vector&);
            IMPORT virtual bool request_flee_destination(unsigned int, enum FleeReason, enum FleeDestinationType&, Vector&, unsigned int&, float&);
            IMPORT virtual void scan_state_change(bool);
            IMPORT virtual void ship_in_sights_event(unsigned int);
            IMPORT virtual void tether_object_event(unsigned int, unsigned int, enum TetherStatusType, const Vector&);

            public:
            unsigned char data[OBJECT_DATA_SIZE];
        };
    }
}