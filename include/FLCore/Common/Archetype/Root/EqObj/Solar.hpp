#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct Solar : public EqObj
    {
        IMPORT Solar(const Solar&);
        IMPORT Solar(IClObj*);
        IMPORT virtual ~Solar();
        IMPORT Solar& operator=(const Solar&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 37 */ bool destrutible;
        /* 38 */ float solarRadius;
        /* 39 */ uint toughness;
        /* 40 */ char* openAnim;
        /* 41 */ char* jumpOutHp;
        /* 42 */ uint loadoutId;
    };
}