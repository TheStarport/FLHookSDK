#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct Tractor : public Equipment
    {
        IMPORT Tractor(const Tractor&);
        IMPORT Tractor(IClObj*);
        IMPORT virtual ~Tractor();
        IMPORT Tractor& operator=(const Tractor&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual HpAttachmentType get_hp_type() const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 28 */ float maxLength;
        /* 29 */ float reachSpeed;
    };
}