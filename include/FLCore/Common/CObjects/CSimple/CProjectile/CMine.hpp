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

    IMPORT ~CMine() override;
    IMPORT int update(f32, u32) override;
    IMPORT u32 get_name() const override;
    IMPORT void init_physics(const Vector&, const Vector&) override;
    IMPORT virtual void init(const CreateParms&);
    IMPORT void expire_safe_time() override;

    IMPORT CMine(const CMine&);
    IMPORT CMine(Class);
    IMPORT const Archetype::Mine* minearch();
};
