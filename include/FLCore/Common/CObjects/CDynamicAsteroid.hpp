#pragma once
#include "../../FLCoreDefs.hpp"
#include "CObject.hpp"

namespace Archetype
{
    class DynamicAsteroid;
}

struct CDynamicAsteroid : CObject
{
        IMPORT virtual ~CDynamicAsteroid();
        IMPORT virtual int update(f32, u32);
        IMPORT virtual void init_physics(const Vector&, const Vector&, u32);

        struct IMPORT CreateParms
        {
                CreateParms();
                CreateParms& operator=(const CreateParms&);

                u8 data[OBJECT_DATA_SIZE];
        };

        IMPORT CDynamicAsteroid(const CDynamicAsteroid&);
        IMPORT CDynamicAsteroid();
        IMPORT const Archetype::DynamicAsteroid* dynamicAsteroidArch() const;
        IMPORT void init(const CreateParms&);
};
