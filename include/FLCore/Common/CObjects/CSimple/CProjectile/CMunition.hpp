#pragma once
#include "FLCore/FLCoreDefs.hpp"

struct CMunition : public CProjectile
{
    public:
    IMPORT virtual ~CMunition();

    IMPORT CMunition(const CMunition&);
    IMPORT CMunition(Class);
    IMPORT const Archetype::Munition* munitionarch() const;
};