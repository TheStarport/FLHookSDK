#pragma once
#include "../../../FLCoreDefs.hpp"
#include <FLCore/Common/Archetype/ArchetypeMethods.hpp>
#include <FLCore/Common/Archetype/Root.hpp>
#include <FLCore/Common/Enums.hpp>

namespace Archetype
{
    class IMPORT FuseIgnitionList
    {
        public:
            unsigned dunno[4];
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

            /* 23 */ f32 volume;
            /* 24 */ unsigned useCount;
            /* 25 */ unsigned unitsPerContainer;
            /* 26 */ unsigned tractoredExplosionId;
            /* 27 */ bool lootable;
    };
} // namespace Archetype
