#pragma once
#include "../../../FLCoreDefs.hpp"
#include "FLCore/Common/Archetype/ArchetypeMethods.hpp"
#include "FLCore/Common/Archetype/Root.hpp"
#include "FLCore/Common/INI_Reader.hpp"

namespace Archetype
{
    class IMPORT FuseIgnitionList
    {
        public:
        uint dunno[4];
    };

    struct Equipment : Root
    {
        IMPORT Equipment(const Equipment&);
        IMPORT Equipment(IClObj*);
        IMPORT virtual ~Equipment();
        IMPORT Equipment& operator=(const Equipment&);

        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);
        IMPORT virtual bool load();
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual void free_resources();
        IMPORT virtual HpAttachmentType get_hp_type() const;
        IMPORT virtual Equipment* get_loot_appearance();
        IMPORT virtual struct CargoPod* get_pod_appearance();
        IMPORT virtual bool is_attached() const;

        /* 23 */ float volume;
        /* 24 */ uint useCount;
        /* 25 */ uint unitsPerContainer;
        /* 26 */ uint tractoredExplosionId;
        /* 27 */ uint lootable;
    };
}