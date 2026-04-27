#pragma once
#include <FLCore/FLCoreDefs.hpp>

namespace Archetype
{
    struct Mine;
}
struct CMine : CProjectile
{
    struct IMPORT CreateParms
    {
        CreateParms();
        CreateParms& operator=(const CreateParms&);

        u8 data[OBJECT_DATA_SIZE];
    };

    IMPORT virtual ~CMine();
    IMPORT virtual int update(f32, u32);
    IMPORT virtual u32 get_name() const;
    IMPORT virtual void init_physics(const Vector&, const Vector&);
    IMPORT virtual void init(const CreateParms&);
    IMPORT virtual void expire_safe_time();

    IMPORT CMine(const CMine&);
    IMPORT CMine(Class);
    IMPORT const Archetype::Mine* minearch();
};