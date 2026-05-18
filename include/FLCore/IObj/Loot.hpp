#pragma once

#include "Base.hpp"

struct IObjServerLoot : ServerGameObject
{
    CLoot* cloot() { return reinterpret_cast<CLoot*>(cobject()); };

    static IObjServerLoot* cast(IObjInspectImpl* iobj)
    {
        if (iobj->cobject()->objectClass == CObject::CLOOT_OBJECT)
        {
            return reinterpret_cast<IObjServerLoot*>(iobj);
        }
        return nullptr;
    }
    // TODO: Fields and methods
};
