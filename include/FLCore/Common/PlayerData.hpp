#pragma once

#include "../FLCoreDefs.hpp"
#include "MiscStructs.hpp"
#include "Unknown.hpp"
#include "CArchGroup.hpp"

struct LoadedCharacterData
{
        CHARACTER_ID characterCode;
        unsigned padding;
        st6::wstring name;                                    // 512
        st6::wstring description;                             // 528
        unsigned descripStrId;                                    // 544
        unsigned datetimeHigh;                                    // 548
        unsigned datetimeLow;                                     // 552
        unsigned shipHash;                                        // 556
        int money;                                            // 560
        int numOfKills;                                       // 564
        int numOfSuccessMissions;                             // 568
        int numOfFailedMissions;                              // 572
        f32 hullStatus;                                     // 576
        st6::list<EquipDesc> currentEquipAndCargo;            // 580
        st6::list<CollisionGroupDesc> currentCollisionGroups; // 592
        unsigned system;                                          // 644
        unsigned currentBase;
        unsigned currentRoom;
        unsigned voice;
        unsigned rank;
        Costume costumeOne;
        Costume costumeTwo;
};
