#pragma once
#include <FLCore/FLCoreDefs.hpp>

namespace Archetype
{
    struct Solar : public EqObj
    {
        IMPORT Solar(const Solar&);
        IMPORT Solar(IClObj*);
        IMPORT ~Solar() override;
        IMPORT Solar& operator=(const Solar&);
        IMPORT ClassType get_class_type() const override;
        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;

      public:
        /* 37 */ bool destrutible;
        /* 38 */ f32 solarRadius;
        /* 39 */ unsigned toughness;
        /* 40 */ char* openAnim;
        /* 41 */ char* jumpOutHp;
        /* 42 */ unsigned loadoutId;
    };
} // namespace Archetype
