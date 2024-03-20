#pragma once

#include "../../FLCoreDefs.hpp"
#include "EqObj.hpp"

struct Ship : public EqObj, public IObjAffect, public IObjDestructor
{
    CShip* cship(){return reinterpret_cast<CShip*>(cobject());};

    static Ship* Cast(IObjInspectImpl* iobj)
    {
        if(iobj->cobject()->objectClass == CObject::CSHIP_OBJECT)
        {
            return reinterpret_cast<Ship*>(iobj);
        }
        return nullptr;
    }

    int iDunno_0x8C;
    int iDunno_0x90;
    int iDunno_0x94;
    bool bDunno_0x98;
    int iDunno_0x9C;
    int iDunno_0xA0;
    int* iDunno_0xA4; // struct size 0x28
    uint A4Size;
    int iDunno_0xAC;
    int iDunno_0xB0;
    int iDunno_0xB4;
    bool bDunno_0xB8;
    float pendingEnvironmentalDamage;
    float timeSinceLastUpdate;
    uint* nextEqId;
};