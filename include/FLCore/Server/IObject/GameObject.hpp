#pragma once

#include "../../FLCoreDefs.hpp"
#include "IObjectInspect.hpp"
#include <FLCore/Common/CObjects/CSimple/CEqObj/CSolar.hpp>

struct GameObject : public IObjRW, public IObjAffect, public IObjDestructor
{
    CSimple* csimple() { return reinterpret_cast<CSimple*>(cobject()); };
    static GameObject* Cast(IObjInspectImpl* iobj)
    {
        if ((iobj->cobject()->objectClass & CObject::CSIMPLE_MASK) == CObject::CSIMPLE_MASK)
        {
            return reinterpret_cast<GameObject*>(iobj);
        }
        return nullptr;
    }

    bool IsStaticSolar()
    {
        if (!cobj)
        {
            return false;
        }
        if (!(cobj->objectClass & CObject::CSOLAR_OBJECT))
        {
            return false;
        }
        return !reinterpret_cast<CSolar*>(cobj)->isDynamic;
    }

    CObject* cobj;
    GameObject* next;  // warning: might only apply to client variant of the object
    void* pDunno_0x18; // struct size: 12 bytes
    int iDunnos_0x1C;  // length of 0x1C
    f64 timer;
    StarSystem* starSystem; // has something to do with fuses
    byte bDunno_0x2C;
    void* pDunno_0x30;   // struct size: 20 bytes
    int iDunno_0x34;     // length of 0x30
    byte isInvulnerable; // not entirely sure on those two
    byte isPlayerVulnerable;
    f32 maxHpLoss;    // when invulnerable, allow HP to drop down to this percentage
    byte bDunno_0x40; // is alive? Used when fetching IObjRW via sub_6D00670
    byte bDunno_0x41;
    byte bAlign_0x42; // probably not used
    byte bAlign_0x43; // probably not used
    byte bDunno_0x44;
    void* pDunno_0x48; // struct size: 20 bytes
    int iDunno_0x4C;   // size of 0x48
    byte bDunno_0x50;
    int iDunnos_0x54;
};
