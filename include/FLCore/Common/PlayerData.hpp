#pragma once

#include "../FLCoreDefs.hpp"
#include "MiscStructs.hpp"
#include "Unknown.hpp"
#include "CArchGroup.hpp"

struct LoadedCharacterData
{
        CHARACTER_ID characterCode;
        uint padding;
        st6::wstring name;                                    // 512
        st6::wstring description;                             // 528
        uint descripStrId;                                    // 544
        uint datetimeHigh;                                    // 548
        uint datetimeLow;                                     // 552
        uint shipHash;                                        // 556
        int money;                                            // 560
        int numOfKills;                                       // 564
        int numOfSuccessMissions;                             // 568
        int numOfFailedMissions;                              // 572
        float hullStatus;                                     // 576
        st6::list<EquipDesc> currentEquipAndCargo;            // 580
        st6::list<CollisionGroupDesc> currentCollisionGroups; // 592
        uint system;                                          // 644
        uint currentBase;
        uint currentRoom;
        uint voice;
        uint rank;
        Costume costumeOne;
        Costume costumeTwo;
};
