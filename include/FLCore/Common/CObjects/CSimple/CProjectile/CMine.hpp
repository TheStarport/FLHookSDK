#pragma once
#include "FLCore/FLCoreDefs.hpp"

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

        unsigned char data[OBJECT_DATA_SIZE];
    };

    IMPORT virtual ~CMine();
    IMPORT virtual int update(float, unsigned int);
    IMPORT virtual unsigned int get_name() const;
    IMPORT virtual void init_physics(const Vector&, const Vector&);
    IMPORT virtual void init(const CreateParms&);
    IMPORT virtual void expire_safe_time();

    IMPORT CMine(const CMine&);
    IMPORT CMine(Class);
    IMPORT const Archetype::Mine* minearch();
};