#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct Scanner final : Equipment
    {
        IMPORT Scanner(const Scanner&);
        IMPORT Scanner(IClObj*);
        IMPORT virtual ~Scanner();
        IMPORT Scanner& operator=(const Scanner&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual HpAttachmentType get_hp_type() const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 28 */ float powerUsage;
        /* 29 */ float range;
        /* 30 */ float cargoScanRange;
    };
}