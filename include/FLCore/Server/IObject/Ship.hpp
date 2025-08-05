#pragma once

#include "../../FLCoreDefs.hpp"
#include "../../Common/SubObjectID.hpp"
#include "EqObj.hpp"

struct Ship : public EqObj
{
        CShip* cship() { return reinterpret_cast<CShip*>(cobject()); };

        static Ship* Cast(IObjInspectImpl* iobj)
        {
            if (iobj->cobject()->objectClass == CObject::CSHIP_OBJECT)
            {
                return reinterpret_cast<Ship*>(iobj);
            }
            return nullptr;
        }

        // float iDunno_0x8C; 0x8C hidden when debugging for unknown reasons, a float of -26.18375
        int iDunno_0x90;
        int iDunno_0x94;
        bool bDunno_0x98;
        int iDunno_0x9C;
        float Dunno_0xA0;
        int* iDunno_0xA4; // struct size 0x28
        uint A4Size;
        int iDunno_0xAC;
        int iDunno_0xB0;
        int iDunno_0xB4;
        bool bDunno_0xB8;
        float pendingEnvironmentalDamage;
        float timeSinceLastUpdate;
        SubObjectID::EquipIdMaker equipIdMaker;
};
